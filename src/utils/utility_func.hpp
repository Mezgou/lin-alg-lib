#pragma once

#include "../matrix/matrix.hpp"

#include <vector>
#include <iostream>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"

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
static void print_vector(const std::vector<T>& input_vector) {
    std::cout << "PrintVector-----------------\n";
    std::cout << "[ ";
    for (const T element : input_vector) {
        std::cout << element << " ";
    }
    std::cout << "]\n";
    std::cout << "----------------------------\n";
}

static void print_matrix(const Matrix& input_matrix) {
    std::cout << "PrintMatrix-----------------\n";
    for (const std::vector<double>& row : input_matrix.get_matrix()) {
        for (const double element : row) {
            std::cout << element << " ";
        }
        std::cout << "\n";
    }
    std::cout << "----------------------------\n";
}