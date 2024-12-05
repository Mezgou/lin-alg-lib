#pragma once

#include <vector>
#include <cstdint>

class Matrix {
public:
    explicit Matrix(const std::vector<std::vector<double>>& input_matrix);
    explicit Matrix(const std::vector<double>& values, const std::vector<uint16_t>& column_idx, const std::vector<uint16_t>& row_ptr, bool isSquareMatrix, uint16_t rows, uint16_t cols);
    ~Matrix() = default;

    std::vector<std::vector<double>> get_matrix() const { return _transform_csr_to_basic(); }
    std::vector<double> get_values() const { return _values; }
    std::vector<uint16_t> get_column_idx() const { return _column_idx; }
    std::vector<uint16_t> get_row_ptr() const { return _row_ptr; }

    uint16_t get_count_rows() const { return _count_rows; }
    uint16_t get_count_cols() const { return _count_cols; }

    bool is_square_matrix() const { return _isSquareMatrix; }

    double get_trace() const;
    double get_element(int row, int col) const;
    double get_determinant() const;

    Matrix operator*(double scalar);
    Matrix operator*(const Matrix& other) const;
    Matrix operator+(const Matrix& other) const;
private:
    void _transform_basic_to_csr(const std::vector<std::vector<double>>& input_matrix);
    std::vector<std::vector<double>> _transform_csr_to_basic() const;

    static double _determinant_recursive(const std::vector<std::vector<double>>& matrix);

    std::vector<double> _values;
    std::vector<uint16_t> _column_idx;
    std::vector<uint16_t> _row_ptr;

    bool _isSquareMatrix;

    uint16_t _count_rows;
    uint16_t _count_cols;
};
