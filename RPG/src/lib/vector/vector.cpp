/*
** BENSUPERPC PROJECT, 2020
** CPU
** File description:
** vector.cpp
*/

#include "vector.hpp"

void vector::fill_row(std::vector<int> &row)
{
    std::generate(row.begin(), row.end(), []() { return rand() % 100; });
}

void vector::fill_matrix_1(std::vector<std::vector<int>> &mat)
{
    std::for_each(mat.begin(), mat.end(), fill_row);
}

void vector::fill_matrix_2(std::vector<std::vector<int>> &Matrix)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    // std::vector<std::vector<int>> Matrix(5, std::vector<int>(7, 0));

    for (auto it1 = Matrix.begin(); it1 != Matrix.end(); it1++) {
        for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
            *it2 = dis(gen);
        }
    }
}

void vector::fill_matrix_2(std::vector<std::vector<int>> &Matrix, int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    // std::vector<std::vector<int>> Matrix(5, std::vector<int>(7, 0));

    for (auto it1 = Matrix.begin(); it1 != Matrix.end(); it1++) {
        for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
            *it2 = dis(gen);
        }
    }
}

void vector::print_2d(std::vector<std::vector<int>> &mat)
{
    for (const auto &y : mat) {
        for (const auto &x : y) {
            std::cout << std::setw(4) << x;
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> vector::generate_matrix(size_t x, size_t y)
{
    std::vector<std::vector<int>> matrix(x, std::vector<int>(y, 0));
    return matrix;
}

std::vector<std::vector<int>> vector::generate_matrix(size_t x, size_t y, int z)
{
    std::vector<std::vector<int>> matrix(x, std::vector<int>(y, z));
    return matrix;
}

void vector::cache_unfriendly_copy(std::vector<std::vector<int>> &mat1, std::vector<std::vector<int>> &mat2)
{
    for (unsigned int x = 0; x < mat1[0].size(); ++x) {

        for (unsigned int y = 0; y < mat1.size(); ++y) {
            mat1[y][x] = mat2[y][x];
        }
    }
}

void vector::cache_friendly_copy(std::vector<std::vector<int>> &mat1, std::vector<std::vector<int>> &mat2)
{
    for (unsigned int y = 0; y < mat1.size(); ++y) {
        for (unsigned int x = 0; x < mat1[0].size(); ++x) {
            mat1[y][x] = mat2[y][x];
        }
    }
}