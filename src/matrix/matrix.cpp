#include "matrix.hpp"

Matrix::Matrix(const std::vector<std::vector<double>>& input_matrix)
    : _count_rows(input_matrix.size()), _count_cols(input_matrix[0].size())
{
    _transform_basic_to_csr(input_matrix);
}

void Matrix::_transform_basic_to_csr(const std::vector<std::vector<double>>& input_matrix)
{
    if (input_matrix.empty()) return;
    _row_ptr.push_back(0);
    for (uint16_t j = 0; j < input_matrix.size(); j++) {
        uint16_t row_size = input_matrix[j].size();
        for (uint16_t i = 0; i < row_size; i++) {
            if (input_matrix[j][i] != 0) {
                _values.push_back(input_matrix[j][i]);
                _column_idx.push_back(i);
            }
        }
        _row_ptr.push_back(_values.size());
    }
}

const std::vector<std::vector<double>> Matrix::_transform_csr_to_basic() const
{
    std::vector<std::vector<double>> output_matrix(_count_rows, std::vector<double>(_count_cols, 0.0));
    for (uint16_t j = 0; j < _count_rows; j++) {
        uint16_t start_idx = _row_ptr[j];
        uint16_t end_idx = _row_ptr[j + 1];
        for (uint16_t i = start_idx; i < end_idx; i++) {
            output_matrix[j][_column_idx[i]] = _values[i];
        }
    }
    return output_matrix;
}
