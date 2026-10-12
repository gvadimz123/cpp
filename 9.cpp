#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <unordered_map>

using namespace std;

int main() {
    cout << "=== БЛОК 1: БАЗОВЫЕ ЗАДАЧИ ===" << endl;

    Enemy originalEnemy(100, 20, 1.5);
    cout << "Original enemy: ";
    originalEnemy.print();

    Enemy* copy1 = originalEnemy.clone();
    Enemy* copy2 = originalEnemy.clone();
    Enemy* copy3 = originalEnemy.clone();

    cout << "Copied enemies:" << endl;
    copy1->print();
    copy2->print();
    copy3->print();

    cout << "\nЗадача 2: Изменение копии" << endl;
    copy1->setHP(50);
    cout << "After changing copy1 HP:" << endl;
    cout << "Copy1: "; copy1->print();
    cout << "Original: "; originalEnemy.print();

    cout << "\nЗадача 4: Клонирование оружия" << endl;
    Weapon legendarySword("Legendary Sword", 100, 1000.0);

    for (int i = 0; i < 5; ++i) {
        Weapon* clonedSword = legendarySword.clone();
        clonedSword->setDamage(100 + i * 10);
        clonedSword->setPrice(1000.0 + i * 100.0);
        clonedSword->setName("Cloned Sword " + to_string(i + 1));
        clonedSword->print();
        delete clonedSword;
    }

    cout << "\nЗадача 5: Армия клонов NPC" << endl;
    NPC originalNPC("Warrior", 10, "Humans");

    vector<NPC*> npcArmy;
    for (int i = 0; i < 3; ++i) {
        npcArmy.push_back(originalNPC.clone());
        npcArmy[i]->print();
    }

    cout << "\nЗадача 6: Shallow copy проблема" << endl;
    ShallowCopyExample shallow1(42);
    ShallowCopyExample* shallow2 = shallow1.clone();

    shallow1.print();
    shallow2->print();

    delete shallow2; 

    cout << "\nЗадача 7: Deep copy исправление" << endl;
    DeepCopyExample deep1(42);
    DeepCopyExample* deep2 = deep1.clone();

    deep1.print();
    deep2->print();

    delete deep2;

    cout << "\nЗадача 8: Копирование инвентаря" << endl;
    Character player("Hero");
    player.addItem("Potion");
    player.addItem("Sword");
    player.print();

    Character* playerClone = player.clone();
    playerClone->addItem("Shield");
    cout << "Clone after adding item:" << endl;
    playerClone->print();
    cout << "Original:" << endl;
    player.print();

    delete playerClone;

    cout << "\nЗадача 9: Клонирование игрока" << endl;
    Sword* sword = new Sword("Steel");
    Player originalPlayer("Aragorn", 150, sword);
    originalPlayer.print();

    Player* clonedPlayer = originalPlayer.clone();
    clonedPlayer->print();

    delete clonedPlayer;

    cout << "\nЗадача 11: EnemyFactory" << endl;
    EnemyFactory factory;
    Enemy* zombie = factory.createEnemy("zombie");
    Enemy* skeleton = factory.createEnemy("skeleton");

    if (zombie) zombie->print();
    if (skeleton) skeleton->print();

    delete zombie;
    delete skeleton;

    cout << "\nЗадача 12: Registry" << endl;
    PrototypeRegistry registry;
    registry.registerPrototype("fireball", new Fireball());
    registry.registerPrototype("iceblast", new IceBlast());

    Spell* spell1 = dynamic_cast<Spell*>(registry.create("fireball"));
    Spell* spell2 = dynamic_cast<
Spell*>(registry.create("iceblast"));

if (spell1) spell1->cast();
if (spell2) spell2->cast();

delete spell1;
delete spell2;

cout << "\nЗадача 13: Spawner" << endl;
Enemy* baseEnemy = new Enemy(80, 25, 1.3);
Spawner spawner(baseEnemy);

for (int i = 0; i < 3; ++i) {
    Enemy* spawnedEnemy = static_cast<Enemy*>(spawner.spawn());
    spawnedEnemy->print();
    delete spawnedEnemy;
}

delete baseEnemy;

cout << "\nЗадача 14: Клонирование заклинаний" << endl;
Fireball fireball;
IceBlast iceblast;
PoisonCloud poisoncloud;

Spell* clonedFireball = fireball.clone();
Spell* clonedIceblast = iceblast.clone();
Spell* clonedPoisoncloud = poisoncloud.clone();

clonedFireball->cast();
clonedIceblast->cast();
clonedPoisoncloud->cast();

delete clonedFireball;
delete clonedIceblast;
delete clonedPoisoncloud;

cout << "\nЗадача 15: Генератор уровней" << endl;
Room originalRoom(1);
originalRoom.addContent("chest");
originalRoom.addContent("monster");
originalRoom.print();

vector<Room*> levelRooms;
for (int i = 2; i <= 4; ++i) {
    Room* clonedRoom = originalRoom.clone();
    clonedRoom->print();
    levelRooms.push_back(clonedRoom);
}

for (auto* room : levelRooms) {
    delete room;
}

cout << "\nЗадача 16: Decorator с клонированием" << endl;
Weapon* basicSword = new Weapon("Basic Sword", 50, 100.0);
FireWeapon* fireSword = new FireWeapon(basicSword);

Weapon* clonedFireSword = fireSword->clone();
clonedFireSword->print();

delete fireSword; 
delete clonedFireSword;

cout << "\nЗадача 17: Команда клонирования" << endl;
NPC* characterToClone = new NPC("Ranger", 15, "Elves");
CloneCharacterCommand cloneCommand(characterToClone);

NPC* clonedCharacter = static_cast<NPC*>(cloneCommand.execute());
clonedCharacter->print();

delete characterToClone;
delete clonedCharacter;

cout << "\nЗадача 18: GameFacade" << endl;
GameFacade game;
game.createPrototypes();
game.startLevel();

cout << "\nЗадача 19: Modern C++ с unique_ptr" << endl;
ModernEnemy modernEnemy(120, 5);
modernEnemy.print();

ModernEnemy* clonedModernEnemy = modernEnemy.clone();
clonedModernEnemy->print();

delete clonedModernEnemy;

cout << "\nЗадача 20: Архитектурная система игровых объектов" << endl;
PrototypeRegistry gameRegistry;

gameRegistry.registerPrototype("zombie", new EnemyObject("zombie"));
gameRegistry.registerPrototype("fireball", new SpellObject("fireball"));
gameRegistry.registerPrototype("potion", new ItemObject("health potion"));

GameObject* zombie = dynamic_cast<GameObject*>(gameRegistry.create("zombie"));
GameObject* fireball = dynamic_cast<GameObject*>(gameRegistry.create("fireball"));
GameObject* potion = dynamic_cast<GameObject*>(gameRegistry.create("potion"));

if (dynamic_cast<EnemyObject*>(zombie)) {
    dynamic_cast<EnemyObject*>(zombie)->print();
}
if (dynamic_cast<SpellObject*>(fireball)) {
    dynamic_cast<SpellObject*>(fireball)->print();
}
if (dynamic_cast<ItemObject*>(potion)) {
    dynamic_cast<ItemObject*>(potion)->print();
}

delete zombie;
delete fireball;
delete potion;

cout << "\nВсе задачи выполнены успешно!" << endl;
return 0;
}
