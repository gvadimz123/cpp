#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <fstream>

// 1. Интерфейс Strategy для калькулятора
class CalculationStrategy {
public:
    virtual double execute(double a, double b) const = 0;
    virtual ~CalculationStrategy() = default;
};

// 2. Две реализации
class AdditionStrategy : public CalculationStrategy {
public:
    double execute(double a, double b) const override {
        return a + b;
    }
};

class SubtractionStrategy : public CalculationStrategy {
public:
    double execute(double a, double b) const override {
        return a - b;
    }
};

// 3. Класс Context
class Calculator {
private:
    std::unique_ptr<CalculationStrategy> strategy;

public:
    // 16. Передача через конструктор
    Calculator(std::unique_ptr<CalculationStrategy> strat)
        : strategy(std::move(strat)) {}

    // 17. Замена во время выполнения
    void setStrategy(std::unique_ptr<CalculationStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    double calculate(double a, double b) {
        return strategy->execute(a, b);
    }
};
// 6. SortStrategy
class SortStrategy {
public:
    virtual void sort(std::vector<int>& data) const = 0;
    virtual ~SortStrategy() = default;
};

class BubbleSort : public SortStrategy {
public:
    void sort(std::vector<int>& data) const override {
        size_t n = data.size();
        for (size_t i = 0; i < n - 1; ++i) {
            for (size_t j = 0; j < n - i - 1; ++j) {
                if (data[j] > data[j + 1]) {
                    std::swap(data[j], data[j + 1]);
                }
            }
        }
        std::cout << "Bubble sort completed\n";
    }
};

class QuickSort : public SortStrategy {
private:
    void quickSort(std::vector<int>& data, int low, int high) const {
        if (low < high) {
            int pi = partition(data, low, high);
            quickSort(data, low, pi - 1);
            quickSort(data, pi + 1, high);
        }
    }

    int partition(std::vector<int>& data, int low, int high) const {
        int pivot = data[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (data[j] <= pivot) {
                ++i;
                std::swap(data[i], data[j]);
            }
        }
        std::swap(data[i + 1], data[high]);
        return i + 1;
    }

public:
    void sort(std::vector<int>& data) const override {
        quickSort(data, 0, data.size() - 1);
        std::cout << "Quick sort completed\n";
    }
};

// 8. Поиск
class SearchStrategy {
public:
    virtual int search(const std::vector<int>& data, int target) const = 0;
    virtual ~SearchStrategy() = default;
};

class LinearSearch : public SearchStrategy {
public:
    int search(const std::vector<int>& data, int target) const override {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i] == target) return i;
        }
        return -1;
    }
};

class BinarySearch : public SearchStrategy {
public:
    int search(const std::vector<int>& data, int target) const override {
        int left = 0, right = data.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (data[mid] == target) return mid;
            else if (data[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
};

// 9. Фильтрация
class FilterStrategy {
public:
    virtual std::vector<int> filter(const std::vector<int>& data) const = 0;
    virtual ~FilterStrategy() = default;
};

class EvenFilter : public FilterStrategy {
public:
    std::vector<int> filter(const std::vector<int>& data) const override {
        std::vector<int> result;
        for (int num : data) {
            if (num % 2 == 0) result.push_back(num);
        }
        return result;
    }
};

class PositiveFilter : public FilterStrategy {
public:
    std::vector<int> filter(const std::vector<int>& data) const override {
        std::vector<int> result;
        for (int num : data) {
            if (num > 0) result.push_back(num);
        }
        return result;
    }
};

// 10. Обработка строк
class StringStrategy {
public:
    virtual std::string process(const std::string& text) const = 0;
    virtual ~StringStrategy() = default;
};

class ToUpperStrategy : public StringStrategy {
public:
    std::string process(const std::string& text) const override {
        std::string result = text;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
};

class ToLowerStrategy : public StringStrategy {
public:
    std::string process(const std::string& text) const override {
        std::string result = text;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
};
// 11. Оплата
class PaymentStrategy {
public:
    virtual void pay(double amount) const = 0;
    virtual ~PaymentStrategy() = default;
};

class CardPayment : public PaymentStrategy {
public:
    void pay(double amount) const override {
        std::cout << "Paying " << amount << " via card\n";
    }
};

class CashPayment : public PaymentStrategy {
public:
    void pay(double amount) const override {
        std::cout << "Paying " << amount << " with cash\n";
    }
};

class CryptoPayment : public PaymentStrategy {
public:
    void pay(double amount) const override {
        std::cout << "Paying " << amount << " with cryptocurrency\n";
    }
};

// 12. Скидки
class DiscountStrategy {
public:
    virtual double apply(double price) const = 0;
    virtual ~DiscountStrategy() = default;
};

class PercentageDiscount : public DiscountStrategy {
private:
    double percentage;
public:
    PercentageDiscount(double percent) : percentage(percent) {}
    double apply(double price) const override {
        return price * (1 - percentage / 100);
    }
};

class FixedDiscount : public DiscountStrategy {
private:
    double amount;
public:
    FixedDiscount(double amt) : amount(amt) {}
    double apply(double price) const override {
        return std::max(0.0, price - amount);
    }
};

// 13. Логирование
class LoggingStrategy {
public:
    virtual void log(const std::string& message) const = 0;
    virtual ~LoggingStrategy() = default;
};

class ConsoleLogger : public LoggingStrategy {
public:
    void log(const std::string& message) const override {
        std::cout << "[CONSOLE] " << message << std::endl;
    }
};

class FileLogger : public LoggingStrategy {
public:
    void log(const std::string& message) const override {
        std::ofstream file("log.txt", std::ios::app);
        if (file.is_open
