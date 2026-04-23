#ifndef UNTITLED3_EXCEPTION_H
#define UNTITLED3_EXCEPTION_H

#include <iostream>
#include <string>
#include <cctype>

// ========================= ЗАДАНИЕ 1 =========================


class PasswordError : public std::exception {
public:
    const char* what() const noexcept override {
        return "Password error";
    }
};

class LengthError : public PasswordError {
public:
    const char* what() const noexcept override {
        return "LengthError: password must be at least 9 characters";
    }
};

class RegisterError : public PasswordError {
public:
    const char* what() const noexcept override {
        return "RegisterError: password must contain both uppercase and lowercase letters";
    }
};

class DigitError : public PasswordError {
public:
    const char* what() const noexcept override {
        return "DigitError: password must contain at least one digit";
    }
};

class ForbiddenLetterError : public PasswordError {
public:
    const char* what() const noexcept override {
        return "ForbiddenLetterError: password contains ambiguous characters (l, I, 1, o, O, 0)";
    }
};

std::string get_password() {
    std::string pwd;
    std::cout << "Enter password: ";
    std::getline(std::cin, pwd);

    if (pwd.length() < 9) {
        throw LengthError();
    }

    bool has_upper = false, has_lower = false;
    for (char c : pwd) {
        if (std::isupper(static_cast<unsigned char>(c))) has_upper = true;
        if (std::islower(static_cast<unsigned char>(c))) has_lower = true;
    }
    if (!has_upper || !has_lower) {
        throw RegisterError(); //static_cast<unsigned char> необходим для корректной работы
        //isupper/islower/isdigit т.к. они требуют неотрицательных значений
    }

    bool has_digit = false;
    for (char c : pwd) {
        if (std::isdigit(static_cast<unsigned char>(c))) { //isdigit – истина, если символ десятичная цифра
            has_digit = true;
            break;
        }
    }
    if (!has_digit) {
        throw DigitError();
    }

    for (char c : pwd) {
        if (c == 'l' || c == 'I' || c == '1' || c == 'o' || c == 'O' || c == '0') {
            throw ForbiddenLetterError();
        }
    }

    return pwd;
}

// ========================= ЗАДАНИЕ 2 =========================

// Собственные классы исключений
class GameException : public std::exception {};
class OutOfRangeException : public GameException {
    std::string msg;
public:
    OutOfRangeException(const std::string& weapon_name) : msg("Weapon " + weapon_name + " cannot reach the target") {}
    const char* what() const noexcept override { return msg.c_str(); }
};
class NoWeaponException : public GameException {
public:
    const char* what() const noexcept override { return "Hero has no weapon!"; }
};



#endif