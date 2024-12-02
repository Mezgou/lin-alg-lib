#pragma once

#include "../matrix/matrix.hpp"

#include <vector>

template<typename T>
static void print_vector(const std::vector<T>& input_vector) {
    std::cout << "PrintVector=================\n";
    std::cout << "[ ";
    for (const T element : input_vector) {
        std::cout << element << " ";
    }
    std::cout << "]\n";
    std::cout << "============================\n";
}

static void print_matrix(const Matrix& input_matrix) {
    std::cout << "PrintMatrix=================\n";
    for (const std::vector<double>& row : input_matrix.get_matrix()) {
        for (const double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << "============================\n";
}