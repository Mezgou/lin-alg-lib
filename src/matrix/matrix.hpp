#pragma once

#include <vector>
#include <cstdint>

class Matrix {
public:
    Matrix(const std::vector<std::vector<double>>& input_matrix);
    ~Matrix() = default;

    inline std::vector<std::vector<double>> get_matrix() const { return _transform_csr_to_basic(); }
    inline std::vector<double> get_values() const { return _values; }
    inline std::vector<uint16_t> get_column_idx() const { return _column_idx; }
    inline std::vector<uint16_t> get_row_ptr() const { return _row_ptr; }
private:
    void _transform_basic_to_csr(const std::vector<std::vector<double>>& input_matrix);
    const std::vector<std::vector<double>> _transform_csr_to_basic() const;

    std::vector<double> _values;
    std::vector<uint16_t> _column_idx;
    std::vector<uint16_t> _row_ptr;

    uint16_t _count_rows;
    uint16_t _count_cols;
};
