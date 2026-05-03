#include "class.h"

int main() {
    std::cout << "-------- Задание 1 --------" << std::endl;
    std::vector<int> v1 = {1, 2, 3};
    Print(v1, ", ");
    std::cout << std::endl;

    std::cout << "-------- Задание 2 --------" << std::endl;
    std::vector<int> nums2 = {1, 2, 1, 2, 2, 1, 6};
    zad2(nums2);
    std::cout << std::endl;

    std::cout << "-------- Задание 3 --------" << std::endl;
    zad3({"apple", "peach"});
    zad3({"alpha", "beta", "gamma"});
    std::cout << std::endl;

    std::cout << "-------- Задание 4 --------" << std::endl;
    zad4({"copy", "delta", "copy", "copy", "delta", "paste", "paste", "beta", "paste"});
    std::cout << std::endl;

    std::cout << "-------- Задание 5 --------" << std::endl;
    std::vector<int> v5 = {1, 2, 3};
    Duplicate(v5);
    Print(v5, " ");
    std::cout << std::endl;

    std::cout << "-------- Задание 6 --------" << std::endl;
    std::vector<int> v6 = { -1, 2, -3, 4, 5, 0, -7 };
    Process(v6);
    std::cout << std::endl;

    std::cout << "-------- Задание 7 --------" << std::endl;
    std::vector<int> v7 = {1, 1, 2, 2, 2, 3, 4, 4, 5};
    auto new_end = Unique(v7.begin(), v7.end());
    v7.erase(new_end, v7.end());
    Print(v7, " ");
    std::cout << std::endl;

    std::cout << "-------- Задание 8 --------" << std::endl;
    zad8();

    return 0;
}