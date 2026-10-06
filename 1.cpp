#include <iostream>

class Engine {
public:
    void start() { std::cout << "Engine started\n"; }
};

class Lights {
public:
    void turnOn() { std::cout << "Lights on\n"; }
};

class CarFacade {
private:
    Engine engine;
    Lights lights;
public:
    void startCar() {
        engine.start();
        lights.turnOn();
    }
};

class System {
private:
    void initHardware() { std::cout << "Hardware initialized\n"; }
    void loadSettings() { std::cout << "Settings loaded\n"; }
    void checkConnections() { std::cout << "Connections checked\n"; }
public:
    void start() {
        initHardware();
        loadSettings();
        checkConnections();
        std::cout << "System ready\n";
    }
};

Engine engine;
Lights lights;
engine.start();
lights.turnOn();
CarFacade car;
car.startCar();

class Setup {
private:
    void configureNetwork() { std::cout << "Network configured\n"; }
    void initializeDB() { std::cout << "DB initialized\n"; }
public:
    void setupSystem() {
        configureNetwork();
        initializeDB();
    }
};

class ComputerFacade {
private:
    void shutdownOS() { std::cout << "OS shutting down\n"; }
    void powerOff() { std::cout << "Power off\n"; }
public:
    void startup() { /* ... */ }
    void shutdown() {
        shutdownOS();
        powerOff();
    }
};


class CPU { public: void run() { std::cout << "CPU running\n"; } };
class Memory { public: void load() { std::cout << "Memory loaded\n"; } };
class Disk { public: void read() { std::cout << "Disk reading\n"; } };

class ComputerFacade {
    CPU cpu; Memory memory; Disk disk;
public:
    void boot() {
        cpu.run();
        memory.load();
        disk.read();
    }
};

class Graphics { public: void render() { std::cout << "Graphics rendering\n"; } };
class Sound { public: void play() { std::cout << "Sound playing\n"; } };
class Physics { public: void simulate() { std::cout << "Physics simulating\n"; } };

class GameFacade {
    Graphics graphics; Sound sound; Physics physics;
public:
    void startGame() {
        graphics.render();
        sound.play();
        physics.simulate();
    }
};

class Validator { public: bool validate(const std::string& s) { return !s.empty(); } };
class Database { public: void save(const std::string& s) { std::cout << "Saved: " << s << "\n"; } };
class EmailService { public: void send(const std::string& to) { std::cout << "Email sent to " << to << "\n"; } };

class UserService {
    Validator validator; Database db; EmailService email;
public:
    bool registerUser(const std::string& name, const std::string& email) {
        if (!validator.validate(name) || !validator.validate(email)) return false;
        db.save(name);
        email.send(email);
        return true;
    }
};

class TV { public: void on() { std::cout << "TV on\n"; } };
class AudioSystem { public: void volumeUp() { std::cout << "Audio on\n"; } };
class DVD { public: void play() { std::cout << "DVD playing\n"; } };

class HomeTheaterFacade {
    TV tv; AudioSystem audio; DVD dvd;
public:
    void watchMovie() {
        tv.on();
        audio.volumeUp();
        dvd.play();
    }
};

class Logger {
public:
    void log(const std::string& msg) {
        std::cout << "[LOG] " << msg << "\n";
    }
};

class SmartHomeFacade {
    Logger logger;
public:
    void activateSecurity() {
        logger.log("Activating security system...");
        logger.log("Security system ready");
    }
};

class UserFacade {
public:
    void greetUser(const std::string& name) {
        std::cout << "Hello, " << name << "!\n";
    }
};

class ServerFacade {
public:
    void start() { /* базовый старт */ }
    void init() { /* инициализация */ }
    void fullStart() {
        start();
        init();
        // ...
    }
};

class DataProcessor {
private:
    void encrypt() { /* сложная логика */ }
    void compress() { /* сложная логика */ }
public:
    void process(const std::string& data) {
        encrypt();
        compress();
        std::cout << "Data processed\n";
    }
};

class SafeFacade {
public:
    bool safeOperation() {
        try {
            // ... операции
            return true;
        } catch (...) {
            std::cout << "Error occurred\n";
            return false;
        }
    }
};

class AdminFacade { /* админские операции */ };
class UserFacade { /* пользовательские операции */ };

class OldSystem { public: void legacyMethod() {} };
class Adapter {
    OldSystem old;
public:
    void modernMethod() { old.legacyMethod(); }
};
class FacadeWithAdapter {
    Adapter adapter;
public:
    void operation() { adapter.modernMethod(); }
};

class Command { public: virtual void execute() = 0; };
class FacadeWithCommands {
    std::vector<Command*> commands;
public:
    void executeAll() {
        for (auto c : commands) c->execute();
    }
};

class SingletonFacade {
private:
    static SingletonFacade* instance;
    SingletonFacade() {}
public:
    static SingletonFacade* getInstance() {
        if (!instance) instance = new SingletonFacade();
        return instance;
    }
    void doSomething() { /* ... */ }
};
SingletonFacade* SingletonFacade::instance = nullptr;

#include <vector>
class VectorFacade {
    std::vector<int> data;
public:
    void add(int value) { data.push_back(value); }
    void printAll() {
        for (int v : data) std::cout << v << " ";
        std::cout << "\n";
    }
};

#include <iostream>
#include <string>

class AuthService {
public:
    bool authenticate(const std::string& username) {
        std::cout << "AuthService: Authenticating user '" << username << "'\n";
        return !username.empty();
    }
};

class PaymentService {
public:
    bool processPayment(double amount) {
        std::cout << "PaymentService: Processing payment of $" << amount << "\n";
        return amount > 0 && amount <= 10000.0;
    }
};

class NotificationService {
public:
    void sendOrderConfirmation(const std::string& user) {
        std::cout << "NotificationService: Sending order confirmation to '" << user << "'\n";
    }

    void sendErrorNotification(const std::string& user, const std::string& error) {
        std::cout << "NotificationService: Sending error notification to '" << user
                  << "': " << error << "\n";
    }
};

class OrderFacade {
private:
    AuthService authService;
    PaymentService paymentService;
    NotificationService notificationService;

public:
    bool placeOrder(const std::string& username, double amount) {
        if (!authService.authenticate(username)) {
            notificationService.sendErrorNotification(
                username, "Authentication failed: invalid username");
            return false;
        }

        if (!paymentService.processPayment(amount)) {
            notificationService.sendErrorNotification(
                username, "Payment failed: invalid amount");
            return false;
        }

        notificationService.sendOrderConfirmation(username);
        std::cout << "OrderFacade: Order placed successfully for '"
                  << username << "' with amount $" << amount << "\n";
        return true;
    }
};

int main() {
    OrderFacade facade;

    std::cout << "=== Order System - Facade Pattern Demo ===\n\n";

    std::cout << "Test 1: Valid order\n";
    facade.placeOrder("alice", 299.99);
    std::cout << "\n";

    std::cout << "Test 2: Authentication error (empty username)\n";
    facade.placeOrder("", 150.0);
    std::cout << "\n";

    std::cout << "Test 3: Payment error (negative amount)\n";
    facade.placeOrder("bob", -50.0);
    std::cout << "\n";

    std::cout << "Test 4: Payment error (amount exceeds limit)\n";
    facade.placeOrder("charlie", 15000.0);

    return 0;
}
