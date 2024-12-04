#pragma once

#include "../matrix/matrix.h"

#include <vector>
#include <iostream>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"

#define LOG(title, x) std::cout << title << ": " << x << "\n"

#ifdef _WIN32
#include <windows.h>

inline void enable_ansi_support() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

static void print_test_result(const CU_pSuite& suite) {
    const unsigned int failures = CU_get_number_of_failures();
    const unsigned int tests = CU_get_number_of_tests_run();
    const unsigned int passed = tests - failures;

    std::cout << CYAN << "----------------------------------------" << RESET << std::endl;
    std::cout << CYAN << "Recruitment Tests: " << suite->pName << RESET << std::endl;
    std::cout << "Total tests: " << tests << std::endl;
    std::cout << GREEN << "Successful: " << passed << RESET << std::endl;
    if (failures > 0) {
        std::cout << RED << "Failed: " << failures << RESET << std::endl;
    } else {
        std::cout << GREEN << "All tests have been successfully passed!" << RESET << std::endl;
    }
    std::cout << CYAN << "----------------------------------------" << RESET << std::endl;
}

template<typename T>
static void print_vector(const std::vector<T>& input_vector, const std::string& title) {
    std::string util_string = "--";
    std::cout << title << util_string << "\n";
    std::cout << "[ ";
    for (const T element : input_vector) {
        std::cout << element << " ";
    }
    std::cout << "]\n";
    const uint16_t count_for_add = title.size();
    for (uint16_t i = 0; i < count_for_add; i++) {
        util_string += "-";
    }
    std::cout << util_string << "\n";
}

static void print_matrix(const Matrix& input_matrix, const std::string& title) {
    std::string util_string = "--";
    std::cout << title << util_string << "\n";
    for (const std::vector<double>& row : input_matrix.get_matrix()) {
        for (const double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
    const uint16_t count_for_add = title.size();
    for (uint16_t i = 0; i < count_for_add; i++) {
        util_string += "-";
    }
    std::cout << util_string << "\n";
}

static std::vector<std::vector<double>> read_matrix() {
    uint16_t n, m;
    std::cout << "Enter the dimensions of the matrix (N and M): ";
    std::cin >> n >> m;
    std::vector input_matrix(n, std::vector(m, 0.0));
    std::cout << "Enter the elements of the matrix (N rows of M elements): ";
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            std::cin >> input_matrix[i][j];
        }
    }
    return input_matrix;
}
