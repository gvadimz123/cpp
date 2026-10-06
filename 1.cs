using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

class Order
{
    public int Id { get; set; }
    public string Product { get; set; }
    public double Price { get; set; }
    public int Quantity { get; set; }
    public double Total => Price * Quantity;
}

class Program
{
    private static List<Order> orders = new List<Order>();
    private static string ordersFile = "orders.json";
    private static string logFile = "app.log";
    private static int nextId = 1;

    static void Main(string[] args)
    {
        LoadOrders();
        Log("INFO", "Запуск программы");

        while (true)
        {
            Console.WriteLine("\n--- Система управления заказами ---");
            Console.WriteLine("1. Показать все заказы");
            Console.WriteLine("2. Добавить заказ");
            Console.WriteLine("3. Удалить заказ");
            Console.WriteLine("4. Найти заказ по Id");
            Console.WriteLine("5. Выход");
            Console.Write("Выберите действие: ");

            var choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    ShowAllOrders();
                    break;
                case "2":
                    AddOrder();
                    break;
                case "3":
                    DeleteOrder();
                    break;
                case "4":
                    FindOrderById();
                    break;
                case "5":
                    Log("INFO", "Завершение работы программы");
                    return;
                default:
                    Log("WARNING", "Некорректный ввод в меню");
                    Console.WriteLine("Неверный выбор. Попробуйте снова.");
                    break;
            }
        }
    }

    static void LoadOrders()
    {
        try
        {
            if (File.Exists(ordersFile))
            {
                var json = File.ReadAllText(ordersFile);
                orders = JsonSerializer.Deserialize<List<Order>>(json) ?? new List<Order>();
                if (orders.Count > 0)
                    nextId = orders.Max(o => o.Id) + 1;
            }
            else
            {
                orders = new List<Order>();
            }
        }
        catch (JsonException ex)
        {
            Log("ERROR", $"Ошибка десериализации: {ex.Message}");
            orders = new List<Order>();
        }
        catch (Exception ex)
        {
            Log("ERROR", $"Ошибка чтения файла: {ex.Message}");
            orders = new List<Order>();
        }
    }

    static void SaveOrders()
    {
        try
        {
            if (File.Exists(ordersFile))
                File.Copy(ordersFile, "orders_backup.json", true);

            var options = new JsonSerializerOptions { WriteIndented = true };
            var json = JsonSerializer.Serialize(orders, options);
            File.WriteAllText(ordersFile, json);
        }
        catch (Exception ex)
        {
            Log("ERROR", $"Ошибка записи файла: {ex.Message}");
        }
    }

    static void ShowAllOrders()
    {
        Console.WriteLine("\n--- Все заказы ---");
        if (orders.Count == 0)
        {
            Console.WriteLine("Заказы отсутствуют.");
            return;
        }

        Console.WriteLine("{0,-5} {1,-20} {2,-10} {3,-10} {4,-10}", "Id", "Товар", "Цена", "Кол-во", "Сумма");
        foreach (var order in orders)
        {
            Console.WriteLine("{0,-5} {1,-20} {2,-10:F2} {3,-10} {4,-10:F2}",
                order.Id, order.Product, order.Price, order.Quantity, order.Total);
        }
    }

    static void AddOrder()
    {
        try
        {
            Console.Write("Введите название товара: ");
            var product = Console.ReadLine();
            Console.Write("Введите цену: ");
            if (!double.TryParse(Console.ReadLine(), out double price) || price <= 0)
            {
                Log("WARNING", "Некорректная цена при добавлении заказа");
                Console.WriteLine("Ошибка: Цена должна быть положительным числом.");
                return;
            }

            Console.Write("Введите количество: ");
            if (!int.TryParse(Console.ReadLine(), out int quantity) || quantity <= 0)
            {
                Log("WARNING", "Некорректное количество при добавлении заказа");
                Console.WriteLine("Ошибка: Количество должно быть положительным целым числом.");
                return;
            }

            var newOrder = new Order
            {
                Id = nextId++,
                Product = product,
                Price = price,
                Quantity = quantity
            };

            orders.Add(newOrder);
            SaveOrders();
            Log("INFO", $"Добавлен заказ Id={newOrder.Id}");
            Console.WriteLine($"Заказ добавлен с Id={newOrder.Id}");
        }
        catch (Exception ex)
        {
            Log("ERROR", $"Ошибка при добавлении заказа: {ex.Message}");
            Console.WriteLine("Произошла ошибка при добавлении заказа.");
        }
    }

    static void DeleteOrder()
    {
        try
        {
            Console.Write("Введите Id заказа для удаления: ");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Log("WARNING", "Некорректный Id при попытке удаления заказа");
                Console.WriteLine("Ошибка: Введите корректный числовой Id.");
                return;
            }

            var order = orders.FirstOrDefault(o => o.Id == id);
            if (order != null)
            {
                orders.Remove(order);
                SaveOrders();
                Log("INFO", $"Удален заказ Id={id}");
                Console.WriteLine($"Заказ с Id={id} удален.");
            }
            else
            {
                Log("WARNING", $"Попытка удалить несуществующий заказ Id={id}");
                Console.WriteLine($"Заказ с Id={id} не найден.");
            }
        }
        catch (Exception ex)
        {
            Log("ERROR", $"Ошибка при удалении заказа: {ex.Message}");
            Console.WriteLine("Произошла ошибка при удалении заказа.");
        }
    }

    static void FindOrderById()
    {
        try
        {
            Console.Write("Введите Id заказа для поиска: ");
            if (!int.TryParse(Console.ReadLine(), out int id))
            {
                Log("WARNING", "Некорректный Id при поиске заказа");
                Console.WriteLine("Ошибка: Введите корректный числовой Id.");
                return;
            }

            var order = orders.FirstOrDefault(o => o.Id == id);
            if (order != null)
            {
                Console.WriteLine($"\nЗаказ Id={order.Id}:");
                Console.WriteLine($"Товар: {order.Product}");
                Console.WriteLine($"Цена: {order.Price:F2}");
                Console.WriteLine($"Количество: {order.Quantity}");
                Console.WriteLine($"Сумма: {order.Total:F2}");
            }
            else
            {
                Log("WARNING", $"Заказ Id={id} не найден при поиске");
                Console.WriteLine($"Заказ с Id={id} не найден.");
            }
        }
        catch (Exception ex)
        {
            Log("ERROR", $"Ошибка при поиске заказа: {ex.Message}");
            Console.WriteLine("Произошла ошибка при поиске заказа.");
        }
    }

    static void Log(string level, string message)
    {
        var logEntry = $"[{DateTime.Now:yyyy-MM-dd HH:mm:ss}] [{level}] {message}";
        Console.WriteLine(logEntry);
        File.AppendAllText(logFile, logEntry + Environment.NewLine);
    }
}
