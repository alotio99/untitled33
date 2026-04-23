#include <exception>
#include <iostream>
#include <ostream>
#include <string>

#include "class.h"
#include "exception.h"


int main() {

    std::cout << "---------------- Задание 1 ----------------" << std::endl;
    try {
        std::string pwd = get_password();
        std::cout << "Пароль принят: " << pwd << std::endl;
    } catch (const PasswordError& e) {
        std::cout << "Исключение: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Неизвестное исключение: " << e.what() << std::endl;
    }

    std::cout << std::endl << "---------------- Задание 2 ----------------" << std::endl;

    Weapon sword("Меч", 30, 2.0);
    Weapon bow("Лук", 20, 8.0);
    Weapon axe("Топор", 40, 1.5);
    Weapon dagger("Кинжал", 15, 1.0);

    MainHero hero(0.0, 0.0, "Воронов", 100);
    std::cout << "Герой " << hero.get_name() << " появился в точке (0,0) со здоровьем " << hero.get_hp() << std::endl;

    hero.add_weapon(sword);
    hero.add_weapon(bow);
    hero.next_weapon();
    hero.next_weapon();

    BaseEnemy goblin(3.0, 0.0, dagger, 40);
    BaseEnemy orc(7.0, 1.0, axe, 80);
    BaseEnemy archer(2.0, 5.0, bow, 50);

    std::cout << std::endl <<  "----- Начало битвы -----" << std::endl;

    std::cout << std::endl << "Бой с гоблином:" << std::endl;
    hero.hit(goblin);
    hero.next_weapon();
    hero.hit(goblin);
    hero.hit(goblin);
    hero.hit(goblin);

    Weapon spear("Копьё", 25, 4.0);
    hero.add_weapon(spear);

    std::cout << std::endl << "Бой с орком:" << std::endl;
    hero.next_weapon();
    hero.hit(orc);
    hero.next_weapon();
    hero.hit(orc);
    hero.hit(orc);

    std::cout << std::endl << "Лечение:" << std::endl;
    hero.heal(30);

    std::cout << std::endl << "Бой с лучником:" << std::endl;
    hero.next_weapon();
    hero.hit(archer);
    hero.next_weapon();
    hero.hit(archer);
    hero.next_weapon();
    hero.hit(archer);
    hero.next_weapon();
    hero.hit(archer);
    hero.hit(archer);
    hero.hit(archer);


    std::cout << std::endl << "Битва окончена. Герой жив? " << (hero.is_alive() ? "Да" : "Нет") << std::endl;

    std::cout << std::endl << "----- Проверка исключений -----" << std::endl;
    MainHero naked_hero(0, 0, "Безоружный", 100);
    try {
        if (naked_hero.get_hp() > 0) {
            throw NoWeaponException();
        }
    } catch (const NoWeaponException& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }

    try {
        Weapon short_sword("Короткий меч", 10, 0.5);
        MainHero dummy(0, 0, "Тест", 100);
        dummy.add_weapon(short_sword);
        BaseEnemy distant_enemy(10, 0, dagger, 50);
        throw OutOfRangeException(short_sword.getName());
    } catch (const OutOfRangeException& e) {
        std::cout << "Поймано исключение: " << e.what() << std::endl;
    }

    return 0;
}
