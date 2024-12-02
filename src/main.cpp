#include <iostream>

#include "matrix/matrix.hpp"
#include "utils/utility_func.hpp"

int main() {
#ifndef NDEBUG
    std::cout << "Tests..." << std::endl;
#endif
    std::vector<std::vector<double>> input_matrix = {
        {0.0, 0.0, 3.0, 0.0},
        {0.0, 0.0, 0.0, 4.0},
        {5.0, 0.0, 0.0, 6.0}
    };
    Matrix matrix = Matrix(input_matrix);
    print_vector(matrix.get_values());
    print_vector(matrix.get_column_idx());
    print_vector(matrix.get_row_ptr());
    print_matrix(matrix);
}