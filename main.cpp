#include <iostream>

// Librerias de Containers
#include <vector>
#include <list>
#include <deque>
// Librerias de Algoritmos
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <type_traits>
#include <random>
#include <fstream>

bool EsPar(int item) {
    return item % 2 == 0;
}

template<typename Container>
void print(std::ostream& os, const Container& v) {
    using T = typename Container::value_type;
    std::copy(v.begin(), v.end(),
              std::ostream_iterator<T>(os, " "));
    os << std::endl;
}

void ejemplo_copy() {
    std::vector v1 = {1, 2, 3, 4, 5, 6, 7};
    auto v2 = v1;
    // Forma #1
    std::vector<int> v3(4);
    std::copy(v1.begin()+3, v1.end(), v3.begin());
    print(std::cout, v3);
    // Forma #2
    std::vector<int> v4;
    v4.reserve(v1.size());
    std::copy(v1.begin()+3, v1.end(), std::back_inserter(v4));
    print(std::cout, v4);
    // Forma #3
    std::vector<int> v5;
    v5.reserve(v1.size());
    std::copy_if(v1.begin(), v1.end(), std::back_inserter(v5), EsPar);
    print(std::cout, v5);
    // Forma #4
    std::vector<int> v6;
    v6.reserve(v1.size());
    std::copy_if(v1.begin(), v1.end(), std::back_inserter(v6),
                 [](auto item){ return item % 2 != 0; });
    print(std::cout, v6);
    // Forma #5
    std::list<int> l1 = {1, 2, 3, 4, 5, 6, 7};;
    std::vector<int> v7;
    v7.reserve(l1.size());

    std::copy(std::next(l1.begin(),3), l1.end(), std::back_inserter(v7));
    print(std::cout, v7);
}

template<typename T>
struct Greater {
    bool operator()(T a, T b) const { return a > b; }
};


void ejemplo_sort() {
    std::vector<int> v1(20);
    std::iota(v1.begin(), v1.end(), 1);

    std::random_device rd;     // Es el dispositivo de randorizacion (Ejemplo los Dados)
    std::mt19937 g(rd());   // El motor de randorizacion
    print(std::cout, v1);
    std::shuffle(v1.begin(), v1.end(), g);
    print(std::cout, v1);
    std::sort(v1.begin(), v1.end(), std::less{});
    print(std::cout, v1);
    std::sort(v1.begin(), v1.end(), Greater<int>{});
    print(std::cout, v1);
}

void ejemplo_accumulate() {
    std::ifstream file("data.txt");
    if (file.fail()) {
        std::cout << "Archivo Incorrecto";
        return;
    }
    std::vector<int> v1;
    int item = 0;
    while (file >> item) {
        v1.emplace_back(item);
    }

    print(std::cout, v1);

    auto total = std::accumulate(v1.begin(), v1.end(), 0);
    std::cout << total << std::endl;
}

void ejemplo_accumulate_2() {
    std::ifstream file("data.txt");
    if (file.fail()) {
        std::cout << "Archivo Incorrecto";
        return;
    }
    std::vector<int> v1;
    std::copy(
            std::istream_iterator<int>(file),
            std::istream_iterator<int>(),
            std::back_inserter(v1));
//    int item = 0;
//    while (file >> item) {
//        v1.emplace_back(item);
//    }

    print(std::cout, v1);

    auto total = std::accumulate(v1.begin(), v1.end(), 0);
    std::cout << total << std::endl;
}

void ejemplo_accumulate_3() {
    std::ifstream file("data.txt");
    if (file.fail()) {
        std::cout << "Archivo Incorrecto";
        return;
    }
    auto total_sum = std::accumulate(
            std::istream_iterator<long long>(file),
            std::istream_iterator<long long>(), 0ll);

    file.clear();
    file.seekg(0);
    auto total_multiple = std::accumulate(
            std::istream_iterator<int>(file),
            std::istream_iterator<int>(), 1, std::multiplies{});

    std::cout << total_sum << " " << total_multiple << std::endl;
}


int main() {
//    ejemplo_copy();
//    ejemplo_sort();
//    ejemplo_accumulate();
//    ejemplo_accumulate_2();
    ejemplo_accumulate_3();
    return 0;
}
