#include "matrix.hpp"

#include <iostream>

Matrix::Matrix(const std::vector<std::vector<double>>& input_matrix)
    : _isSquareMatrix(input_matrix.size() == input_matrix[0].size()), _count_rows(input_matrix.size()),
        _count_cols(input_matrix[0].size()) {
    _transform_basic_to_csr(input_matrix);
}

double Matrix::get_trace() const {
    double trace = 0.0;
    if (!_isSquareMatrix) {
        std::cout << "[LOG] [WARNING] It is not a square matrix!\n";
        return trace;
    }
    for (uint16_t j = 0; j < _count_rows; j++) {
        const uint16_t start_idx = _row_ptr[j];
        const uint16_t end_idx = _row_ptr[j + 1];
        for (uint16_t i = start_idx; i < end_idx; i++) {
            if (_column_idx[i] == j) {
                trace += _values[i];
                break;
            }
        }
    }
    return trace;
}

double Matrix::get_element(int row, int col) const {
    row--;
    col--;
    const uint16_t start_idx = _row_ptr[row];
    const uint16_t end_idx = _row_ptr[row + 1];
    for (uint16_t i = start_idx; i < end_idx; i++) {
        if (_column_idx[i] == col) {
            return _values[i];
        }
    }
    return 0.0;
}

double Matrix::get_determinant() const {
    if (!_isSquareMatrix) {
        std::cout << "[LOG] [WARNING] It is not a square matrix!\n";
    }
    return _determinant_recursive(get_matrix());
}

Matrix Matrix::operator*(const double scalar) {
    for (uint16_t i = 0; i < _values.size(); i++) {
        _values[i] *= scalar;
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &other) const {
    std::vector<std::vector<double>> current_matrix = this->get_matrix();
    const std::vector<std::vector<double>> other_matrix = other.get_matrix();
    if (current_matrix[0].size() != other_matrix.size()) {
        std::cout << "[LOG] [ERROR] Matrices cannot be multiplied: inconsistent sizes!\n";
    }
    const uint16_t rows = current_matrix.size();
    const uint16_t cols = other_matrix[0].size();
    const uint16_t common_dim = current_matrix[0].size();
    std::vector result_matrix(rows, std::vector(cols, 0.0));
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            for (size_t k = 0; k < common_dim; ++k) {
                result_matrix[i][j] += current_matrix[i][k] * other_matrix[k][j];
            }
        }
    }
    return Matrix(result_matrix);
}

Matrix Matrix::operator+(const Matrix &other) const {
    std::vector<std::vector<double>> current_matrix = this->get_matrix();
    const std::vector<std::vector<double>> other_matrix = other.get_matrix();
    for (uint16_t j = 0; j < current_matrix.size(); j++) {
        for (uint16_t i = 0; i < current_matrix[0].size(); i++) {
            current_matrix[j][i] += other_matrix[j][i];
        }
    }
    return Matrix(current_matrix);
}

void Matrix::_transform_basic_to_csr(const std::vector<std::vector<double>>& input_matrix) {
    if (input_matrix.empty()) return;
    _row_ptr.push_back(0);
    for (uint16_t j = 0; j < input_matrix.size(); j++) {
        const uint16_t row_size = input_matrix[j].size();
        for (uint16_t i = 0; i < row_size; i++) {
            if (input_matrix[j][i] != 0) {
                _values.push_back(input_matrix[j][i]);
                _column_idx.push_back(i);
            }
        }
        _row_ptr.push_back(_values.size());
    }
}

std::vector<std::vector<double>> Matrix::_transform_csr_to_basic() const {
    std::vector output_matrix(_count_rows, std::vector(_count_cols, 0.0));
    for (uint16_t j = 0; j < _count_rows; j++) {
        const uint16_t start_idx = _row_ptr[j];
        const uint16_t end_idx = _row_ptr[j + 1];
        for (uint16_t i = start_idx; i < end_idx; i++) {
            output_matrix[j][_column_idx[i]] = _values[i];
        }
    }
    return output_matrix;
}

double Matrix::_determinant_recursive(const std::vector<std::vector<double>>& matrix) const {
    uint16_t n = matrix.size();
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    double det = 0.0;
    for (uint16_t col = 0; col < n; col++) {
        std::vector<std::vector<double>> minor_matrix;
        for (uint16_t i = 1; i < n; i++) {
            std::vector<double> row;
            for (uint16_t j = 0; j < n; j++) {
                if (j != col) {
                    row.push_back(matrix[i][j]);
                }
            }
            minor_matrix.push_back(row);
        }
        det += (col % 2 == 0 ? 1 : -1) * matrix[0][col] * _determinant_recursive(minor_matrix);
    }
    return det;
}
