#include <iostream>
#include <cmath>

#include "matrix.h"
#include "test_matrix.h"
#include "utility_func.h"

int main() {
#ifndef NDEBUG
#ifdef _WIN32
    enable_ansi_support();
#endif
    if (CU_initialize_registry() != CUE_SUCCESS) {
        std::cerr << RED << "Failed to initialize the test registry!" << RESET << std::endl;
        return CU_get_error();
    }

    const CU_pSuite suite = CU_add_suite("MatrixTests", nullptr, nullptr);
    if (!suite) {
        CU_cleanup_registry();
        std::cerr << RED << "Error adding the test set!" << RESET << std::endl;
        return CU_get_error();
    }

    // Добавление тестов
    if (!CU_add_test(suite, "test_get_element", test_get_element) ||
        !CU_add_test(suite, "test_get_trace", test_get_trace) ||
        !CU_add_test(suite, "test_get_determinant", test_get_determinant) ||
        !CU_add_test(suite, "test_operator_scalar_multiply", test_scalar_multiplication) ||
        !CU_add_test(suite, "test_operator_matrix_multiply", test_matrix_multiplication) ||
        !CU_add_test(suite, "test_operator_add", test_matrix_addition) ||
        !CU_add_test(suite, "test_csr_to_basic", test_csr_to_basic) ||
        !CU_add_test(suite, "test_constructor_and_csr", test_constructor_and_csr)) {
        CU_cleanup_registry();
        std::cerr << RED << "Error adding tests!" << RESET << std::endl;
        return CU_get_error();
        }
    CU_basic_set_mode(CU_BRM_NORMAL);
    std::cout << CYAN << "Run tests..." << RESET << std::endl;
    CU_basic_run_tests();

    print_test_result(suite);
    CU_cleanup_registry();
#endif
    // Task #1
    LOG("Task", 1);
    std::cout << "Entering one matrices for first task:\n";
    const auto matrix = Matrix(read_matrix());
    print_vector(matrix.get_values(), "Values");
    print_vector(matrix.get_column_idx(), "ColumnIndices");
    print_vector(matrix.get_row_ptr(), "Row pointers");
    LOG("TraceMatrix", matrix.get_trace());
    uint16_t i, j;
    std::cout << "Enter the position of the item you want to receive: ";
    std::cin >> j >> i;
    LOG("GetElement", matrix.get_element(j, i));

    // Task #2
    LOG("Task", 2);
    std::cout << "Entering two matrices for addition:\n";
    auto first_matrix = Matrix(read_matrix());
    auto second_matrix = Matrix(read_matrix());
    print_matrix(first_matrix + second_matrix, "Addition");
    std::cout << "Entering one matrices for scalar multiplication:\n";
    first_matrix = Matrix(read_matrix());
    double scalar;
    std::cout << "Enter scalar: ";
    std::cin >> scalar;
    print_matrix(first_matrix * scalar, "ScalarMultiplication");
    std::cout << "Entering two matrices for multiplication:\n";
    first_matrix = Matrix(read_matrix());
    second_matrix = Matrix(read_matrix());
    print_matrix(first_matrix * second_matrix, "MatrixMultiplication");

    // Task #3
    LOG("Task", 3);
    std::cout << "Entering one matrices for third task:\n";
    const auto matrix_for_search_det = Matrix(read_matrix());
    const double determinant = matrix_for_search_det.get_determinant();
    constexpr double EPSILON = 1e-9;
    LOG("Determinant", determinant);
    const char* result = std::fabs(determinant) < EPSILON ? "no" : "yes";
    std::cout << "Is there a matrix that is the inverse of this one? " << result << "\n";
}