#include <iostream>

#include "matrix/matrix.hpp"
#include "utils/utility_func.hpp"

int main() {
#ifndef NDEBUG
    std::cout << "Tests..." << std::endl;
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
}