#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <stdexcept>

class Character {
private:
    std::string name;
    std::string characterClass;
    int health;
    int mana;
    int strength;
    int agility;
    int intelligence;
    std::string weapon;
    std::string armor;

public:
    Character() = default;

    friend class CharacterBuilder;

    void print() const {
        std::cout << "Character: " << name << " (" << characterClass << ")\n";
        std::cout << "Health: " << health << ", Mana: " << mana << "\n";
        std::cout << "Strength: " << strength << ", Agility: " << agility << ", Intelligence: " << intelligence << "\n";
        std::cout << "Weapon: " << weapon << ", Armor: " << armor << "\n\n";
    }
};

class CharacterBuilder {
private:
    Character character;

public:
    CharacterBuilder() {
        character.health = 100;
        character.mana = 50;
        character.strength = 10;
        character.agility = 10;
        character.intelligence = 10;
    }

    CharacterBuilder& setName(const std::string& name) {
        character.name = name;
        return *this;
    }

    CharacterBuilder& setClass(const std::string& cls) {
        character.characterClass = cls;
        return *this;
    }

    CharacterBuilder& setHealth(int h) {
        character.health = h;
        return *this;
    }

    CharacterBuilder& setMana(int m) {
        character.mana = m;
        return *this;
    }

    CharacterBuilder& setStrength(int s) {
        character.strength = s;
        return *this;
    }

    CharacterBuilder& setAgility(int a) {
        character.agility = a;
        return *this;
    }

    CharacterBuilder& setIntelligence(int i) {
        character.intelligence = i;
        return *this;
    }

    CharacterBuilder& setWeapon(const std::string& w) {
        character.weapon = w;
        return *this;
    }

    CharacterBuilder& setArmor(const std::string& a) {
        character.armor = a;
        return *this;
    }

    Character build() {
        if (character.name.empty()) {
            throw std::invalid_argument("Name cannot be empty");
        }
        if (character.health <= 0) {
            throw std::invalid_argument("Health must be greater than 0");
        }
        return character;
    }
};

class Order {
private:
    std::string customerName;
    std::vector<std::string> products;
    std::string deliveryMethod;
    std::string promoCode;
    bool giftWrapping;
    std::string comment;

public:
    Order() = default;

    friend class OrderBuilder;

    void print() const {
        std::cout << "Order for: " << customerName << "\n";
        std::cout << "Products: ";
        for (const auto& p : products) std::cout << p << " ";
        std::cout << "\nDelivery: " << deliveryMethod << ", Promo: " << promoCode;
        std::cout << ", Gift wrapping: " << (giftWrapping ? "Yes" : "No");
        std::cout << ", Comment: " << comment << "\n\n";
    }
};

class OrderBuilder {
private:
    Order order;

public:
    OrderBuilder& setCustomerName(const std::string& name) {
        order.customerName = name;
        return *this;
    }

    OrderBuilder& addProduct(const std::string& product) {
        order.products.push_back(product);
        return *this;
    }

    OrderBuilder& setDeliveryMethod(const std::string& method) {
        order.deliveryMethod = method;
        return *this;
    }

    OrderBuilder& setPromoCode(const std::string& code) {
        order.promoCode = code;
        return *this;
    }

    OrderBuilder& enableGiftWrapping() {
        order.giftWrapping = true;
        return *this;
    }

    OrderBuilder& setComment(const std::string& comment) {
        order.comment = comment;
        return *this;
    }

    Order build() {
        if (order.products.empty()) {
            throw std::invalid_argument("Order must have at least one product");
        }
        return order;
    }
};

class HttpRequest {
private:
    std::string method;
    std::string url;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> params;
    std::string body;

public:
    HttpRequest() = default;

    friend class HttpRequestBuilder;

    void print() const {
        std::cout << method << " " << url << "\n";
        for (const auto& [k, v] : headers) std::cout << k << ": " << v << "\n";
        for (const auto& [k, v] : params) std::cout << "Param " << k << " = " << v << "\n";
        if (!body.empty()) std::cout << "Body: " << body << "\n";
        std::cout << "\n";
    }
};

class HttpRequestBuilder {
private:
    HttpRequest request;

public:
    RequestBuilder& setMethod(const std::string& m) {
        request.method = m;
        return *this;
    }

    RequestBuilder& setUrl(const std::string& u) {
        request.url = u;
        return *this;
    }

    RequestBuilder& addHeader(const std::string& key, const std::string& value) {
        request.headers[key] = value;
        return *this;
    }

    RequestBuilder& addParam(const std::string& key, const std::string& value) {
        request.params[key] = value;
        return *this;
    }

    RequestBuilder& setBody(const std::string& b) {
        request.body = b;
        return *this;
    }

    HttpRequest build() {
        if (request.url.empty()) {
            throw std::invalid_argument("URL cannot be empty");
        }
        return request;
    }
};

class DatabaseConfig {
private:
    std::string host;
    int port;
    std::string login;
    std::string password;
    std::string databaseName;
    bool useSSL;
    int timeout;

public:
    DatabaseConfig() = default;

    friend class DatabaseConfigBuilder;

    void print() const {
        std::cout << "Host: " << host << ", Port: " << port << "\n";
        std::cout << "Login: " << login << ", Password: " << (password.empty() ? "WARNING: empty" : "set") << "\n";
        std::cout << "Database: " << databaseName << ", SSL: " << (useSSL ? "Yes" : "No") << ", Timeout: " << timeout << "\n\n";
    }
};

class DatabaseConfigBuilder {
private:
    DatabaseConfig config;

public:
    DatabaseConfigBuilder() {
        config.host = "localhost";
        config.port = 3306;
        config.timeout = 30;
    }

    DatabaseConfigBuilder& setHost(const std::string& h) {
        config.host = h;
        return *this;
    }

    DatabaseConfigBuilder& setPort(int p) {
        if (p < 1 || p > 65535) {
            throw std::invalid_argument("Port must be between 1 and 65535");
        }
        config.port = p;
        return *this;
    }

    DatabaseConfigBuilder& setLogin(const std::string& l) {
        config.login = l;
        return *this;
    }

    DatabaseConfigBuilder& setPassword(const std::string& p) {
        config.password = p;
        return *this;
    }

    DatabaseConfigBuilder& setDatabaseName(const std::string& name) {
        config.databaseName = name;
        return *this;
    }

    DatabaseConfigBuilder& enableSSL() {
        config.useSSL = true;
        return *this;
    }

    DatabaseConfigBuilder& setTimeout(int t) {
        config.timeout = t;
        return *this;
    }

    DatabaseConfig build() {
        if (config.password.empty()) {
            std::cout << "WARNING: Password is empty!\n";
        }
        return config;
    }
};

class Query {
private:
    std::string selectClause;
    std::string fromClause;
    std::string whereClause;
    std::string orderByClause;
    int limitValue;

public:
    Query() : limitValue(-1) {}

    friend class QueryBuilder;

    void print() const {
        std::cout << "SQL Query: SELECT " << selectClause << " FROM " << fromClause;
        if (!whereClause.empty()) std::cout << " WHERE " << whereClause;
        if (!orderByClause.empty()) std::cout << " ORDER BY " << orderByClause;
        if (limitValue != -1) std::cout << " LIMIT " << limitValue;
        std::cout << "\n\n";
    }
};

class QueryBuilder {
private:
    Query query;

public:
    QueryBuilder& select(const std::string& fields) {
        query.selectClause = fields;
        return *this;
    }

    QueryBuilder& from(const std::string& table) {
        query.fromClause = table;
        return *this;
    }

    QueryBuilder& where(const std::string& condition) {
        query.whereClause = condition;
        return *this;
    }

    QueryBuilder& orderBy(const std::string& field) {
        query.orderByClause = field;
        return *this;
    }

    QueryBuilder& limit(int l) {
        query.limitValue = l;
        return *this;
    }

    Query build() {
        if (query.selectClause.empty() || query.fromClause.empty()) {
            throw std::invalid_argument("Query must have SELECT and FROM clauses");
        }
        return query;
    }
};

class Computer {
private:
    std::string CPU;
    std::string GPU;
    std::string RAM;
    std::string SSD;
    std::string HDD;
    bool WiFi;
    bool Bluetooth;
    bool waterCooling;

public:
    Computer() = default;

    friend class ComputerBuilder;

    void print() const {
        std::cout << "Computer Configuration:\n";
        std::cout << "CPU: " << CPU << ", GPU: " << GPU << ", RAM: " << RAM << "\n";
        std::cout << "SSD: " << SSD << ", HDD: " << HDD << "\n";
        std::cout << "WiFi: " << (WiFi ? "Yes" : "No") << ", Bluetooth: " << (Bluetooth ? "Yes" : "No");
        std::cout << ", Water Cooling: " << (waterCooling ? "Yes" : "No") << "\n\n";
    }
};

class ComputerBuilder {
private:
    Computer computer;

public:
    ComputerBuilder& setCPU(const std::string& cpu) {
        computer.CPU = cpu;
        return *this;
    }

    ComputerBuilder& setGPU(const std::string& gpu) {
        computer.GPU = gpu;
        return *this;
    }

    ComputerBuilder& setRAM(const std::string& ram) {
        computer.RAM = ram;
        return *this;
    }

    ComputerBuilder& setSSD(const std::string& ssd) {
        computer.SSD = ssd;
        return *this;
    }

    ComputerBuilder& setHDD(const std::string& hdd) {
        computer.HDD = hdd;
        return *this;
    }

    ComputerBuilder& enableWiFi() {
        computer.WiFi = true;
        return *this;
    }

    ComputerBuilder& enableBluetooth() {
        computer.Bluetooth = true;
        return *this;
    }

    ComputerBuilder& enableWaterCooling() {
        computer.waterCooling = true;
        return *this;
    }

    Computer build() { return computer; }
};

class ComputerDirector {
public:
    static Computer buildOfficePC() {
        return ComputerBuilder()
            .setCPU("Intel i3")
            .setGPU("Integrated")
            .setRAM("8GB")
            .setSSD("256GB")
            .setHDD("1TB")
            .enableWiFi()
            .build();
    }

    static Computer buildGamingPC() {
        return ComputerBuilder()
            .setCPU("AMD Ryzen 7")
            .setGPU("NVIDIA RTX 4080")
            .setRAM("32GB")
            .setSSD("1TB NVMe")
            .setHDD("2TB")
            .enableWiFi()
            .enableBluetooth()
            .enableWaterCooling()
            .build();
    }

    static Computer buildServer() {
        return ComputerBuilder()
            .setCPU("Dual Xeon")
            .setGPU("None")
            .setRAM("128GB")
            .setSSD("4x1TB NVMe RAID")
            .setHDD("8x4TB RAID")
            .enableWiFi(false)
            .enableBluetooth(false)
            .build();
    }
};

class UserProfile {
private:
    std::string login;
    std::string email;
    std::string phone;
    std::string city;
    int age;
    std::string role;
    bool isVerified;

public:
    UserProfile() : age(0), isVerified(false), role("user") {}

    friend class UserProfileBuilder;

    void print() const {
        std::cout << "User Profile:\n";
        std::cout << "Login: " << login << ", Email: " << email << ", Phone: " << phone << "\n";
        std::cout << "City: " << city << ", Age: " << age << ", Role: " << role;
        std::cout << ", Verified: " << (isVerified ? "Yes" : "No") << "\n\n";
    }
};

class UserProfileBuilder {
private:
    UserProfile profile;

public:
    UserProfileBuilder& setLogin(const std::string& l) {
        profile.login = l;
        return *this;
    }

    UserProfileBuilder& setEmail(const std::string& e) {
        profile.email = e;
        return *this;
    }

    UserProfileBuilder& setPhone(const std::string& p) {
        profile.phone = p;
        return *this;
    }

    UserProfileBuilder& setCity(const std::string& c) {
        profile.city = c;
        return *this;
    }

    UserProfileBuilder& setAge(int a) {
        profile.age = a;
        return *this;
    }

    UserProfileBuilder& setRole(const std::string& r) {
        profile.role = r;
        return *this;
    }

    UserProfileBuilder& verify() {
        profile.isVerified = true;
        return *this;
    }

    UserProfile build() {
        if (profile.email.find('@') == std::string::npos) {
            throw std::invalid_argument("Invalid email format");
        }
        return profile;
    }
};

class GameLevel {
private:
    std::string name;
    std::string difficulty;
    std::vector<std::string> enemies;
    std::vector<std::string
> items;
    bool hasBoss;
    std::string weatherEffect;

public:
    GameLevel() : hasBoss(false) {}

    friend class GameLevelBuilder;

    void print() const {
        std::cout << "Level: " << name << " (Difficulty: " << difficulty << ")\n";
        std::cout << "Enemies: ";
        for (const auto& e : enemies) std::cout << e << " ";
        std::cout << "\nItems: ";
        for (const auto& i : items) std::cout << i << " ";
        std::cout << "\nBoss: " << (hasBoss ? "Yes" : "No") << ", Weather: " << weatherEffect << "\n\n";
    }
};

class GameLevelBuilder {
private:
    GameLevel level;

public:
    GameLevelBuilder& setName(const std::string& n) {
        level.name = n;
        return *this;
    }

    GameLevelBuilder& setDifficulty(const std::string& d) {
        level.difficulty = d;
        return *this;
    }

    GameLevelBuilder& addEnemy(const std::string& enemy) {
        level.enemies.push_back(enemy);
        return *this;
    }

    GameLevelBuilder& addItem(const std::string& item) {
        level.items.push_back(item);
        return *this;
    }

    GameLevelBuilder& enableBoss() {
        level.hasBoss = true;
        return *this;
    }

    GameLevelBuilder& setWeatherEffect(const std::string& weather) {
        level.weatherEffect = weather;
        return *this;
    }

    GameLevel build() {
        if (level.name.empty()) {
            throw std::invalid_argument("Level name cannot be empty");
        }
        return level;
    }
};

class Notification {
private:
    std::string recipient;
    std::string title;
    std::string text;
    std::string channel;
    int priority;
    bool requiresConfirmation;

public:
    Notification() : priority(1), requiresConfirmation(false) {}

    friend class NotificationBuilder;

    void print() const {
        std::cout << "Notification to: " << recipient << "\n";
        std::cout << "Title: " << title << ", Text: " << text << "\n";
        std::cout << "Channel: " << channel << ", Priority: " << priority;
        std::cout << ", Requires confirmation: " << (requiresConfirmation ? "Yes" : "No") << "\n\n";
    }
};

class NotificationBuilder {
private:
    Notification notification;

public:
    NotificationBuilder& setRecipient(const std::string& r) {
        notification.recipient = r;
        return *this;
    }

    NotificationBuilder& setTitle(const std::string& t) {
        notification.title = t;
        return *this;
    }

    NotificationBuilder& setText(const std::string& t) {
        notification.text = t;
        return *this;
    }

    NotificationBuilder& setChannel(const std::string& c) {
        if (c == "email" || c == "sms" || c == "push") {
            notification.channel = c;
        } else {
            throw std::invalid_argument("Invalid channel. Use: email, sms, push");
        }
        return *this;
    }

    NotificationBuilder& setPriority(int p) {
        notification.priority = p;
        return *this;
    }

    NotificationBuilder& requireConfirmation() {
        notification.requiresConfirmation = true;
        return *this;
    }

    Notification build() {
        if (notification.recipient.empty() || notification.text.empty()) {
            throw std::invalid_argument("Recipient and text cannot be empty");
        }
        return notification;
    }
};

class Order {
private:
    std::string customerName;
    std::vector<std::string> products;
    std::string deliveryMethod;

public:
    Order() = default;

    friend class OrderBuilder;

    void print() const {
        std::cout << "Order for: " << customerName << "\nProducts: ";
        for (const auto& p : products) std::cout << p << " ";
        std::cout << "\nDelivery: " << deliveryMethod << "\n\n";
    }
};

class OrderBuilder {
private:
    Order order;

public:
    OrderBuilder& setCustomerName(const std::string& name) {
        order.customerName = name;
        return *this;
    }

    OrderBuilder& addProduct(const std::string& product) {
        order.products.push_back(product);
        return *this;
    }

    OrderBuilder& setDeliveryMethod(const std::string& method) {
        order.deliveryMethod = method;
        return *this;
    }

    Order build() { return order; }
};

class PaymentService {
public:
    static void processPayment(const Order& order) {
        std::cout << "Processing payment for order: " << order.customerName << "\n";
    }
};

class DeliveryService {
public:
    static void arrangeDelivery(const Order& order) {
        std::cout << "Arranging delivery for: " << order.deliveryMethod << "\n";
    }
};

class NotificationService {
public:
    static void sendNotification(const Order& order) {
        std::cout << "Sending notification to: " << order.customerName << "\n";
    }
};

class OrderFacade {
public:
    static void placeOrder(const Order& order) {
        PaymentService::processPayment(order);
        DeliveryService::arrangeDelivery(order);
        NotificationService::sendNotification(order);
        std::cout << "Order placed successfully!\n\n";
    }
};

class OrderWithDiscount {
private:
    double totalAmount;
    std::unique_ptr<class DiscountStrategy> strategy;

public:
    OrderWithDiscount() : totalAmount(0.0) {}

    friend class OrderWithDiscountBuilder;

public:
    void setTotalAmount(double amount) { totalAmount = amount; }
    void setStrategy(std::unique_ptr<DiscountStrategy> s) { strategy = std::move(s); }
    double getFinalAmount() const { return strategy ? strategy->apply(totalAmount) : totalAmount; }

    void print() const {
        std::cout << "Order total: " << totalAmount << ", Final amount: " << getFinalAmount() << "\n\n";
    }
};

class DiscountStrategy {
public:
    virtual ~DiscountStrategy() = default;
    virtual double apply(double amount) const = 0;
};

class NoDiscount : public DiscountStrategy {
public:
    double apply(double amount) const override { return amount; }
};

class PercentDiscount : public DiscountStrategy {
private:
    double percent;
public:
    PercentDiscount(double p) : percent(p) {}
    double apply(double amount) const override {
        return amount * (1 - percent / 100);
    }
};

class FixedDiscount : public DiscountStrategy {
private:
    double discount;
public:
    FixedDiscount(double d) : discount(d) {}
    double apply(double amount) const override {
        return std::max(0.0, amount - discount);
    }
};

class OrderWithDiscountBuilder {
private:
    OrderWithDiscount order;

public:
    OrderWithDiscountBuilder& setTotalAmount(double amount) {
        order.setTotalAmount(amount);
        return *this;
    }

    OrderWithDiscountBuilder& setStrategy(std::unique_ptr<DiscountStrategy> strategy) {
        order.setStrategy(std::move(strategy));
        return *this;
    }

    OrderWithDiscount build() { return order; }
};

class CharacterPrototype {
private:
    std::string name;
    std::string characterClass;
    int health;

public:
    CharacterPrototype() = default;
    CharacterPrototype(const std::string& n, const std::string& cls, int h)
        : name(n), characterClass(cls), health(h) {}

    virtual ~CharacterPrototype() = default;

    virtual CharacterPrototype* clone() const {
        return new CharacterPrototype(*this);
    }

    void setName(const std::string& n) { name = n; }
    void setWeapon(const std::string& w) { weapon = w; }

    void print() const {
        std::cout << "Character: " << name << " (" << characterClass << "), Health: " << health;
        std::cout << ", Weapon: " << weapon << "\n";
    }

private:
    std::string weapon;
};

class WarriorPrototype : public CharacterPrototype {
public:
    WarriorPrototype() : CharacterPrototype("Warrior", "Warrior", 150) {
        setWeapon("Sword");
    }

    CharacterPrototype* clone() const override {
        return new WarriorPrototype(*this);
    }
};

class Burger {
protected:
    std::string description = "Basic Burger";
    double cost = 100.0;

public:
    virtual std::string getDescription() const { return description; }
    virtual double getCost() const { return cost; }
    virtual ~Burger() = default;
};

class BurgerBuilder {
private:
    Burger* burger;

public:
    BurgerBuilder() { burger = new Burger(); }

    BurgerBuilder& addCheese() {
        burger = new CheeseDecorator(burger);
        return *this;
    }

    BurgerBuilder& addBacon() {
        burger = new BaconDecorator(burger);
        return *this;
    }

    BurgerBuilder& addSauce() {
        burger = new SauceDecorator(burger);
        return *this;
    }

    Burger* build() { return burger; }
};

class BurgerDecorator : public Burger {
protected:
    Burger* wrappedBurger;

public:
    BurgerDecorator(Burger* burger) : wrappedBurger(burger) {}
    ~BurgerDecorator() override { delete wrappedBurger; }
};

class CheeseDecorator : public BurgerDecorator {
public:
    CheeseDecorator(Burger* burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return wrappedBurger->getDescription() + ", Cheese";
    }

    double getCost() const override {
        return wrappedBurger->getCost() + 20.0;
    }
};

class BaconDecorator : public BurgerDecorator {
public:
    BaconDecorator(Burger* burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return wrappedBurger->getDescription() + ", Bacon";
    }

    double getCost() const override {
        return wrappedBurger->getCost() + 30.0;
    }
};

class SauceDecorator : public BurgerDecorator {
public:
    SauceDecorator(Burger* burger) : BurgerDecorator(burger) {}

    std::string getDescription() const override {
        return wrappedBurger->getDescription() + ", Sauce";
    }

    double getCost() const override {
        return wrappedBurger->getCost() + 10.0;
    }
};

class RegistrationForm {
private:
    std::string login;
    std::string password;
    std::string email;
    int age;
    bool isValid;

public:
    RegistrationForm() : age(0), isValid(false) {}

    friend class RegistrationFormBuilder;

    bool getValidationStatus() const { return isValid; }

    void print() const {
        if (!isValid) {
            std::cout << "Registration form is invalid!\n\n";
            return;
        }
        std::cout << "Registration successful:\n";
        std::cout << "Login: " << login << ", Email: " << email << ", Age: " << age << "\n\n";
    }
};

class RegistrationFormBuilder {
private:
    RegistrationForm form;

public:
    RegistrationFormBuilder& setLogin(const std::string& l) {
        form.login = l;
        return *this;
    }

    RegistrationFormBuilder& setPassword(const std::string& p) {
        form.password = p;
        return *this;
    }

    RegistrationFormBuilder& setConfirmPassword(const std::string& cp) {
        form.confirmPassword = cp;
        return *this;
    }

    RegistrationFormBuilder& setEmail(const std::string& e) {
        form.email = e;
        return *this;
    }

    RegistrationFormBuilder& setAge(int a) {
        form.age = a;
        return *this;
    }

    RegistrationForm build() {
        bool valid = true;
        if (form.password != form.confirmPassword) {
            std::cout << "Error: Passwords do not match!\n";
            valid = false;
        }
        if (form.age < 14) {
            std::cout << "Error: Age must be at least 14!\n";
            valid = false;
        }
        if (form.email.find('@') == std::string::npos) {
            std::cout << "Error: Invalid email format!\n";
            valid = false;
        }
        form.isValid = valid;
        return form;
    }

private:
    std::string confirmPassword;
};

class Report {
private:
    std::string title;
    std::string author;
    std::string date;
    std::vector<std::string> sections;
    std::vector<std::string> tables;
    std::vector<std::string> conclusions;

public:
    Report() = default;

    friend class ReportBuilder;

    void print() const {
        std::cout << "Report: " << title << " by " << author << " (" << date << ")\n";
        std::cout << "Sections: ";
        for (const auto& s : sections) std::cout << s << " | ";
        std::cout << "\nTables: ";
        for (const auto& t : tables) std::cout << t << " | ";
        std::cout << "\nConclusions: ";
        for (const auto& c : conclusions) std::cout << c << " | ";
        std::cout << "\n\n";
    }
};

class ReportBuilder {
private:
    Report report;

public:
    ReportBuilder& setTitle(const std::string& t) {
        report.title = t;
        return *this;
    }

    ReportBuilder& setAuthor(const std::string& a) {
        report.author = a;
        return *this;
    }

    ReportBuilder& setDate(const std::string& d) {
        report.date = d;
        return *this;
    }

    ReportBuilder& addSection(const std::string& section) {
        report.sections.push_back(section);
        return *this;
    }

    ReportBuilder& addTable(const std::string& table) {
        report.tables.push_back(table);
        return *this;
    }

    ReportBuilder& addConclusion(const std::string& conclusion) {
        report.conclusions.push_back(conclusion);
        return *this;
    }

    Report build() { return report; }
};

class ReportDirector {
public:
    static Report createShortReport() {
        return ReportBuilder()
            .setTitle("Short Report")
            .setAuthor("System")
            .setDate("2024-01-01")
            .addSection("Summary")
            .addConclusion("Main points covered")
            .build();
    }

    static Report createFullReport() {
        return ReportBuilder()
            .setTitle("Full Report")
            .setAuthor("System")
            .setDate("2024-01-01")
            .addSection("Introduction")
            .addSection("Methodology")
            .addSection("Results")
            .addTable("Data Analysis")
            .addConclusion("Conclusions based on comprehensive analysis")
            .build();
    }

    static Report createTechnicalReport() {
        return ReportBuilder()
            .setTitle("Technical Report")
            .setAuthor("System")
            .setDate("2024-01-01")
            .addSection("Architecture")
            .addSection("Implementation")
            .addSection("Performance")
            .addTable("Benchmark Results")
            .addTable("Memory Usage")
            .addConclusion("System meets technical requirements")
            .build();
    }
};
