#include <iostream>

#include "matrix/matrix.hpp"
#include "matrix/test_matrix.hpp"
#include "utils/utility_func.hpp"

int main() {
#ifndef NDEBUG
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
    const auto matrix = Matrix(input_matrix);
    print_vector(matrix.get_values());
    print_vector(matrix.get_column_idx());
    print_vector(matrix.get_row_ptr());
    print_matrix(matrix);
    std::cout << matrix.is_square_matrix() << std::endl;
    std::cout << matrix.get_trace() << std::endl;
    std::cout << matrix.get_element(2, 2) << std::endl;
    const std::vector<std::vector<double>> other_input_matrix({
        {1, 0},
        {0, 1},
        {4, 5}
    });
    const auto other_matrix = Matrix(other_input_matrix);
    print_matrix(matrix + other_matrix);
    print_matrix(matrix * other_matrix);
    double det = matrix.get_determinant();
    if (det != 0) {
        std::cout << "The matrix is reversible, the determinant: " << det << std::endl;
    } else {
        std::cout << "The matrix is irreversible, the determinant is zero." << std::endl;
    }
}