#include "test_matrix.hpp"
#include "matrix.hpp"

// Тест для конструктора и преобразования в CSR
void test_constructor_and_csr() {
    std::vector<std::vector<double>> input_matrix = {
        {5, 0, 0},
        {0, 8, 0},
        {3, 0, 6}
    };
    Matrix matrix(input_matrix);

    // Проверяем CSR представление
    std::vector<double> expected_values = {5, 8, 3, 6};
    std::vector<uint16_t> expected_column_idx = {0, 1, 0, 2};
    std::vector<uint16_t> expected_row_ptr = {0, 1, 2, 4};

    CU_ASSERT_EQUAL(matrix.get_values().size(), expected_values.size());
    for (size_t i = 0; i < expected_values.size(); i++) {
        CU_ASSERT_DOUBLE_EQUAL(matrix.get_values()[i], expected_values[i], 1e-9);
        CU_ASSERT_EQUAL(matrix.get_column_idx()[i], expected_column_idx[i]);
    }
    CU_ASSERT_EQUAL(matrix.get_row_ptr().size(), expected_row_ptr.size());
    for (size_t i = 0; i < expected_row_ptr.size(); i++) {
        CU_ASSERT_EQUAL(matrix.get_row_ptr()[i], expected_row_ptr[i]);
    }
}

// Тест для функции get_trace
void test_get_trace() {
    std::vector<std::vector<double>> input_matrix = {
        {5, 0, 0},
        {0, 8, 0},
        {3, 0, 6}
    };
    Matrix matrix(input_matrix);

    double trace = matrix.get_trace();
    CU_ASSERT_DOUBLE_EQUAL(trace, 19.0, 1e-9);
}

// Тест для функции get_element
void test_get_element() {
    std::vector<std::vector<double>> input_matrix = {
        {5, 0, 0},
        {0, 8, 0},
        {3, 0, 6}
    };
    Matrix matrix(input_matrix);

    CU_ASSERT_DOUBLE_EQUAL(matrix.get_element(1, 1), 5.0, 1e-9);
    CU_ASSERT_DOUBLE_EQUAL(matrix.get_element(2, 2), 8.0, 1e-9);
    CU_ASSERT_DOUBLE_EQUAL(matrix.get_element(3, 3), 6.0, 1e-9);
    CU_ASSERT_DOUBLE_EQUAL(matrix.get_element(1, 2), 0.0, 1e-9);
}

// Тест для функции get_determinant
void test_get_determinant() {
    std::vector<std::vector<double>> input_matrix = {
        {2, 3, 1},
        {4, 1, 3},
        {3, 2, 4}
    };
    Matrix matrix(input_matrix);

    double determinant = matrix.get_determinant();
    CU_ASSERT_DOUBLE_EQUAL(determinant, -20.0, 1e-9);
}

// Тест для умножения на скаляр
void test_scalar_multiplication() {
    std::vector<std::vector<double>> input_matrix = {
        {1, 0, 0},
        {0, 2, 0},
        {0, 0, 3}
    };
    Matrix matrix(input_matrix);

    matrix = matrix * 2.0;
    CU_ASSERT_DOUBLE_EQUAL(matrix.get_element(1, 1), 2.0, 1e-9);
    CU_ASSERT_DOUBLE_EQUAL(matrix.get_element(2, 2), 4.0, 1e-9);
    CU_ASSERT_DOUBLE_EQUAL(matrix.get_element(3, 3), 6.0, 1e-9);
}

// Тест для умножения матриц
void test_matrix_multiplication() {
    std::vector<std::vector<double>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<std::vector<double>> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    Matrix mat1(matrix1);
    Matrix mat2(matrix2);

    Matrix result = mat1 * mat2;

    std::vector<std::vector<double>> expected = {
        {30, 24, 18},
        {84, 69, 54},
        {138, 114, 90}
    };

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            CU_ASSERT_DOUBLE_EQUAL(result.get_element(i + 1, j + 1), expected[i][j], 1e-9);
        }
    }
}

// Тест для сложения матриц
void test_matrix_addition() {
    std::vector<std::vector<double>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    std::vector<std::vector<double>> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };
    Matrix mat1(matrix1);
    Matrix mat2(matrix2);

    Matrix result = mat1 + mat2;

    std::vector<std::vector<double>> expected = {
        {10, 10, 10},
        {10, 10, 10},
        {10, 10, 10}
    };

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            CU_ASSERT_DOUBLE_EQUAL(result.get_element(i + 1, j + 1), expected[i][j], 1e-9);
        }
    }
}

// Тест преобразования CSR обратно в базовый формат
void test_csr_to_basic() {
    std::vector<std::vector<double>> input_matrix = {
        {5, 0, 0},
        {0, 8, 0},
        {3, 0, 6}
    };
    Matrix matrix(input_matrix);

    std::vector<std::vector<double>> basic_matrix = matrix.get_matrix();

    for (size_t i = 0; i < input_matrix.size(); i++) {
        for (size_t j = 0; j < input_matrix[0].size(); j++) {
            CU_ASSERT_DOUBLE_EQUAL(basic_matrix[i][j], input_matrix[i][j], 1e-9);
        }
    }
}