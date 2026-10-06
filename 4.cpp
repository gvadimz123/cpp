#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <algorithm>

class Component {
public:
    virtual ~Component() = default;
    virtual void display(int depth = 0) const = 0;
    virtual bool remove(const std::string& name) = 0;
    virtual int count() const = 0;
    virtual Component* find(const std::string& name) = 0;
    virtual std::string getName() const = 0;
};

class MenuItem : public Component {
private:
    std::string name;

public:
    explicit MenuItem(const std::string& itemName) : name(itemName) {}

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ') << "┗─ " << name << std::endl;
    }

    bool remove(const std::string& targetName) override {
        return name == targetName;
    }

    int count() const override {
        return 1;
    }

    Component* find(const std::string& targetName) override {
        if (name == targetName) {
            return this;
        }
        return nullptr;
    }

    std::string getName() const override {
        return name;
    }
};

class Menu : public Component {
private:
    std::string name;
    std::vector<std::shared_ptr<Component>> children;

public:
    explicit Menu(const std::string& menuName) : name(menuName) {}

    void add(std::shared_ptr<Component> component) {
        children.push_back(std::move(component));
    }

    void display(int depth = 0) const override {
        std::cout << std::string(depth * 2, ' ');
        if (depth > 0) std::cout << "┣─ ";
        std::cout << name << std::endl;

        for (const auto& child : children) {
            child->display(depth + 1);
        }
    }

    bool remove(const std::string& targetName) override {
        auto it = std::remove_if(children.begin(), children.end(),
            [&targetName](const std::shared_ptr<Component>& comp) {
                return comp->remove(targetName);
            });
        bool removed = it != children.end();
        children.erase(it, children.end());
        return removed;
    }

    int count() const override {
        int total = 1; 
        for (const auto& child : children) {
            total += child->count();
        }
        return total;
    }

    Component* find(const std::string& targetName) override {
        if (name == targetName) return this;

        for (auto& child : children) {
            if (Component* found = child->find(targetName)) {
                return found;
            }
        }
        return nullptr;
    }

    std::string getName() const override {
        return name;
    }

    void dfs() const {
        std::cout << "DFS обход:" << std::endl;
        dfsHelper(this, 0);
    }

    void dfsHelper(const Component* node, int depth) const {
        node->display(depth);
        const Menu* menu = dynamic_cast<const Menu*>(node);
        if (menu) {
            for (const auto& child : menu->children) {
                dfsHelper(child.get(), depth + 1);
            }
        }
    }

    void bfs() const {
        std::cout << "BFS обход:" << std::endl;
        std::queue<std::pair<const Component*, int>> q;
        q.push({this, 0});

        while (!q.empty()) {
            auto [node, depth] = q.front();
            q.pop();
            node->display(depth);

            const Menu* menu = dynamic_cast<const Menu*>(node);
            if (menu) {
                for (const auto& child : menu->children) {
                    q.push({child.get(), depth + 1});
                }
            }
        }
    }
};

class File : public Component {
private:
    std::string name;
    size_t size;

public:
    File(const std::string& fileName, size_t fileSize)
        : name(fileName), size(fileSize) {}

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ')
                  << "┗─ " << name << " (" << size << " bytes)" << std::endl;
    }

    bool remove(const std::string& targetName) override {
        return name == targetName;
    }

    int count() const override { return 1; }

    Component* find(const std::string& targetName) override {
        if (name == targetName) return this;
        return nullptr;
    }

    std::string getName() const override { return name; }
    size_t getSize() const { return size; }
};

class Folder : public Component {
private:
    std::string name;
    std::vector<std::shared_ptr<Component>> contents;

public:
    Folder(const std::string& folderName) : name(folderName) {}

    void add(std::shared_ptr<Component> item) {
        contents.push_back(std::move(item));
    }

    void display(int depth) const override {
        std::cout << std::string(depth * 2, ' ');
        if (depth > 0) std::cout << "┣─ ";
        std::cout << name << std::endl;
        for (const auto& item : contents) {
            item->display(depth + 1);
        }
    }

    bool remove(const std::string& targetName) override {
        auto it = std::remove_if(contents.begin(), contents.end(),
            [&targetName](const std::shared_ptr<Component>& comp) {
                return comp->remove(targetName);
            });
        bool removed = it != contents.end();
        contents.erase(it, contents.end());
        return removed;
    }

    int count() const override {
        int total = 1;
        for (const auto& item : contents) {
            total += item->count();
        }
        return total;
    }

    Component* find(const std::string& targetName) override {
        if (name == targetName) return this;
        for (auto& item : contents) {
            if (Component* found = item->find(targetName)) {
                return found;
            }
        }
        return nullptr;
    }

    std::string getName() const override { return name; }

    size_t getSize() const {
        size_t totalSize = 0;
        for (const auto& item : contents) {
            if (auto* file = dynamic_cast<File*>(item.get())) {
                totalSize += file->getSize();
            } else if (auto* folder = dynamic_cast<Folder*>(item.get())) {
                totalSize += folder->getSize();
            }
        }
        return totalSize;
    }
};

int main() {
    auto root = std::make_shared<Menu>("Root");
    root->add(std::make_shared<MenuItem>("Leaf1"));
    root->add(std::make_shared<MenuItem>("Leaf2"));

    auto composite = std::make_shared<Menu>("Composite");
    composite->add(std::make_shared<MenuItem>("Leaf3"));
    composite->add(std::make_shared<MenuItem>("Leaf4"));

    root->add(composite);

    std::cout << "Дерево объектов:" << std::endl;
    root->display();
    std::cout << "\nКоличество элементов в дереве: " << root->count() << std::endl;

    std::cout << "\nУдаляем Leaf3:" << std::endl;
    root->remove("Leaf3");
    root->display();

    std::cout << "\nПоиск Leaf2:" << std::endl;
    if (Component* found = root->find("Leaf2")) {
        std::cout << "Найден: " << found->getName() << std::endl;
    } else {
        std::cout << "Не найден" << std::endl;
    }

    std::cout << "\n=== Файловая система ===" << std::endl;
    auto rootFolder = std::make_shared<Folder>("Root");
    rootFolder->add(std::make_shared<File>("document.txt", 1024));
    rootFolder->add(std::make_shared<File>("image.jpg", 2048));

    auto subFolder = std::make_shared<Folder>("Documents");
    subFolder->add(std::make_shared<File>("report.pdf", 4096));
    subFolder->add(std::make_shared<File>("notes.txt", 512));

    rootFolder->add(subFolder);

    rootFolder->display();
    std::cout << "Общий размер папки: " << rootFolder->getSize() << " bytes" << std::endl;

    std::cout << "\n=== Глубокая вложенность (5 уровней) ===" << std::endl;
    auto level1 = std::make_shared<Menu>("Level1");
    auto level2 = std::make_shared<Menu>("Level2");
    auto level3 = std::make_shared<Menu>("Level3");
    auto level4 = std::make_shared<Menu>("Level4");
    auto level5 = std::make_shared<Menu>("Level5");

    level5->add(std::make_shared<MenuItem>("DeepItem"));
    level4->add(level5);
    level3->add(level4);
    level2->add(level3);
    level1->add(level2);

    level1->display();

    std::cout << "\n";
    level1->dfs();
    std::cout << "\n";
    level1->bfs();

    std::cout << "\n=== Игровая карта ===" << std::endl;
    auto world = std::make_shared<Menu>("World");
    auto region = std::make_shared<Menu>("Region");
    auto city = std::make_shared<Menu>("City");
    auto building = std::make_shared<Menu>("Building");

    building->add(std::make_shared<MenuItem>("Player"));
    building->add(std::make_shared<MenuItem>("Enemy"));
    city->add(building);
    region->add(city);
    world->add(region);

    world->display();

    std::cout << "\n=== GUI система ===" << std::endl;
    auto window = std::make_shared<Menu>("Window");
    window->add(std::make_shared<MenuItem>("Button"));
    window->add(std::make_shared<MenuItem>("Label"));

    auto panel = std::make_shared<Menu>("Panel");
    panel->add(std::make_shared<MenuItem>("TextField"));
    window->add(panel);

    window->display();

    std::cout << "\n=== HTML DOM ===" << std::endl;
    auto body = std::make_shared<Menu>("Body");
    body->add(std::make_shared<MenuItem>("TextNode"));

    auto div = std::make_shared<Menu>("Div");
    div->add(std::make_shared<MenuItem>("ImageNode"));
    div->add(std::make_shared<MenuItem>("ButtonNode"));
    body->add(div);

    body->display();

    std::cout << "\n=== Организационная структура ===" << std::endl;
    auto company = std::make_shared<Menu>("Company");
    company->add(std::make_shared<MenuItem>("Employee1"));

    auto dept = std::make_shared<Menu>("Department");
    dept->add(std::make_shared<MenuItem>("Employee2"));
    dept->add(std::make_shared<MenuItem>("Employee3"));
    company->add(dept);

    company->display();

    std::cout << "\n=== Composite + Decorator ===" << std::endl;
    auto decoratedPanel = std::make_shared<Menu>("Panel with Border and Shadow");
    decoratedPanel->add(std::make_shared<MenuItem>("BorderDecorator"));
    decoratedPanel->add(std::make_shared<MenuItem>("ShadowDecorator"));
    decoratedPanel->add(std::make_shared<MenuItem>("Button"));
    decoratedPanel->display();

    std::cout << "\n=== Composite + Bridge ===" << std::endl;
    auto uiElements = std::make_shared<Menu>("UI Elements");
    uiElements->add(std::make_shared<MenuItem>("OpenGLRenderer"));
    uiElements->add(std::make_shared<MenuItem>("VulkanRenderer"));
    uiElements->add(std::make_shared<MenuItem>("Button"));
    uiElements->display();

    std::cout << "\n=== Composite + Command ===" << std::endl;
    auto commandSystem = std::make_shared<Menu>("Command System");
    commandSystem->add(std::make_shared<MenuItem>("update"));
    commandSystem->add(std::make_shared<MenuItem>("render"));
    commandSystem->add(std::make_shared<MenuItem>("delete"));
    commandSystem->display();

    return 0;
}
