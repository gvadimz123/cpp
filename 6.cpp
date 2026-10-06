#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

// 1. Минимальный Flyweight
class Flyweight {
private:
    std::string intrinsicState;
public:
    Flyweight(const std::string& state) : intrinsicState(state) {}
    
    void operation(const std::string& extrinsicState) const {
        std::cout << "Flyweight with state '" << intrinsicState
                  << "' processing '" << extrinsicState << "'\n";
    }
    
    friend class FlyweightFactory;
};

class FlyweightFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<Flyweight>> flyweights;
    int createdCount = 0;

public:
    std::shared_ptr<Flyweight> getFlyweight(const std::string& key) {
        auto it = flyweights.find(key);
        if (it == flyweights.end()) {
            auto newFlyweight = std::make_shared<Flyweight>(key);
            flyweights[key] = newFlyweight;
            createdCount++;
            return newFlyweight;
        }
        return it->second;
    }

    int getCreatedCount() const { return createdCount; }
};

class Context {
private:
    std::shared_ptr<Flyweight> flyweight;
    std::string extrinsicState;

public:
    Context(std::shared_ptr<Flyweight> fw, const std::string& extState)
        : flyweight(fw), extrinsicState(extState) {}

    void operation() const {
        flyweight->operation(extrinsicState);
    }
};

// 2. Внутреннее и внешнее состояние — класс Car
class Car {
private:
    // Внутреннее состояние (Flyweight)
    std::string model;
    std::string color;
    std::string engine;

    // Внешнее состояние (в контексте)
    double x, y;
    double speed;

public:
    Car(const std::string& m, const std::string& c, const std::string& e)
        : model(m), color(c), engine(e), x(0), y(0), speed(0) {}

    void setPosition(double xPos, double yPos) { x = xPos; y = yPos; }
    void setSpeed(double sp) { speed = sp; }

    void display() const {
        std::cout << model << " " << color << " " << engine
                  << " at (" << x << "," << y << ") speed: " << speed << "\n";
    }
};

// 3. Подсчёт объектов и проверка переиспользования
void demonstrateFlyweight() {
    FlyweightFactory factory;

    auto fw1 = factory.getFlyweight("shared");
    auto fw2 = factory.getFlyweight("shared"); // Тот же объект
    auto fw3 = factory.getFlyweight("unique");

    std::cout << "Created flyweight count: " << factory.getCreatedCount() << "\n";

    // 4. Проверка переиспользования — выводим адреса
    std::cout << "Address of fw1: " << fw1.get() << "\n";
    std::cout << "Address of fw2: " << fw2.get() << "\n"; // Тот же адрес
    std::cout << "Address of fw3: " << fw3.get() << "\n";

    Context c1(fw1, "context1");
    Context c2(fw2, "context2");
    c1.operation();
    c2.operation();
}
// 6. Игровой лес
class TreeType {
private:
    std::string texture;
    std::string model;
    std::string type;

public:
    TreeType(const std::string& t, const std::string& m, const std::string& ty)
        : texture(t), model(m), type(ty) {}

    void draw(double x, double y, double height) const {
        std::cout << "Drawing " << type << " at (" << x << "," << y
                  << ") height: " << height << " texture: " << texture << "\n";
    }
};

class Tree {
private:
    std::shared_ptr<TreeType> type;
    double x, y, height;

public:
    Tree(std::shared_ptr<TreeType> t, double xPos, double yPos, double h)
        : type(t), x(xPos), y(yPos), height(h) {}

    void draw() const { type->draw(x, y, height); }
};

class TreeFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<TreeType>> treeTypes;

public:
    std::shared_ptr<TreeType> getTreeType(const std::string& type,
                                         const std::string& texture,
                                         const std::string& model) {
        std::string key = type + "_" + texture + "_" + model;
        auto it = treeTypes.find(key);
        if (it == treeTypes.end()) {
            auto newType = std::make_shared<TreeType>(texture, model, type);
            treeTypes[key] = newType;
            return newType;
        }
        return it->second;
    }
};

// 7. Текстовый редактор
class CharacterStyle {
private:
    std::string font;
    int size;
    std::string color;

public:
    CharacterStyle(const std::string& f, int s, const std::string& c)
        : font(f), size(s), color(c) {}

    void apply(char character, int x, int y) const {
        std::cout << "Character '" << character << "' at (" << x << "," << y
                  << ") with style: " << font << " " << size << "pt " << color << "\n";
    }
};

class Character {
private:
    std::shared_ptr<CharacterStyle> style;
    char character;
    int x, y;

public:
    Character(std::shared_ptr<CharacterStyle> s, char c, int xPos, int yPos)
        : style(s), character(c), x(xPos), y(yPos) {}

    void render() const { style->apply(character, x, y); }
};
// 11. Кеш моделей
class Model {
private:
    std::string name;
    // Данные модели...

public:
    Model(const std::string& n) : name(n) {
        // Загрузка модели из файла
        std::cout << "Loading model: " << name << "\n";
    }

    void render(double x, double y, double z) const {
        std::cout << "Rendering " << name << " at (" << x << "," << y << "," << z << ")\n";
    }
};

class ModelFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<Model>> models;

public:
    std::shared_ptr<Model> getModel(const std::string& name) {
        auto it = models.find(name);
        if (it == models.end()) {
            auto newModel = std::make_shared<Model>(name);
            models[name] = newModel;
            return newModel;
        }
        return it->second;
    }
};

// 14. Большое количество объектов
void testMemoryEfficiency() {
    const int OBJECT_COUNT = 10000;
    FlyweightFactory factory;
    std::vector<std::shared_ptr<Context>> contexts;

    for (int i = 0; i < OBJECT_COUNT; ++i) {
        auto flyweight = factory.getFlyweight("common");
        contexts.push_back(std::make_shared<Context>(flyweight, "data_" + std::to_string(i)));
    }

    std::cout << "Total objects: " << OBJECT_COUNT << "\n";
    std::cout << "Flyweight objects created: " << factory
    // Продолжение функции testMemoryEfficiency()
    std::cout << "Total objects: " << OBJECT_COUNT << "\n";
    std::cout << "Flyweight objects created: " << factory.getCreatedCount() << "\n";

    // Оценка экономии памяти (упрощённая)
    size_t contextSize = sizeof(Context);
    size_t flyweightSize = sizeof(Flyweight);

    size_t totalWithoutFlyweight = OBJECT_COUNT * (contextSize + flyweightSize);
    size_t totalWithFlyweight = OBJECT_COUNT * contextSize + factory.getCreatedCount() * flyweightSize;

    std::cout << "Memory without Flyweight: ~" << totalWithoutFlyweight << " bytes\n";
    std::cout << "Memory with Flyweight: ~" << totalWithFlyweight << " bytes\n";
    std::cout << "Memory saved: ~" << (totalWithoutFlyweight - totalWithFlyweight) << " bytes\n";
}

// 15. Изменяемое состояние — пример ошибки
class MutableFlyweight {
private:
    std::string data;
public:
    MutableFlyweight(const std::string& d) : data(d) {}

    void setData(const std::string& newData) { data = newData; }
    void display() const { std::cout << "Data: " << data << "\n"; }
};

class MutableContext {
private:
    std::shared_ptr<MutableFlyweight> flyweight;
public:
    MutableContext(std::shared_ptr<MutableFlyweight> fw) : flyweight(fw) {}
    void changeData(const std::string& newData) { flyweight->setData(newData); }
    void show() const { flyweight->display(); }
};

void demonstrateMutableError() {
    auto flyweight = std::make_shared<MutableFlyweight>("original");

    MutableContext c1(flyweight);
    MutableContext c2(flyweight);

    std::cout << "Before change:\n";
    c1.show();
    c2.show();

    c1.changeData("changed!");

    std::cout << "After c1 changes data:\n";
    c1.show(); // changed!
    c2.show(); // тоже changed! — проблема!
}
// 17. Flyweight + Proxy — ленивая загрузка текстур
class TextureProxy {
private:
    std::string filename;
    std::shared_ptr<std::string> textureData; // Упрощённо: строка как данные текстуры

public:
    TextureProxy(const std::string& file) : filename(file), textureData(nullptr) {}

    void load() {
        if (!textureData) {
            std::cout << "Loading texture: " << filename << "\n";
            textureData = std::make_shared<std::string>("Texture data for " + filename);
        }
    }

    const std::shared_ptr<std::string>& getData() {
        load();
        return textureData;
    }
};

class TextureFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<TextureProxy>> textures;

public:
    std::shared_ptr<TextureProxy> getTexture(const std::string& filename) {
        auto it = textures.find(filename);
        if (it == textures.end()) {
            auto newTexture = std::make_shared<TextureProxy>(filename);
            textures[filename] = newTexture;
            return newTexture;
        }
        return it->second;
    }
};

// 20. Архитектурная задача — система рендеринга игрового мира
enum class ObjectType { Tree, Rock, Grass, NPC };

class GameObjectType {
private:
    ObjectType type;
    std::string model;
    std::string texture;
    std::string animation;
    std::string sound;

public:
    GameObjectType(ObjectType t, const std::string& m, const std::string& tex,
                 const std::string& anim, const std::string& snd)
        : type(t), model(m), texture(tex), animation(anim), sound(snd) {}

    void render(double x, double y, double z) const {
        std::cout << "Rendering " << getTypeString() << " at (" << x << "," << y << "," << z
                  << ") with model: " << model << "\n";
    }

private:
    std::string getTypeString() const {
        switch (type) {
            case ObjectType::Tree: return "Tree";
            case ObjectType::Rock: return "Rock";
            case ObjectType::Grass: return "Grass";
            case ObjectType::NPC: return "NPC";
            default: return "Unknown";
        }
    }
};

class GameObject {
private:
    std::shared_ptr<GameObjectType> type;
    double x, y, z;
    int health;
    std::string state;
    double direction;

public:
    GameObject(std::shared_ptr<GameObjectType> t, double xPos, double yPos, double zPos,
               int hp, const std::string& st, double dir)
        : type(t), x(xPos), y(yPos), z(zPos), health(hp), state(st), direction(dir) {}

    void update() { /* логика обновления */ }
    void render() const { type->render(x, y, z); }
};

class GameWorldFactory {
private:
    std::unordered_map<ObjectType, std::vector<std::shared_ptr<GameObjectType>>> objectTypes;
    int flyweightCount = 0;

public:
    std::shared_ptr<GameObjectType> getObjectType(ObjectType type, const std::string& model,
                                                      const std::string& texture, const std::string& animation,
                                               const std::string& sound) {
        // Создаём ключ на основе типа и характеристик
        std::string key = std::to_string(static_cast<int>(type)) + "_" + model + "_" + texture;

        auto& typeList = objectTypes[type];
        for (const auto& existingType : typeList) {
            if (existingType->getTypeString() == getTypeStringFromEnum(type) &&
                existingType->getModel() == model &&
                existingType->getTexture() == texture) {
                return existingType;
            }
        }

        auto newType = std::make_shared<GameObjectType>(type, model, texture, animation, sound);
        typeList.push_back(newType);
        flyweightCount++;
        return newType;
    }

    int getFlyweightCount() const { return flyweightCount; }

private:
    std::string getTypeStringFromEnum(ObjectType type) const {
        switch (type) {
            case ObjectType::Tree: return "Tree";
            case ObjectType::Rock: return "Rock";
            case ObjectType::Grass: return "Grass";
            case ObjectType::NPC: return "NPC";
            default: return "Unknown";
        }
    }
};

void demonstrateGameWorld() {
    GameWorldFactory factory;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    const int TOTAL_OBJECTS = 1000;

    // Создаём объекты с повторяющимися типами
    auto treeType1 = factory.getObjectType(ObjectType::Tree, "Oak", "oak_texture", "idle", "wind.wav");
    auto treeType2 = factory.getObjectType(ObjectType::Tree, "Pine", "pine_texture", "idle", "wind.wav");
    auto rockType = factory.getObjectType(ObjectType::Rock, "LargeRock", "rock_texture", "none", "none");

    for (int i = 0; i < TOTAL_OBJECTS; ++i) {
        if (i % 3 == 0) {
            gameObjects.push_back(std::make_shared<GameObject>(
                treeType1, i * 10, 0, 0, 100, "alive", 0.0));
        } else if (i % 3 == 1) {
            gameObjects.push_back(std::make_shared<GameObject>(
                treeType2, i * 10, 5, 0, 100, "alive", 0.0));
        } else {
            gameObjects
