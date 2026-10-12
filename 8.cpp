#include <iostream>
#include <string>

// 1. Минимальный Decorator
class Component {
public:
    virtual std::string operation() = 0;
    virtual ~Component() = default;
};

class ConcreteComponent : public Component {
public:
    std::string operation() override {
        return "Базовый объект";
    }
};

class Decorator : public Component {
protected:
    Component* component;
public:
    Decorator(Component* c) : component(c) {}
    std::string operation() override {
        if (component) return component->operation();
        return "";
    }
};

class SimpleDecorator : public Decorator {
public:
    SimpleDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return "Декоратор: " + Decorator::operation();
    }
};

// 2. Проверка обёртки
void testWrapper() {
    ConcreteComponent* component = new ConcreteComponent();
    SimpleDecorator* decorated = new SimpleDecorator(component);
    std::cout << decorated->operation() << std::endl;
    delete decorated;
    delete component;
}

// 3. Цепочка декораторов
class AnotherDecorator : public Decorator {
public:
    AnotherDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return "Другой декоратор: " + Decorator::operation();
    }
};

void testChain() {
    ConcreteComponent* component = new ConcreteComponent();
    SimpleDecorator* decorator1 = new SimpleDecorator(component);
    AnotherDecorator* decorator2 = new AnotherDecorator(decorator1);
    std::cout << decorator2->operation() << std::endl;
    delete decorator2;
    delete decorator1;
    delete component;
}

// 4. Порядок применения
void testOrder() {
    std::cout << "Порядок 1:\n";
    ConcreteComponent* comp1 = new ConcreteComponent();
    SimpleDecorator* dec1 = new SimpleDecorator(comp1);
    AnotherDecorator* dec2 = new AnotherDecorator(dec1);
    std::cout << dec2->operation() << std::endl;

    std::cout << "\nПорядок 2:\n";
    ConcreteComponent* comp2 = new ConcreteComponent();
    AnotherDecorator* dec3 = new AnotherDecorator(comp2);
    SimpleDecorator* dec4 = new SimpleDecorator(dec3);
    std::cout << dec4->operation() << std::endl;

    delete dec2; delete dec1; delete comp1;
    delete dec4; delete dec3; delete comp2;
}

// 5. Без Decorator (наследование)
class InheritedComponent : public ConcreteComponent {
public:
    std::string operation() override {
        return "Наследование: " + ConcreteComponent::operation();
    }
};

void testInheritance() {
    InheritedComponent* inherited = new InheritedComponent();
    std::cout << inherited->operation() << std::endl;
    delete inherited;
}
// 6. Текст и декораторы
class Text : public Component {
private:
    std::string content;
public:
    Text(const std::string& text) : content(text) {}
    std::string operation() override { return content; }
};

class BoldDecorator : public Decorator {
public:
    BoldDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return "<b>" + Decorator::operation() + "</b>";
    }
};

class ItalicDecorator : public Decorator {
public:
    ItalicDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return "<i>" + Decorator::operation() + "</i>";
    }
};

// 7. Добавление нового декоратора
class UnderlineDecorator : public Decorator {
public:
    UnderlineDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return "<u>" + Decorator::operation() + "</u>";
    }
};

// 8. Комбинация
void testTextCombination() {
    Text* text = new Text("Пример текста");
    BoldDecorator* bold = new BoldDecorator(text);
    ItalicDecorator* italic = new ItalicDecorator(bold);
    UnderlineDecorator* underline = new UnderlineDecorator(italic);
    std::cout << underline->operation() << std::endl;
    delete underline; delete italic; delete bold; delete text;
}

// 9. Кофе и декораторы
class Coffee : public Component {
private:
    double price;
public:
    Coffee(double p = 100.0) : price(p) {}
    std::string operation() override {
        return "Кофе";
    }
    double getPrice() { return price; }
};

class MilkDecorator : public Decorator {
private:
    double milkPrice = 20.0;
public:
    MilkDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return Decorator::operation() + " с молоком";
    }
    double getPrice() {
        Coffee* coffee = dynamic_cast<Coffee*>(component);
        return coffee ? coffee->getPrice() + milkPrice : milkPrice;
    }
};

class SugarDecorator : public Decorator {
private:
    double sugarPrice = 5.0;
public:
    SugarDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return Decorator::operation() + " с сахаром";
    }
    double getPrice() {
        Coffee* coffee = dynamic_cast<Coffee*>(component);
        return coffee ? coffee->getPrice() + sugarPrice : sugarPrice;
    }
};

// 10. Подсчёт стоимости
void testCoffeePrice() {
    Coffee* coffee = new Coffee(100.0);
    MilkDecorator* milk = new MilkDecorator(coffee);
    SugarDecorator* sugar = new SugarDecorator(milk);
    std::cout << sugar->operation() << std::endl;
    std::cout << "Цена: " << sugar->getPrice() << " руб." << std::endl;
    delete sugar; delete milk; delete coffee;
}
// 11. Заказ и декораторы
class Order : public Component {
private:
    double basePrice;
public:
    Order(double price) : basePrice(price) {}
    std::string operation() override {
        return "Заказ";
    }
    double getPrice() { return basePrice; }
};

class DeliveryDecorator : public Decorator {
private:
    double deliveryCost = 300.0;
public:
    DeliveryDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return Decorator::operation() + " с доставкой";
    }
    double getPrice() {
        Order* order = dynamic_cast<Order*>(component);
        return order ? order->getPrice() + deliveryCost : deliveryCost;
    }
};

class PackagingDecorator : public Decorator {
private:
    double packagingCost = 50.0;
public:
    PackagingDecorator(Component* c) : Decorator(c) {}
    std::string operation() override {
        return Decorator::operation() + " в упаковке";
    }
    double getPrice() {
        Order* order = dynamic_cast<Order*>(component);
        return order ? order->getPrice() + packagingCost : packagingCost;
    }
};

// 12. Скидки
class DiscountDecorator : public Decorator {
private:
    double discountPercent;
public:
    DiscountDecorator(Component* c, double percent)
        : Decorator(c), discountPercent(percent) {}
    std::string operation() override {
        return Decorator::operation() + " со скидкой " +
               std::to_string(discountPercent) + "%";
    }
    double getPrice() {
        Order* order = dynamic_cast<Order*>(component);
        if (!order) return 0.0;
        double originalPrice = order->getPrice();
        return originalPrice * (1.0 - discountPercent / 100.0);
    }
};

// 13. Логирование
class LoggingDecorator : public Decorator {
public:
    LoggingDecorator(Component* c) : Decorator(c) {}

    std::string operation() override {
        std::cout << "LOG: Вызов метода operation() декоратора\n";
        std::string result = Decorator::operation();
        std::cout << "LOG: Результат операции: " << result << "\n";
        return result;
    }

    // Если нужно логировать и другие методы (например, getPrice),
    // их тоже можно переопределить:
    double getPrice() {
        Order* order = dynamic_cast<Order*>(component);
        if (!order) {
            std::cout << "LOG: Объект не является заказом, цена недоступна\n";
            return 0.0;
        }
        double price = order->getPrice();
        std::cout << "LOG: Получена цена: " << price << " руб.\n";
        return price;
    }
};

// Функция для тестирования декоратора логирования
void testLoggingDecorator() {
    std::cout << "\n=== ТЕСТИРОВАНИЕ ДЕКОРАТОРА ЛОГИРОВАНИЯ ===\n";

    // Создаём базовый заказ
    Order* order = new Order(1000.0);

    // Обернём заказ в декоратор логирования
    LoggingDecorator* loggingOrder = new LoggingDecorator(order);

    // Вызываем методы — должны появиться логи
    std::cout << "Вызов operation():\n";
    std::cout << loggingOrder->operation() << std::endl;

    std::cout << "\nВызов getPrice():\n";
    double price = loggingOrder->getPrice();
    std::cout << "Итоговая цена: " << price << " руб." << std::endl;

    // Освобождаем память
    delete loggingOrder;
    delete order;
}
