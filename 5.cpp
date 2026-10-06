#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <functional>


class Subject {
public:
    virtual ~Subject() = default;
    virtual void request() = 0;
};

class RealSubject : public Subject {
public:
    void request() override {
        std::cout << "RealSubject: Handling request.\n";
    }
};

class Proxy : public Subject {
private:
    RealSubject* realSubject;
public:
    Proxy() : realSubject(nullptr) {}

    void request() override {
        std::cout << "Proxy: Before calling real subject.\n";
        if (!realSubject) {
            realSubject = new RealSubject();
        }
        realSubject->request();
        std::cout << "Proxy: After calling real subject.\n";
    }

    ~Proxy() { delete realSubject; }
};

class Image {
public:
    virtual ~Image() = default;
    virtual void display() = 0;
};

class RealImage : public Image {
private:
    std::string filename;
public:
    RealImage(const std::string& filename) : filename(filename) {
        loadFromDisk();
    }

    void loadFromDisk() {
        std::cout << "Loading " << filename << " from disk...\n";
    }

    void display() override {
        std::cout << "Displaying " << filename << "\n";
    }
};

class ImageProxy : public Image {
private:
    std::string filename;
    RealImage* realImage;
public:
    ImageProxy(const std::string& filename) : filename(filename), realImage(nullptr) {}

    void display() override {
        if (!realImage) {
            realImage = new RealImage(filename);
        }
        realImage->display();
    }

    ~ImageProxy() { delete realImage; }
};

class Database {
public:
    virtual ~Database() = default;
    virtual void query(const std::string& sql) = 0;
};

class RealDatabase : public Database {
public:
    void query(const std::string& sql) override {
        std::cout << "Executing: " << sql << "\n";
    }
};

class DatabaseProxy : public Database {
private:
    RealDatabase* realDatabase;
    bool isAdmin;
public:
    DatabaseProxy(bool isAdmin) : realDatabase(new RealDatabase()), isAdmin(isAdmin) {}

    void query(const std::string& sql) override {
        if (isAdmin) {
            std::cout << "Admin access granted.\n";
            realDatabase->query(sql);
        } else {
            std::cout << "Access denied: Not an administrator.\n";
        }
    }

    ~DatabaseProxy() { delete realDatabase; }
};

class LoggingProxy : public Subject {
private:
    RealSubject* realSubject;
    int callCount;
public:
    LoggingProxy() : realSubject(new RealSubject()), callCount(0) {}

    void request() override {
        auto start = std::chrono::high_resolution_clock::now();
        callCount++;
        std::cout << "Logging: Call #" << callCount
                  << " started at " << start.time_since_epoch().count() << "\n";

        realSubject->request();

        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Logging: Call ended at " << end.time_since_epoch().count()
                  << ", duration: "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                  << " microseconds\n";
    }

    ~LoggingProxy() { delete realSubject; }
};

class HeavyCalculator {
public:
    int compute(int x) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return x * x;
    }
};

class CachingProxy {
private:
    HeavyCalculator* calculator;
    std::unordered_map<int, int> cache;
public:
    CachingProxy() : calculator(new HeavyCalculator()) {}

    int compute(int x) {
        auto it = cache.find(x);
        if (it != cache.end()) {
            std::cout << "Cache hit for " << x << ": " << it->second << "\n";
            return it->second;
        }

        int result = calculator->compute(x);
        cache[x] = result;
        std::cout << "Computed " << x << "^2 = " << result << " (cached)\n";
        return result;
    }

    ~CachingProxy() { delete calculator; }
};

class API {
public:
    virtual ~API() = default;
    virtual bool call(const std::string& endpoint) = 0;
};

class RealAPI : public API {
public:
    bool call(const std::string& endpoint) override {
        std::cout << "Calling API endpoint: " << endpoint << "\n";
        return true;
    }
};

class APIGatewayProxy : public API {
private:
    RealAPI* realAPI;
    std::string token;
    int requestCount;
public:
    APIGatewayProxy(const std::string& token) : realAPI(new RealAPI()), token(token), requestCount(0) {}

    bool call(const std::string& endpoint) override {
        requestCount++;
        if (token != "valid_token") {
            std::cout << "API Gateway: Invalid token\n";
            return false;
        }
        if (requestCount > 5) {
            std::cout << "API Gateway: Rate limit exceeded\n";
            return false;
        }
        std::cout << "API Gateway: Logging request #" << requestCount << " to " << endpoint << "\n";
        return realAPI->call(endpoint);
    }

    ~APIGatewayProxy() { delete realAPI; }
};

class FileSystem {
public:
    virtual ~FileSystem() = default;
    virtual bool deleteFile(const std::string& path) = 0;
};

class RealFileSystem : public FileSystem {
public:
    bool deleteFile(const std::string& path) override {
        std::cout << "Deleting file: " << path << "\n";
        return true;
    }
};

class ProtectedFileSystem : public FileSystem {
private:
    RealFileSystem* realFS;
    bool hasPermission;
public:
    ProtectedFileSystem(bool hasPermission) : realFS(new RealFileSystem()), hasPermission(hasPermission) {}

    bool deleteFile(const std::string& path) override {
        if (path.find("/system/") == 0) {
            std::cout << "ProtectedFileSystem: Cannot delete system file: " << path << "\n";
            return false;
        }
        if (!hasPermission) {
            std::cout << "ProtectedFileSystem: No permission to delete: " << path << "\n";
            return false;
        }
        std::cout << "ProtectedFileSystem: Logging deletion of " << path << "\n";
        return realFS->deleteFile(path);
    }

    ~ProtectedFileSystem() { delete realFS; }
};

class Texture {
public:
    virtual ~Texture() = default;
    virtual void render() = 0;
};

class RealTexture : public Texture {
private:
    std::string name;
public:
    RealTexture(const std::string& name) : name(name) {
        std::cout << "Texture '" << name << "' loaded from disk\n";
    }
    void render() override {
        std::cout << "Rendering texture: " << name << "\n";
    }
};

class TextureProxy : public Texture {
private:
    std::string name;
    RealTexture* realTexture;
    int usageCount;
public:
    TextureProxy(const std::string& name)
        : name(name), realTexture(nullptr), usageCount(0) {}

    void render() override {
        usageCount++;
        if (!realTexture) {
            realTexture = new RealTexture(name);
        }
        std::cout << "TextureProxy: Usage count = " << usageCount << "\n";
        realTexture->render();
    }

    ~TextureProxy() { delete realTexture; }
};

class Video {
public:
    virtual ~Video() = default;
    virtual void play() = 0;
};

class RealVideo : public Video {
private:
    std::string filename;
public:
    RealVideo(const std::string& filename) : filename(filename) {
        std::cout << "Video '" << filename << "' loaded from server\n";
    }
    void play() override {
        std::cout << "Playing video: " << filename << "\n";
    }
};

class VideoProxy : public Video {
private:
    std::string filename;
    RealVideo* realVideo;
    int ageLimit;
public:
    VideoProxy(const std::string& filename, int ageLimit)
        : filename(filename), realVideo(nullptr), ageLimit(ageLimit) {}

    void play(int userAge) {
        if (userAge < ageLimit) {
            std::cout << "VideoProxy: Access denied - user is under " << ageLimit << " years old\n";
            return;
        }
        if (!realVideo) {
            realVideo = new RealVideo(filename);
        }
        realVideo->play();
    }

    void play() override {
        std::cout << "VideoProxy: Please specify user age\n";
    }

    ~VideoProxy() { delete realVideo; }
};

class BankAccount {
public:
    virtual ~BankAccount() = default;
    virtual bool withdraw(double amount) = 0;
};

class RealBankAccount : public BankAccount {
private:
    double balance;
public:
    RealBankAccount(double initialBalance) : balance(initialBalance) {}
    bool withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrew " << amount << ", new balance: " << balance << "\n";
            return true;
        }
        std::cout << "Insufficient funds\n";
        return false;
    }
};

class SecureBankProxy : public BankAccount {
private:
    RealBankAccount* account;
    std::string pin;
    const double MAX_WITHDRAWAL = 1000.0;
public:
    SecureBankProxy(double initialBalance, const std::string& pin)
        : account(new RealBankAccount(initialBalance)), pin(pin) {}

    bool authenticate(const std::string& inputPin) {
        return pin == inputPin;
    }

    bool withdraw(double amount, const std::string& inputPin) {
        if (!authenticate(inputPin)) {
            std::cout << "SecureBankProxy: Authentication failed\n";
            return false;
        }
        if (amount > MAX_WITHDRAWAL) {
            std::cout << "SecureBankProxy: Withdrawal limit exceeded (max: " << MAX_WITHDRAWAL << ")\n";
            return false;
        }
        std::cout << "SecureBankProxy: Logging withdrawal of " << amount << "\n";
        return account->withdraw(amount);
    }

    bool withdraw(double amount) override {
        std::cout << "SecureBankProxy: PIN required\n";
        return false;
    }

    ~SecureBankProxy() { delete account; }
};

class RemoteService {
public:
    virtual ~RemoteService() = default;
    virtual std::string call(const std::string& method) = 0;
};

class RealRemoteService : public RemoteService {
public:
    std::string call(const std::string& method) override {
        int delay = 100 + rand() % 400;
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        if (rand() % 10 == 0) { 
            throw std::runtime_error("Network error: Connection failed");
        }
        std::cout << "HTTP Request: " << method << " completed with " << delay << "ms delay\n";
        return "Response from " + method;
    }
};

class RemoteServiceProxy : public RemoteService {
private:
    RealRemoteService* realService;
public:
    RemoteServiceProxy() : realService(new RealRemoteService()) {}

    std::string call(const std::string& method) override {
        try {
            return realService->call(method);
        } catch (const std::exception& e) {
            std::cout << "RemoteServiceProxy: Error - " << e.what() << "\n";
            return "Error";
        }
    }

    ~RemoteServiceProxy() { delete realService; }
};

class SmartProxy {
private:
    static int activeCount;
    int id;
    std::chrono::steady_clock::time_point lastAccess;
    const std::chrono::seconds timeout = std::chrono::seconds(5);
public:
    SmartProxy(int id) : id(id) {
        activeCount++;
        lastAccess = std::chrono::steady_clock::now();
        std::cout << "SmartProxy: Object #" << id << " created, active count: " << activeCount << "\n";
    }

    void access() {
        lastAccess = std::chrono::steady_clock::now();
        std::cout << "SmartProxy: Object #" << id << " accessed\n";
        checkTimeout();
    }

    void checkTimeout() {
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - lastAccess) > timeout) {
            std::cout << "SmartProxy: Object #" << id << " destroyed due to inactivity\n";
            delete this;
        }
    }

    static void printActiveCount() {
        std::cout << "SmartProxy: Active objects: " << activeCount << "\n";
    }

    ~SmartProxy() { activeCount--; }
};
int SmartProxy::activeCount = 0;

class User {
public:
    std::string id;
    std::string name;
    User(const std::string& id, const std::string& name) : id(id), name(name) {}
};

class UserService {
public:
    virtual ~UserService() = default;
    virtual User getUser(const std::string& id) = 0;
};

class RealUserService : public UserService {
public:
    User getUser(const std::string& id) override {
        std::cout << "RealUserService: Querying database for user " << id << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        return User(id, "User_" + id);
    }
};

class CachingUserProxy : public UserService {
private:
    RealUserService* realService;
    std::unordered_map<std::string, User> cache;
public:
    CachingUserProxy() : realService(new RealUserService()) {}

    User getUser(const std::string& id) override {
        auto it = cache.find(id);
        if (it != cache.end()) {
            std::cout << "CachingUserProxy: Returning cached user " << id << "\n";
            return it->second;
        }
        User user = realService->getUser(id);
        cache[id] = user;
        std::cout << "CachingUserProxy: Cached user " << id << "\n";
        return user;
    }

    ~CachingUserProxy() { delete realService; }
};

class ThreadSafeProxy {
private:
    bool isBusy;
    std::mutex mtx;
public:
    ThreadSafeProxy() : isBusy(false) {}

    void safeOperation(const std::string& operation) {
        std::lock_guard<std::mutex> lock(mtx);
        if (isBusy) {
            std::cout << "ThreadSafeProxy: Operation '" << operation
                      << "' rejected - resource is busy\n";
            return;
        }
        isBusy = true;
        std::cout << "ThreadSafeProxy: Starting operation: " << operation << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "ThreadSafeProxy: Completed operation: " << operation << "\n";
        isBusy = false;
    }
};

class RateLimitProxy {
private:
    int requestCount;
    const int MAX_REQUESTS = 5;
public:
    RateLimitProxy() : requestCount(0) {}

    bool makeRequest(const std::string& request) {
        if (requestCount >= MAX_REQUESTS) {
            std::cout << "Too many requests\n";
            return false;
        }
        requestCount++;
        std::cout << "RateLimitProxy: Processing request #" << requestCount
                  << ": " << request << "\n";
        return true;
    }
};

class Service {
public:
    virtual ~Service() = default;
    virtual void execute() = 0;
};

class RealService : public Service {
public:
    void execute() override {
        std::cout << "RealService: Executing business logic\n";
    }
};

class AccessProxy : public Service {
private:
    RealService* realService;
    bool hasAccess;
public:
    AccessProxy(bool hasAccess) : realService(new RealService()), hasAccess(hasAccess) {}

    void execute() override {
        if (!hasAccess) {
            std::cout << "AccessProxy: Access denied\n";
            return;
        }
        realService->execute();
    }

    ~AccessProxy() { delete realService; }
};

class LoggingDecorator : public Service {
private:
    Service* wrappedService;
public:
    LoggingDecorator(Service* service) : wrappedService(service) {}

    void execute() override {
        std::cout << "LoggingDecorator: Before execution\n";
        wrappedService->execute();
        std::cout << "LoggingDecorator: After execution\n";
    }

    ~LoggingDecorator() { delete wrappedService; }
};

class ProxyFactory {
public:
    static std::unique_ptr<Service> create(const std::string& type) {
        if (type == "database") {
            return std::make_unique<DatabaseProxy>(true);
        } else if (type == "api") {
            return std::make_unique<APIGatewayProxy>("valid_token");
        } else {
            throw std::invalid_argument("Unknown proxy type: " + type);
        }
    }
};
class FileSystemComponent {
public:
    virtual ~FileSystemComponent() = default;
    virtual void remove() = 0;
    virtual std::string getName() const = 0;
};

class File : public FileSystemComponent {
private:
    std::string name;
public:
    File(const std::string& name) : name(name) {}
    void remove() override {
        std::cout << "File '" << name << "' removed\n";
    }
    std::string getName() const override { return name; }
};

class Folder : public FileSystemComponent {
private:
    std::string name;
    std::vector<std::unique_ptr<FileSystemComponent>> children;
public:
    Folder(const std::string& name) : name(name) {}
    void add(std::unique_ptr<FileSystemComponent> component) {
        children.push_back(std::move(component));
    }
    void remove() override {
        for (const auto& child : children) {
            child->remove();
        }
        std::cout << "Folder '" << name << "' removed\n";
    }
    std::string getName() const override { return name; }
};

class ProtectedFileSystemProxy : public FileSystemComponent {
private:
    FileSystemComponent* component;
    bool hasPermission;
public:
    ProtectedFileSystemProxy(FileSystemComponent* component, bool hasPermission)
        : component(component), hasPermission(hasPermission) {}

    void remove() override {
        if (!hasPermission) {
            std::cout << "ProtectedFileSystemProxy: No permission to remove '"
                      << component->getName() << "'\n";
            return;
        }
        if (component->getName().find("system") != std::string::npos) {
            std::cout << "ProtectedFileSystemProxy: Cannot remove system component '"
                      << component->getName() << "'\n";
            return;
        }
        std::cout << "ProtectedFileSystemProxy: Logging removal of '"
                  << component->getName() << "'\n";
        component->remove();
    }

    std::string getName() const override { return component->getName(); }
};

class ModernProxyExample {
private:
    std::unique_ptr<RealSubject> uniqueSubject;
    std::shared_ptr<RealImage> sharedImage;
public:
    ModernProxyExample()
        : uniqueSubject(std::make_unique<RealSubject>()),
          sharedImage(std::make_shared<RealImage>("shared_image.jpg")) {}

    void demonstrateModernCpp() {
        std::cout << "ModernProxyExample: Using modern C++ smart pointers\n";
        uniqueSubject->request();
        sharedImage->display();
    }
};

class CloudStorage {
public:
    virtual ~CloudStorage() = default;
    virtual bool upload(const std::string& filename, const std::string& content) = 0;
    virtual std::string download(const std::string& filename) = 0;
    virtual bool deleteFile(const std::string& filename) = 0;
};

class RealCloudStorage : public CloudStorage {
public:
    bool upload(const std::string& filename, const std::string& content) override {
        std::cout << "RealCloudStorage: Uploading " << filename << " to cloud...\n";
        return true;
    }
    std::string download(const std::string& filename) override {
        std::cout << "RealCloudStorage: Downloading " << filename << " from cloud...\n";
        return "Content of " + filename;
    }
    bool deleteFile(const std::string& filename) override {
        std::cout << "RealCloudStorage: Deleting " << filename << " from cloud...\n";
        return true;
    }
};

class CloudStorageProxy : public CloudStorage {
private:
    std::unique_ptr<RealCloudStorage> realStorage;
    std::unordered_map<std::string, std::string> cache;
    bool isAuthorized;
    const size_t MAX_UPLOAD_SIZE = 10 * 1024 * 1024; 

    void logOperation(const std::string& operation) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::cout << "[LOG] " << std::ctime(&time_t) << " " << operation << "\n";
    }

public:
    CloudStorageProxy() : realStorage(std::make_unique<RealCloudStorage>()), isAuthorized(false) {}

    void authorize(const std::string& token) {
        isAuthorized = (token == "valid_token");
        if (isAuthorized) {
            std::cout << "CloudStorageProxy: Authorization successful!\n";
        } else {
            std::cout << "CloudStorageProxy: Authorization failed!\
              
            << "\n";
        }
    }

    bool upload(const std::string& filename, const std::string& content) override {
        if (!isAuthorized) {
            logOperation("Upload denied: unauthorized access");
            std::cout << "CloudStorageProxy: Error: Unauthorized access\n";
            return false;
        }

        if (content.size() > MAX_UPLOAD_SIZE) {
            logOperation("Upload denied: file too large");
            std::cout << "CloudStorageProxy: Error: File too large (max 10 MB)\n";
            return false;
        }

        logOperation("Uploading: " + filename);
        bool success = realStorage->upload(filename, content);
        if (success) {
            cache[filename] = content;
            std::cout << "CloudStorageProxy: File '" << filename << "' cached\n";
        }
        return success;
    }

    std::string download(const std::string& filename) override {
        if (!isAuthorized) {
            logOperation("Download denied: unauthorized access");
            std::cout << "CloudStorageProxy: Error: Unauthorized access\n";
            return "";
        }

        auto it = cache.find(filename);
        if (it != cache.end()) {
            std::cout << "CloudStorageProxy: Returning cached version of '" << filename << "'\n";
            logOperation("Downloaded from cache: " + filename);
            return it->second;
        }

        std::string content = realStorage->download(filename);
        cache[filename] = content;
        logOperation("Downloaded and cached: " + filename);
        return content;
    }

    bool deleteFile(const std::string& filename) override {
        if (!isAuthorized) {
            logOperation("Delete denied: unauthorized access");
            std::cout << "CloudStorageProxy: Error: Unauthorized access\n";
            return false;
        }

        logOperation("Deleting: " + filename);
        bool success = realStorage->deleteFile(filename);
        if (success) {
            cache.erase(filename);
            std::cout << "CloudStorageProxy: File '" << filename << "' removed from cache\n";
        }
        return success;
    }
};
