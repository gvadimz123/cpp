#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Implementor {
public:
    virtual void operation() = 0;
    virtual ~Implementor() = default;
};

class ConcreteImplementorA : public Implementor {
public:
    void operation() override {
        std::cout << "ConcreteImplementorA operation\n";
    }
};

class ConcreteImplementorB : public Implementor {
public:
    void operation() override {
        std::cout << "ConcreteImplementorB operation\n";
    }
};

class Abstraction {
protected:
    std::shared_ptr<Implementor> implementor;
public:
    Abstraction(std::shared_ptr<Implementor> imp) : implementor(imp) {}
    virtual void operation() {
        implementor->operation();
    }
};

class RefinedAbstractionA : public Abstraction {
public:
    RefinedAbstractionA(std::shared_ptr<Implementor> imp) : Abstraction(imp) {}
    void operation() override {
        std::cout << "RefinedAbstractionA: ";
        Abstraction::operation();
    }
};

class RefinedAbstractionB : public Abstraction {
public:
    RefinedAbstractionB(std::shared_ptr<Implementor> imp) : Abstraction(imp) {}
    void operation() override {
        std::cout << "RefinedAbstractionB: ";
        Abstraction::operation();
    }
};

class Renderer {
public:
    virtual std::string renderCircle(float radius) = 0;
    virtual std::string renderRectangle(float width, float height) = 0;
    virtual ~Renderer() = default;
};

class RasterRenderer : public Renderer {
public:
    std::string renderCircle(float radius) override {
        return "Raster: Drawing circle with radius " + std::to_string(radius);
    }
    std::string renderRectangle(float width, float height) override {
        return "Raster: Drawing rectangle " + std::to_string(width) + "x" + std::to_string(height);
    }
};

class VectorRenderer : public Renderer {
public:
    std::string renderCircle(float radius) override {
        return "Vector: Drawing circle with radius " + std::to_string(radius);
    }
    std::string renderRectangle(float width, float height) override {
        return "Vector: Drawing rectangle " + std::to_string(width) + "x" + std::to_string(height);
    }
};

class Shape {
protected:
    std::shared_ptr<Renderer> renderer;
public:
    Shape(std::shared_ptr<Renderer> r) : renderer(r) {}
    virtual std::string draw() = 0;
};

class Circle : public Shape {
    float radius;
public:
    Circle(std::shared_ptr<Renderer> r, float rad) : Shape(r), radius(rad) {}
    std::string draw() override {
        return renderer->renderCircle(radius);
    }
};

class Rectangle : public Shape {
    float width, height;
public:
    Rectangle(std::shared_ptr<Renderer> r, float w, float h) : Shape(r), width(w), height(h) {}
    std::string draw() override {
        return renderer->renderRectangle(width, height);
    }
};

void demonstrateRuntimeChange() {
    auto raster = std::make_shared<RasterRenderer>();
    auto vector = std::make_shared<VectorRenderer>();

    Circle circle(raster, 5.0f);
    std::cout << circle.draw() << "\n";

    circle.renderer = vector;
    std::cout << circle.draw() << "\n";
}

// 4. Ошибка проектирования — не реализуем через наследование (описываем проблемы)
// Проблемы подхода с наследованием:
// - Комбинаторный взрыв классов (N форм × M рендереров = N×M классов)
// - Нарушение принципа открытости/закрытости (при добавлении нового рендерера нужно создавать N новых классов)
// - Дублирование кода
// - Жёсткая связь между абстракцией и реализацией

// 5. Добавление новой реализации
class OpenGLRenderer : public Renderer {
public:
    std::string renderCircle(float radius) override {
        return "OpenGL: Drawing circle with radius " + std::to_string(radius);
    }
    std::string renderRectangle(float width, float height) override {
        return "OpenGL: Drawing rectangle " + std::to_string(width) + "x" + std::to_string(height);
    }
};

public:
    virtual void powerOn() = 0;
    virtual void powerOff() = 0;
    virtual ~Device() = default;
};

class TV : public Device {
public:
    void powerOn() override { std::cout << "TV is ON\n"; }
    void powerOff() override { std::cout << "TV is OFF\n"; }
};

class Projector : public Device {
public:
    void powerOn() override { std::cout << "Projector is ON\n"; }
    void powerOff() override { std::cout << "Projector is OFF\n"; }
};

class Radio : public Device {
public:
    void powerOn() override { std::cout << "Radio is ON\n"; }
    void powerOff() override { std::cout << "Radio is OFF\n"; }
};

class Remote {
protected:
    std::shared_ptr<Device> device;
public:
    Remote(std::shared_ptr<Device> d) : device(d) {}
    virtual void togglePower() {
    }
};

class SmartRemote : public Remote {
public:
    SmartRemote(std::shared_ptr<Device> d) : Remote(d) {}
    void togglePower() override {
        device->powerOn();
        std::cout << "Smart remote: Additional features activated\n";
    }
};

class VoiceRemote : public Remote {
public:
    VoiceRemote(std::shared_ptr<Device> d) : Remote(d) {}
    void togglePower() override {
        std::cout << "Voice command received: ";
        device->powerOn();
    }
};

class NotificationSender {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~NotificationSender() = default;
};

class EmailSender : public NotificationSender {
public:
    void send(const std::string& message) override {
        std::cout << "Email sent: " << message << "\n";
    }
};

class SMSSender : public NotificationSender {
public:
    void send(const std::string& message) override {
        std::cout << "SMS sent: " << message << "\n";
    }
};

class PushSender : public NotificationSender {
public:
    void send(const std::string& message) override {
        std::cout << "Push notification sent: " << message << "\n";
    }
};

class Notification {
protected:
    std::shared_ptr<NotificationSender> sender;
    std::string content;
public:
    Notification(std::shared_ptr<NotificationSender> s, const std::string& c)
        : sender(s), content(c) {}
    virtual void notify() {
        sender->send(content);
    }
};

class UrgentNotification : public Notification {
public:
    UrgentNotification(std::shared_ptr<NotificationSender> s, const std::string& c)
        : Notification(s, c) {}
    void notify() override {
        std::cout << "[URGENT] ";
        Notification::notify();
    }
};

class MarketingNotification : public Notification {
public:
    MarketingNotification(std::shared_ptr<NotificationSender> s, const std::string& c)
        : Notification(s, c) {}
    void notify() override {
        std::cout << "[MARKET] ";
class MarketingNotification : public Notification {
public:
    MarketingNotification(std::shared_ptr<NotificationSender> s, const std::string& c)
        : Notification(s, c) {}
    void notify() override {
        std::cout << "[MARKETING] ";
        Notification::notify();
    }
};

class WeaponEffect {
public:
    virtual std::string applyEffect(const std::string& target) = 0;
    virtual ~WeaponEffect() = default;
};

class FireEffect : public WeaponEffect {
public:
    std::string applyEffect(const std::string& target) override {
        return "Fire effect applied to " + target + " (burning damage)";
    }
};

class IceEffect : public WeaponEffect {
public:
    std::string applyEffect(const std::string& target) override {
        return "Ice effect applied to " + target + " (slowing effect)";
    }
};

class PoisonEffect : public WeaponEffect {
public:
    std::string applyEffect(const std::string& target) override {
        return "Poison effect applied to " + target + " (damage over time)";
    }
};

class Weapon {
protected:
    std::shared_ptr<WeaponEffect> effect;
    std::string name;
public:
    Weapon(std::shared_ptr<WeaponEffect> e, const std::string& n)
        : effect(e), name(n) {}
    virtual void attack(const std::string& target) {
        std::cout << name << " attacks " << target << ": ";
        std::cout << effect->applyEffect(target) << "\n";
    }
};

class Sword : public Weapon {
public:
    Sword(std::shared_ptr<WeaponEffect> e) : Weapon(e, "Sword") {}
};

class Bow : public Weapon {
public:
    Bow(std::shared_ptr<WeaponEffect> e) : Weapon(e, "Bow") {}
};

class Staff : public Weapon {
public:
    Staff(std::shared_ptr<WeaponEffect> e) : Weapon(e, "Staff") {}
};

class DatabaseDriver {
public:
    virtual void connect() = 0;
    virtual void query(const std::string& sql) = 0;
    virtual ~DatabaseDriver() = default;
};

class MySQLDriver : public DatabaseDriver {
public:
    void connect() override { std::cout << "MySQL connected\n"; }
    void query(const std::string& sql) override {
        std::cout << "MySQL query: " << sql << "\n";
    }
};

class PostgreSQLDriver : public DatabaseDriver {
public:
    void connect() override { std::cout << "PostgreSQL connected\n"; }
    void query(const std::string& sql) override {
        std::cout << "PostgreSQL query: " << sql << "\n";
    }
};

class SQLiteDriver : public DatabaseDriver {
public:
    void connect() override { std::cout << "SQLite connected\n"; }
    void query(const std::string& sql) override {
        std::cout << "SQLite query: " << sql << "\n";
    }
};

class Repository {
protected:
    std::shared_ptr<DatabaseDriver> driver;
public:
    Repository(std::shared_ptr<DatabaseDriver> d) : driver(d) {}
    virtual void save() = 0;
};

class UserRepository : public Repository {
public:
    UserRepository(std::shared_ptr<DatabaseDriver> d) : Repository(d) {}
    void save() override {
        driver->connect();
        driver->query("INSERT INTO users ...");
    }
};

class ProductRepository : public Repository {
public:
    ProductRepository(std::shared_ptr<DatabaseDriver> d) : Repository(d) {}
    void save() override {
        driver->connect();
        driver->query("INSERT INTO products ...");
    }
};

class FileSystem {
public:
    virtual void saveFile(const std::string& filename, const std::string& content) = 0;
    virtual ~FileSystem() = default;
};

class LocalStorage : public FileSystem {
public:
    void saveFile(const std::string& filename, const std::string& content) override {
        std::cout << "LocalStorage: Saving " << filename << " (" << content.size() << " bytes)\n";
    }
};

class CloudStorage : public FileSystem {
public:
    void saveFile(const std::string& filename, const std::string& content) override {
        std::cout << "CloudStorage: Uploading " << filename << " to cloud\n";
    }
};

class File {
protected:
    std::shared_ptr<FileSystem> storage;
    std::string name;
    std::string content;
public:
    File(std::shared_ptr<FileSystem> s, const std::string& n, const std::string& c)
        : storage(s), name(n), content(c) {}
    virtual void save() {
        storage->saveFile(name, content);
    }
};

class TextFile : public File {
public:
    TextFile(std::shared_ptr<FileSystem> s, const std::string& n, const std::string& c)
        : File(s, n, c) {}
};

class ImageFile : public File {
public:
    ImageFile(std::shared_ptr<FileSystem> s, const std::string& n, const std::string& c)
        : File(s, n, c) {}
};

class VideoFile : public File {
public:
    VideoFile(std::shared_ptr<FileSystem> s, const std::string& n, const std::string& c)
        : File(s, n, c) {}
};

class Renderer3D {
public:
    virtual std::string renderSprite(const std::string& name) = 0;
    virtual std::string renderModel(const std::string& name) = 0;
    virtual std::string renderUIElement(const std::string& name) = 0;
    virtual ~Renderer3D() = default;
};

class OpenGLRenderer : public Renderer3D {
public:
    std::string renderSprite(const std::string& name) override {
        return "OpenGL: Rendering sprite " + name;
    }
    std::string renderModel(const std::string& name) override {
        return "OpenGL: Rendering 3D model " + name;
    }
    std::string renderUIElement(const std::string& name) override {
        return "OpenGL: Rendering UI element " + name;
    }
};

class VulkanRenderer : public Renderer3D {
public:
    std::string renderSprite(const std::string& name) override {
        return "Vulkan: Rendering sprite " + name;
    }
    std::string renderModel(const std::string& name) override {
        return "Vulkan: Rendering 3D model " + name;
    }
    std::string renderUIElement(const std::string& name) override {
        return "Vulkan: Rendering UI element " + name;
    }
};

class DirectXRenderer : public Renderer3D {
public:
    std::string renderSprite(const std::string& name) override {
        return "DirectX: Rendering sprite " + name;
    }
    std::string renderModel(const std::string& name) override {
        return "DirectX: Rendering 3D model " + name;
    }
    std::string renderUIElement(const std::string& name) override {
        return "DirectX: Rendering UI element " + name;
    }
};

class GameObject {
protected:
    std::shared_ptr<Renderer3D> renderer;
    std::string name;
public:
    GameObject(std::shared_ptr<Renderer3D> r, const std::string& n)
        : renderer(r), name(n) {}
    virtual std::string render() = 0;
};

class Sprite : public GameObject {
public:
    Sprite(std::shared_ptr<Renderer3D> r, const std::string& n) : GameObject(r, n) {}
    std::string render() override { return renderer->renderSprite(name); }
};

class Model : public GameObject {
public:
    Model(std::shared_ptr<Renderer3D> r, const std::string& n) : GameObject(r, n) {}
    std::string render() override { return renderer->renderModel(name); }
};

class UIElement : public GameObject {
public:
    UIElement(std::shared_ptr<Renderer3D> r, const std::string& n) : GameObject(r, n) {}
    std::string render() override { return renderer->renderUIElement(name); }
};

class PaymentProvider {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~PaymentProvider() = default;
};

class PayPalProvider : public PaymentProvider {
public:
    void processPayment(double amount) override {
        std::cout << "PayPal: Processing payment of $" << amount << "\n";
    }
};

class StripeProvider : public PaymentProvider {
public:
    void processPayment(double amount) override {
        std::cout << "Stripe: Processing payment of $" << amount << "\n";
    }
};

class CryptoProvider : public PaymentProvider {
public:
    void processPayment(double amount) override {
        std::cout << "Crypto: Processing payment of " << amount << " BTC\n";
    }
};

class Payment {
protected:
    std::shared_ptr<PaymentProvider> provider;
    double amount;
public:
    Payment(std::shared_ptr<PaymentProvider> p, double a)
        : provider(p), amount(a) {}
    virtual void pay() = 0;
};

class RegularPayment : public Payment {
public:
    RegularPayment(std::shared_ptr<PaymentProvider> p, double a) : Payment(p, a) {}
    void pay() override { provider->processPayment(amount); }
};

class SubscriptionPayment : public Payment {
public:
    SubscriptionPayment(std::shared_ptr<PaymentProvider> p, double a) : Payment(p, a) {}
    void pay() override {
        std::cout << "Subscription: ";
        provider->processPayment(amount);
    }
};

class CryptoPayment : public Payment {
public:
    CryptoPayment(std::shared_ptr<PaymentProvider> p, double a) : Payment(p, a) {}
    void pay() override {
        std::cout << "Crypto transaction: ";
        provider->processPayment(amount);
    }
};

class LogWriter {
public:
    virtual void write(const std::string& message) = 0;
    virtual ~LogWriter() = default;
};

class FileWriter : public LogWriter {
public:
    void write(const std::string& message) override {
        std::cout << "[FILE] " << message << "\n";
    }
};

class ConsoleWriter : public LogWriter {
public:
    void write(const std::string& message) override {
        std::cout << "[CONSOLE] " << message << "\n";
    }
};

class NetworkWriter : public LogWriter {
public:
    void write(const std::string& message) override {
        std::cout << "[NETWORK] " << message << "\n";
    }
};

class Logger {
protected:
    std::shared_ptr<LogWriter> writer;
    std::string level;
public:
    Logger(std::shared_ptr<LogWriter> w, const std::string& l)
        : writer(w), level(l) {}
    virtual void log(const std::string& message) {
        writer->write("[" + level + "] " + message);
    }
};

class ErrorLogger : public Logger {
public:
    ErrorLogger(std::shared_ptr<LogWriter> w) : Logger(w, "ERROR") {}
};

class DebugLogger : public Logger {
public:
    DebugLogger(std::shared_ptr<LogWriter> w) : Logger(w, "DEBUG") {}
};

class SecurityLogger : public Logger {
public:
    SecurityLogger(std::shared_ptr<LogWriter> w) : Logger(w, "SECURITY") {}
};

class AIBehavior {
public:
    virtual std::string act(const std::string& npcName) = 0;
    virtual ~AIBehavior() = default;
};

class AggressiveAI : public AIBehavior {
public:
    std::string act(const std::string& npcName) override {
        return npcName + " attacks aggressively!";
    }
};

class PassiveAI : public AIBehavior {
public:
    std::string act(const std::string& npcName) override {
        return npcName + " stands calmly.";
    }
};

class TraderAI : public AIBehavior {
public:
    std::string act(const std::string& npcName) override {
        return npcName + " offers goods for sale.";
    }
};

class NPC {
protected:
    std::shared_ptr<AIBehavior> ai;
    std::string name;
public:
    NPC(std::shared_ptr<AIBehavior> a, const std::string& n)
        : ai(a), name(n) {}
    virtual void update() {
        std::cout << ai->act(name) << "\n";
    }
};

class Merchant : public NPC {
public:
    Merchant(std::shared_ptr<AIBehavior> a, const std::string& n) : NPC(a, n) {}
};

class Guard : public NPC {
public:
    Guard(std::shared_ptr<AIBehavior> a, const std::string& n) : NPC(a, n) {}
};

class Healer : public NPC {
public:
    Healer(std::shared_ptr<AIBehavior> a, const std::string& n) : NPC(a, n) {}
};

class MediaEngine {
public:
    virtual void play(const std::string& file) = 0;
    virtual ~MediaEngine() = default;
};

class FFmpegEngine : public MediaEngine {
public:
    void play(const std::string& file) override {
        std::cout << "FFmpeg: Playing " << file << "\n";
    }
};

class VLCMediaEngine : public MediaEngine {
public:
    void play(const std::string& file) override {
        std::cout << "VLC: Playing " << file << "\n";
    }
};

class MediaPlayer {
protected:
    std::shared_ptr<MediaEngine> engine;
public:
    MediaPlayer(std::shared_ptr<MediaEngine> e) : engine(e) {}
    virtual void play(const std::string& file) = 0;
};

class AudioPlayer : public MediaPlayer {
public:
    AudioPlayer(std::shared_ptr<MediaEngine> e) : MediaPlayer(e) {}
    void play(const std::string& file) override {
        std::cout << "AudioPlayer: ";
        engine->play(file);
    }
};

class VideoPlayer : public MediaPlayer {
public:
    VideoPlayer(std::shared_ptr<MediaEngine> e) : MediaPlayer(e) {}
    void play(const std::string& file) override {
        std::cout << "VideoPlayer: ";
        engine->play(file);
    }
};

class AttackStrategy {
public:
    virtual std::string attack(const std::string& weaponName, const std::string& target) = 0;
    virtual ~AttackStrategy() = default;
};

class MeleeAttack : public AttackStrategy {
public:
    std::string attack(const std::string& weaponName, const std::string& target) override {
        return weaponName + " performs melee attack on " + target;
    }
};

class RangeAttack : public AttackStrategy {
public:
    std::string attack(const std::string& weaponName, const std::string& target) override {
        return weaponName + " performs ranged attack on " + target;
    }
};

class CriticalAttack : public AttackStrategy {
public:
    std::string attack(const std::string& weaponName, const std::string& target) override {
        return weaponName + " performs critical attack on " + target + "! (x2 damage)";
    }
};

class Weapon {
protected:
    std::shared_ptr<AttackStrategy> strategy;
    std::string name;
public:
    Weapon(std::shared_ptr<AttackStrategy> s, const std::string& n)
        : strategy(s), name(n) {}
    virtual void attack(const std::string& target) {
        std::cout << strategy->attack(name, target) << "\n";
    }
    void setStrategy(std::shared_ptr<AttackStrategy> newStrategy) {
        strategy = newStrategy;
    }
};

class Sword : public Weapon {
public:
    Sword(std::shared_ptr<AttackStrategy> s) : Weapon(s, "Sword") {}
};

class Gun : public Weapon {
public:
    Gun(std::shared_ptr<AttackStrategy> s) : Weapon(s, "Gun") {}
};

class NotificationChannel {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~NotificationChannel() = default;
};

class Email : public NotificationChannel {
public:
    void send(const std::string& message) override {
        std::cout << "Email sent: " << message << "\n";
    }
};

class SMS : public NotificationChannel {
public:
    void send(const std::string& message) override {
        std::cout << "SMS sent: " << message << "\n";
    }
};

class NotificationDecorator : public NotificationChannel {
protected:
    std::shared_ptr<NotificationChannel> channel;
public:
    NotificationDecorator(std::shared_ptr<NotificationChannel> c) : channel(c) {}
};

class EncryptionDecorator : public NotificationDecorator {
public:
    EncryptionDecorator(std::shared_ptr<NotificationChannel> c)
        : NotificationDecorator(c) {}
    void send(const std::string& message) override {
        std::string encrypted = "ENCRYPTED:" + message;
        channel->send(encrypted);
    }
};

class LoggingDecorator : public NotificationDecorator {
public:
    LoggingDecorator(std::shared_ptr<NotificationChannel> c)
        : NotificationDecorator(c) {}
    void send(const std::string& message) override {
        std::cout << "[LOG] Sending notification: " << message << "\n";
        channel->send(message);
    }
};

class RendererFactory {
public:
    static std::shared_ptr<Renderer> create(const std::string& type) {
        if (type == "OpenGL") return std::make_shared<OpenGLRenderer>();
        if (type == "Vector") return std::make_shared<VectorRenderer>();
        if (type == "Raster") return std::make_shared<RasterRenderer>();
        return nullptr;
    }
};

class ModernNotification {
protected:
    std::shared_ptr<NotificationSender> sender;
    std::string content;
public:
    ModernNotification(std::shared_ptr<NotificationSender> s, const std::string& c)
        : sender(s), content(c) {}
    void notify() {
        sender->send(content);
    }
};

class MessageSender {
public:
    virtual void sendMessage(const std::string& content) = 0;
    virtual ~MessageSender() = default;
};

class TelegramSender : public MessageSender {
public:
    void sendMessage(const std::string& content) override {
        std::cout << "Telegram: Sending message - " << content << "\n";
    }
};

class WhatsAppSender : public MessageSender {
public:
    void sendMessage(const std::string& content) override {
        std::cout << "WhatsApp: Sending message - " << content << "\n";
    }
};

class DiscordSender : public MessageSender {
public:
    void sendMessage(const std::string& content) override {
        std::cout << "Discord: Sending message - " << content << "\n";
    }
};

class Message {
protected:
    std::shared_ptr<MessageSender> sender;
    std::string content;
public:
    Message(std::shared_ptr<MessageSender> s, const std::string& c)
        : sender(s), content(c) {}
    virtual void send() = 0;
};

class TextMessage : public Message {
public:
    TextMessage(std::shared_ptr<MessageSender> s, const std::string& c)
        : Message(s, c) {}
    void send() override {
        std::cout << "[TEXT] ";
        sender->sendMessage(content);
    }
};

class VoiceMessage : public Message {
public:
    VoiceMessage(std::shared_ptr<MessageSender> s, const std::string& c)
        : Message(s, c) {}
    void send() override {
        std::cout << "[VOICE] ";
        sender->sendMessage(content);
    }
};

class VideoMessage : public Message {
public:
    VideoMessage(std::shared_ptr<MessageSender> s, const std::string& c)
        : Message(s, c) {}
    void send() override {
        std::cout << "[VIDEO] ";
        sender->sendMessage(content);
    }
};

void demonstrateAllCombinations() {
    std::vector<std::shared_ptr<MessageSender>> senders = {
        std::make_shared<TelegramSender>(),
        std::make_shared<WhatsAppSender>(),
        std::make_shared<DiscordSender>()
    };

    std::vector<std::function<std::shared_ptr<Message>(std::shared_ptr<MessageSender>)>> messageCreators = {
        [](std::shared_ptr<MessageSender> s) {
            return std::make_shared<TextMessage>(s, "Hello!");
        },
        [](std::shared_ptr<MessageSender> s) {
            return std::make_shared<VoiceMessage>(s, "Voice message");
        },
        [](std::shared_ptr<MessageSender> s) {
            return std::make_shared<VideoMessage>(s, "Video content");
        }
    };

    int count = 0;
    for (auto& sender : senders) {
        for (auto& creator : messageCreators) {
            if (count >= 6) break;
            auto message = creator(sender);
            message->send();
            count++;
        }
        if (count >= 6) break;
    }
}

int main() {
    std::cout << "=== Демонстрация Bridge паттерна ===\n";

    demonstrateRuntimeChange();

    std::cout << "\n=== Устройства и пульты ===\n";
    auto tv = std::make_shared<TV>();
    auto smartRemote = std::make_shared<SmartRemote>(tv);
    smartRemote->togglePower();

    std::cout << "\n=== Уведомления ===\n";
    auto emailSender = std::make_shared<EmailSender>();
    auto urgentNotif = std::make_shared<UrgentNotification>(emailSender, "System alert!");
    urgentNotif->notify();

    std::cout << "\n=== Система сообщений (6 комбинаций) ===\n";
    demonstrateAllCombinations();

    return 0;
}
