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
        std::cout << "It is not a square matrix.\n";
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
