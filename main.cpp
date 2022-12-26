/*
 * TODO Создать объектную модель игры BattleCity
 * 3. Используя средства языка описать объектную модель игры BattleCity.
 * (Танк, Снаряд, Штаб, Препятствие: {Лед, Вода, Стена: {Железная, Каменная}}.
 * Реализовать pure abstract классы (интерфейсы, описание методов без реализации а данных).
 * Описания в отдельных *.h файлах с защитой от включения (pragma or #define).
 * По возможности использовать наследование.
 */

#include <iostream>
#include <vector>
#include <valarray>

int main() {

    std::vector<std::array<int, 10>> matrix {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
            {10, 11, 12},
            {13, 14, 15}
    };

    auto elem_3_2 = matrix[3][2];
    std::cout << elem_3_2 << std::endl;
    matrix.at(1).at(1) = elem_3_2;
    std::cout << matrix.at(1).at(1) << std::endl;
    std::cout << matrix.capacity() << " " << std::endl;

    return 0;
}
