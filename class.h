#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <numeric>


template <typename Container>
void Print(const Container& container, const std::string& razdel = " ") {
    bool first = true;
    for (const auto& elem : container) {
        if (!first)
            std::cout << razdel;
        std::cout << elem;
        first = false;
    }
    std::cout << std::endl;
}




void zad2(const std::vector<int>& numbers) {
    std::set<int> settt;
    for (int x : numbers) {
        if (settt.find(x) != settt.end()) //если найденный итератор не равен итератору конца, то есть элемент найден
            std::cout << "YES" << std::endl;
        else {
            std::cout << "NO" << std::endl;
            settt.insert(x); //добавляет x
        }
    }
}




void zad3(const std::vector<std::string>& words) {
    if (words.empty())
        return;
    std::set<char> unikal(words[0].begin(), words[0].end());
    for (size_t i = 1; i < words.size(); ++i) {
        std::set<char> unikal_two(words[i].begin(), words[i].end());
        std::set<char> intersection;
        std::set_intersection(unikal.begin(), unikal.end(),
                              unikal_two.begin(), unikal_two.end(),
                              std::inserter(intersection, intersection.begin())); //оператор вставки в intersection
        unikal = std::move(intersection); //перемещаем пересечение в unikal
        if (unikal.empty())
            break; //если unikal стало пустым, то искать больше нечего
    }
    for (char c : unikal)
        std::cout << c;
    std::cout << std::endl;
}




void zad4(const std::vector<std::string>& words) {
    std::map<std::string, int> counts;
    for (const std::string& w : words) {
        int& cnt = counts[w]; //если w нет в map, создаётся пара {w, 0} и возвращается ссылка на 0
        ++cnt;
        std::cout << cnt << std::endl;
    }
}


//что было у Васи не так
//push_back может вызвать перераспределение памяти вектора, после чего
//итератор it становится недействительным
//бесконечный цикл, v.end() всё время сдвигается при добавлении новых
//элементов, поэтому цикл никогда не закончится

template <typename T>
void Duplicate(std::vector<T>& v) {
    std::size_t orig_size = v.size();
    for (std::size_t i = 0; i < orig_size; ++i) {
        v.push_back(v[i]);
    }
}




template <typename Iter>
void PrintResults(Iter first, Iter last) {
    for (Iter it = first; it != last; ++it)
        std::cout << *it << std::endl;
}

template <typename T>
void Process(const std::vector<T>& data) {
    std::vector<T> filtered;
    std::copy_if(data.begin(), data.end(), //алгоритм, который копирует элементы из исходного диапазона в
                 std::back_inserter(filtered), //выходной диапазон, но только если они удовлетворяют условию
                 [](const T& x) { return x > 0; }); //const T& x параметр, который принимает каждый элемент вектора
    PrintResults(filtered.begin(), filtered.end());
}




template <typename Iter>
Iter Unique(Iter first, Iter last) {
    if (first == last)
        return last;
    Iter unik = first;
    while (++first != last) {
        if (!(*unik == *first)) {
            ++unik;
            *unik = std::move(*first); //перемещаем элемент на новую позицию
        }
    }
    return ++unik;
}




void zad8() {
    std::ofstream fail("tekst.txt");
    if (fail) {
        fail << "1 2 3 4 5 6 7 8 9 10" << std::endl; // пример данных
        fail.close();
    } else {
        std::cout << "Не удалось создать tekst.txt" << std::endl;
        return;
    }

    std::ifstream fil("tekst.txt");
    if (!fil) {
        std::cout << "Не удалось открыть tekst.txt" << std::endl;
        return;
    }
    std::vector<int> data;
    int x;
    while (fil >> x)
        data.push_back(x);
    fil.close();

    if (data.empty()) {
        std::cout << "Файл пуст" << std::endl;
        return;
    }

    // a) количество встреч числа n и позиции
    int n;
    std::cout << "Введите число n для поиска: ";
    std::cin >> n;
    int cnt = std::count(data.begin(), data.end(), n); //count сразу считает сколько n в диапазоне
    std::cout << "Число " << n << " встречается " << cnt << " раз(а)" << std::endl << "Позиции: ";
    std::vector<int>::iterator it = data.begin();
    while ((it = std::find(it, data.end(), n)) != data.end()) { //ищет n и если находит передвигает итератор
        std::cout << std::distance(data.begin(), it) << " "; //а дальше находится след позиция
        ++it; //distance ищет расстояние от начала до итератора, то есть позицию
    }
    std::cout << std::endl;

    // b) четные элементы и их номера, сумма
    std::vector<size_t> chet_pozicii; //size_t отлично подходит для размеров и индексов, т.к. беззнаковый
    for (size_t i = 0; i < data.size(); ++i)
        if (data[i] % 2 == 0) chet_pozicii.push_back(i);
    std::cout << "Количество чётных элементов: " << chet_pozicii.size() << std::endl;
    std::cout << "Номера чётных элементов: ";
    for (size_t poz : chet_pozicii) std::cout << poz << " ";
    std::cout << std::endl;

    if (chet_pozicii.size() > data.size() - chet_pozicii.size()) {
        int sum_chet = std::accumulate(data.begin(), data.end(), 0, //accumulate накапливает значения
        [](int acc, int val) { return acc + (val % 2 == 0 ? val : 0); }); //acc – текущая накопленная сумма, val – текущий элемент вектора
        std::cout << "Сумма чётных элементов: " << sum_chet << std::endl;
    } else {
        int sum_all = std::accumulate(data.begin(), data.end(), 0);
        std::cout << "Сумма всех элементов: " << sum_all << std::endl;
    }

    // c) исходный и отсортированный наборы
    data.push_back(3);
    data.push_back(-2);
    data.push_back(7);
    std::cout << "Исходный вектор: ";
    Print(data, " ");
    std::vector<int> sorted = data;
    std::sort(sorted.begin(), sorted.end());
    std::cout << "Отсортированный вектор: ";
    Print(sorted, " ");

    // d) перестановка первого и последнего элемента
    if (!data.empty()) {
        std::swap(data.front(), data.back());
        std::cout << "После обмена первого и последнего: ";
        Print(data, " ");
    }
} //