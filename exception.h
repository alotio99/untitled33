#ifndef UNTITLED3_EXCEPTION_H
#define UNTITLED3_EXCEPTION_H

#include <iostream>
#include <string>
#include <cctype>


class PasswordError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Ошибка пароля";
    } //noexcept - помечаются функции, которые гарантированно не выбросят исключение
};

class LengthError : public PasswordError {
public:
    const char* what() const noexcept override {
        return "LengthError: пароль должен содержать как минимум 9 символов";
    }
};

class RegisterError : public PasswordError {
public:
    const char* what() const noexcept override {
        return "RegisterError: пароль должен содержать как заглавные, так и строчные буквы";
    }
};

class DigitError : public PasswordError {
public:
    const char* what() const noexcept override {
        return "DigitError: пароль должен содержать хотя бы одну цифру";
    }
};

class ForbiddenLetterError : public PasswordError {
public:
    const char* what() const noexcept override {
        return "ForbiddenLetterError: пароль содержит неоднозначные символы (l, I, 1, o, O, 0)";
    }
};

std::string get_password() {
    std::string pwd;
    std::cout << "Введите пароль: ";
    std::getline(std::cin, pwd);

    if (pwd.length() < 9)
        throw LengthError();

    bool upper = false, lower = false;
    for (char c : pwd) {
        if (std::isupper(static_cast<unsigned char>(c))) upper = true;
        if (std::islower(static_cast<unsigned char>(c))) lower = true;
    } //static_cast<unsigned char> необходим для корректной работы
    //isupper/islower/isdigit т.к. они требуют неотрицательных значений
    if (!upper || !lower)
        throw RegisterError();

    bool digit = false;
    for (char c : pwd)
        if (std::isdigit(static_cast<unsigned char>(c))) //isdigit – истина, если символ десятичная цифра

    if (!digit)
        throw DigitError();

    for (char c : pwd) {
        if (c == 'l' || c == 'I' || c == '1' || c == 'o' || c == 'O' || c == '0')
            throw ForbiddenLetterError();
    }

    return pwd;
}




class GameException : public std::exception {};

class OutOfRangeException : public GameException {
    std::string msg;
public:
    OutOfRangeException(const std::string& weapon) : msg("Оружие " + weapon + " не удается достичь цели") {}
    const char* what() const noexcept override { return msg.c_str(); }
};

class NoWeaponException : public GameException {
public:
    const char* what() const noexcept override { return "У героя нет оружия!"; }
};

#endif