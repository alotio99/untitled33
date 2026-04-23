#ifndef UNTITLED3_CLASS_H
#define UNTITLED3_CLASS_H

#include <vector>
#include <cmath>


class BaseCharacter {
protected:
    double pos_x, pos_y;
    int hp;
public:
    BaseCharacter(double x, double y, int h) : pos_x(x), pos_y(y), hp(h) {}

    void move(double delta_x, double delta_y) {
        pos_x += delta_x;
        pos_y += delta_y;
    }

    bool is_alive() const {
        return hp > 0;
    }

    void get_damage(int amount) {
        hp -= amount;
        if (hp < 0) hp = 0;
    }

    double get_x() const { return pos_x; }
    double get_y() const { return pos_y; }

    double distance_to(const BaseCharacter& other) const {
        double dx = pos_x - other.pos_x;
        double dy = pos_y - other.pos_y;
        return std::sqrt(dx*dx + dy*dy);
    }
};


class Weapon {
    std::string name;
    int damage;
    double range;
public:
    Weapon() : name(""), damage(0), range(0.0) {}
    Weapon(const std::string& n, int d, double r) : name(n), damage(d), range(r) {}

    void hit(BaseCharacter& actor, BaseCharacter& target);

    friend std::ostream& operator<<(std::ostream& os, const Weapon& w) {
        os << w.name;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Weapon& w) {
        std::cout << "Enter weapon name: ";
        is >> w.name;
        std::cout << "Enter damage: ";
        is >> w.damage;
        std::cout << "Enter range: ";
        is >> w.range;
        return is;
    }

    std::string getName() const { return name; }
    int getDamage() const { return damage; }
    double getRange() const { return range; }
};


class BaseEnemy : public BaseCharacter {
    Weapon weapon;
public:
    BaseEnemy(double x, double y, const Weapon& w, int h) : BaseCharacter(x, y, h), weapon(w) {}

    void hit(BaseCharacter& target) {
        if (!target.is_alive()) {
            std::cout << "Враг уже повержен" << std::endl;
            return;
        }
        double dist = distance_to(target);
        if (dist > weapon.getRange()) {
            std::cout << "Враг слишком далеко для оружия " << weapon << std::endl;
            return;
        }
        std::cout << "Врагу нанесен урон оружием " << weapon << " в размере " << weapon.getDamage() << std::endl;
        target.get_damage(weapon.getDamage());
    }

    friend std::ostream& operator<<(std::ostream& os, const BaseEnemy& e) {
        os << "Враг на позиции (" << e.pos_x << ", " << e.pos_y << ") с оружием " << e.weapon;
        return os;
    }
};

// Реализация Weapon::hit после определения BaseEnemy и BaseCharacter
void Weapon::hit(BaseCharacter& actor, BaseCharacter& target) {
    if (!target.is_alive()) {
        std::cout << "Враг уже повержен" << std::endl;
        return;
    }
    double dist = actor.distance_to(target);
    if (dist > range) {
        std::cout << "Враг слишком далеко для оружия " << name << std::endl;
        return;
    }
    std::cout << "Врагу нанесен урон оружием " << name << " в размере " << damage << std::endl;
    target.get_damage(damage);
}

// Класс MainHero
class MainHero : public BaseCharacter {
    std::string name;
    std::vector<Weapon> inventory;
    size_t current_weapon_index;
    static const int MAX_HP = 200;

public:
    MainHero(double x, double y, const std::string& n, int h) : BaseCharacter(x, y, h), name(n), current_weapon_index(0) {}

    void hit(BaseEnemy& target) {
        if (inventory.empty()) {
            std::cout << "Я безоружен" << std::endl;
            return;
        }
        Weapon& w = inventory[current_weapon_index];
        w.hit(*this, target);
    }

    void add_weapon(const Weapon& w) {
        inventory.push_back(w);
        if (inventory.size() == 1) {
            current_weapon_index = 0;
        }
        std::cout << "Подобрал " << w << std::endl;
    }

    void next_weapon() {
        if (inventory.empty()) {
            std::cout << "Я безоружен" << std::endl;
            return;
        }
        if (inventory.size() == 1) {
            std::cout << "У меня только одно оружие" << std::endl;
            return;
        }
        current_weapon_index = (current_weapon_index + 1) % inventory.size();
        std::cout << "Сменил оружие на " << inventory[current_weapon_index] << std::endl;
    }

    void heal(int amount) {
        hp += amount;
        if (hp > MAX_HP) hp = MAX_HP;
        std::cout << "Полечился, теперь здоровья " << hp << std::endl;
    }

    int get_hp() const { return hp; }
    std::string get_name() const { return name; }
};

#endif