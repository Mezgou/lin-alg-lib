#include "matrix.h"

#include <iostream>
#include <unordered_map>

/**
 * @brief Конструктор матрицы. Преобразует базовый формат матрицы в CSR-формат.
 * @param input_matrix Базовая матрица (в виде двумерного вектора).
 *
 * @details
 * **Математическое обоснование:**
 * В базовом формате каждая строка содержит все элементы, включая нули.
 * CSR-формат (Compressed Sparse Row) сохраняет:
 * 1. Только ненулевые элементы матрицы в массиве `_values`.
 * 2. Индексы столбцов для каждого элемента в массиве `_column_idx`.
 * 3. Границы строк в массиве `_row_ptr`. Например:
 *    - Если первая строка содержит 2 ненулевых элемента, `_row_ptr[1]` указывает на конец этих элементов.
 *
 * **Применение:**
 * Используется для экономии памяти и ускорения работы с разреженными матрицами.
 */
Matrix::Matrix(const std::vector<std::vector<double>>& input_matrix)
    : _isSquareMatrix(input_matrix.size() == input_matrix[0].size()), _count_rows(input_matrix.size()),
        _count_cols(input_matrix[0].size()) {
    _transform_basic_to_csr(input_matrix);
}

Matrix::Matrix(const std::vector<double> &values, const std::vector<uint16_t> &column_idx, const std::vector<uint16_t> &row_ptr, bool isSquareMatrix, uint16_t rows, uint16_t cols)
    : _values(values), _column_idx(column_idx), _row_ptr(row_ptr), _isSquareMatrix(isSquareMatrix),
    _count_rows(rows), _count_cols(cols) {
}

/**
 * @brief Вычисляет след матрицы (сумму диагональных элементов).
 * @return Значение следа. Если матрица не квадратная, возвращает 0 и выводит предупреждение.
 *
 * @details
 * **Математическое обоснование:**
 * След матрицы — это сумма элементов, расположенных на её главной диагонали (элементы с одинаковыми номерами строки и столбца).
 * Например, для квадратной матрицы размером 3x3:
 * - Диагональные элементы: A[0][0], A[1][1], A[2][2].
 * - След: сумма этих элементов.
 *
 * **Алгоритм:**
 * 1. Проверяем, квадратная ли матрица.
 * 2. Для каждой строки ищем диагональный элемент (индекс столбца совпадает с номером строки).
 * 3. Если элемент найден, добавляем его к сумме.
 */
double Matrix::get_trace() const {
    double trace = 0.0;
    if (!_isSquareMatrix) {
        std::cout << "[LOG] [WARNING] It is not a square matrix! ";
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

/**
 * @brief Возвращает элемент матрицы по указанным строке и столбцу.
 * @param row Строка (1-индексация).
 * @param col Столбец (1-индексация).
 * @return Значение элемента или 0.0, если элемент отсутствует в CSR-представлении.
 *
 * @details
 * **Математическое обоснование:**
 * В CSR-представлении матрицы хранятся только ненулевые элементы.
 * Чтобы найти конкретный элемент:
 * 1. Смотрим диапазон ненулевых элементов строки (между `_row_ptr[row]` и `_row_ptr[row+1]`).
 * 2. Проверяем, есть ли среди них элемент с нужным индексом столбца. Если есть, возвращаем его значение. Если нет, возвращаем 0.
 */
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

/**
 * @brief Вычисляет определитель матрицы (рекурсивным методом).
 * @return Определитель матрицы. Если матрица не квадратная, возвращает предупреждение.
 *
 * @details
 * **Математическое обоснование:**
 * Определитель матрицы вычисляется через разложение по строке. Например:
 * - Для матрицы размера 2x2 определитель равен: det(A) = A[0][0] * A[1][1] - A[0][1] * A[1][0]
 *
 * - Для матрицы большего размера:
 *   1. Выбираем строку (обычно первую).
 *   2. Для каждого элемента этой строки вычисляем минор — матрицу, полученную удалением строки и столбца текущего элемента.
 *   3. Определитель равен чередующейся сумме произведений элемента строки на определитель его минора.
 *
 * **Алгоритм:**
 * 1. Если матрица 1x1, возвращаем её единственный элемент.
 * 2. Если 2x2, вычисляем определитель напрямую.
 * 3. Для матрицы больше 2x2:
 *    - Создаём минор для каждого элемента первой строки.
 *    - Рекурсивно вычисляем определитель минора.
 *    - Учитываем знак (положительный для чётных столбцов, отрицательный для нечётных).
 */
double Matrix::get_determinant() const {
    if (!_isSquareMatrix) {
        std::cout << "[LOG] [WARNING] It is not a square matrix!\n";
    }
    return _determinant_recursive(get_matrix());
}

/**
 * @brief Умножает текущую матрицу на заданный скаляр.
 *
 * Математический принцип:
 * Умножение матрицы на скаляр — это умножение каждого элемента матрицы на одно и то же число.
 * Формула для элемента:
 * A'[i][j] = A[i][j] * scalar
 *
 * Алгоритм:
 * 1. Итерируемся по массиву _values, который содержит ненулевые элементы матрицы в формате CSR.
 * 2. Умножаем каждый элемент на скаляр.
 * 3. Возвращаем модифицированную матрицу.
 *
 * @param scalar Число, на которое нужно умножить матрицу.
 * @return Матрица после умножения.
 */
Matrix Matrix::operator*(const double scalar) {
    for (uint16_t i = 0; i < _values.size(); i++) {
        _values[i] *= scalar;
    }
    return *this;
}

/**
 * @brief Умножает текущую матрицу на другую матрицу.
 *
 * Математический принцип:
 * Произведение двух матриц возможно, если число столбцов первой матрицы равно числу строк второй.
 * Формула для элемента результирующей матрицы:
 * C[i][j] = Σ (A[i][k] * B[k][j]) по k = 0... N,
 * где A - текущая матрица, B - другая матрица.
 *
 * Алгоритм:
 * 1. Проверяем размерности матриц.
 * 2. Создаём результирующую матрицу размером (строки A) x (столбцы B).
 * 3. Для каждого элемента результирующей матрицы:
 *    a. Вычисляем сумму произведений соответствующих элементов строки из A и столбца из B.
 * 4. Возвращаем новую матрицу.
 *
 * @param other Матрица, с которой производится умножение.
 * @return Результат умножения матриц.
 */
Matrix Matrix::operator*(const Matrix &other) const {
    std::vector<std::vector<double>> current_matrix = this->get_matrix();
    const std::vector<std::vector<double>> other_matrix = other.get_matrix();
    if (current_matrix[0].size() != other_matrix.size()) {
        std::cout << "[LOG] [ERROR] Matrices cannot be multiplied: inconsistent sizes! ";
        return Matrix(std::vector<std::vector<double>>{{0}});
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

/**
 * @brief Складывает текущую матрицу с другой матрицей в формате CSR.
 *
 * Математический принцип:
 * Сложение матриц выполняется поэлементно. Элементы, находящиеся в одном и том же
 * столбце и строке, суммируются. Ненулевые элементы сохраняются в результирующей матрице.
 * Формула для элемента:
 * C[i][j] = A[i][j] + B[i][j], если i, j принадлежат ненулевым элементам A или B.
 *
 * Алгоритм:
 * 1. Проверяем, что размеры матриц совпадают (количество строк и столбцов одинаково).
 * 2. Инициализируем временное хранилище для ненулевых элементов результирующей строки.
 * 3. Проходим по строкам обеих матриц.
 *    3.1. Извлекаем ненулевые элементы текущей строки первой матрицы и добавляем их в временное хранилище.
 *    3.2. Извлекаем ненулевые элементы текущей строки второй матрицы и добавляем их в хранилище,
 *         суммируя элементы в совпадающих столбцах.
 * 4. Переносим ненулевые элементы из временного хранилища в результирующую матрицу.
 * 5. Формируем новый массив смещений строк для результирующей матрицы.
 * 6. Возвращаем новую матрицу в формате CSR.
 *
 * @param other Матрица, с которой производится сложение.
 * @return Результат сложения матриц в формате CSR.
 */
Matrix Matrix::operator+(const Matrix &other) const {
    if (this->get_count_rows() != other.get_count_rows() || this->get_count_cols() != other.get_count_cols()) {
        std::cerr << "[LOG] [ERROR] Matrices cannot be added: inconsistent sizes!" << std::endl;
        return Matrix(std::vector<std::vector<double>>{{0}});
    }

    std::vector<double> result_values;
    std::vector<uint16_t> result_columns;
    std::vector<uint16_t> result_row_offsets = {0};

    for (uint16_t row = 0; row < this->get_count_rows(); ++row) {
        std::unordered_map<uint16_t, double> row_sum;

        // Сложение элементов текущей строки из первой матрицы
        for (uint16_t i = this->get_row_ptr()[row]; i < this->get_row_ptr()[row + 1]; ++i) {
            row_sum[this->get_column_idx()[i]] += this->get_values()[i];
        }

        // Сложение элементов текущей строки из второй матрицы
        for (uint16_t i = other.get_row_ptr()[row]; i < other.get_row_ptr()[row + 1]; ++i) {
            row_sum[other.get_column_idx()[i]] += other.get_values()[i];
        }

        // Добавляем ненулевые элементы в результирующую матрицу
        for (const auto &[col, value] : row_sum) {
            if (value != 0.0) { // Учитываем только ненулевые элементы
                result_columns.push_back(col);
                result_values.push_back(value);
            }
        }

        // Обновляем row_offsets
        result_row_offsets.push_back(result_columns.size());
    }
    return Matrix(result_values, result_columns, result_row_offsets,
        this->get_count_rows() == this->get_count_cols(), this->get_count_rows(), this->get_count_cols());
}

/**
 * @brief Преобразует базовый формат матрицы в CSR-формат.
 * @param input_matrix Базовая матрица (двумерный вектор).
 *
 * @details
 * **Математическое обоснование:**
 * В CSR мы храним только ненулевые элементы. Например:
 * - Матрица:
 *   ```
 *   [5, 0, 0]
 *   [0, 8, 0]
 *   [3, 0, 6]
 *   ```
 * - В CSR:
 *   - `_values`: [5, 8, 3, 6]
 *   - `_column_idx`: [0, 1, 0, 2]
 *   - `_row_ptr`: [0, 1, 2, 4]
 */
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

/**
 * @brief Преобразует CSR-формат обратно в базовый вид (двумерный вектор).
 * @return Базовая матрица.
 *
 * @details
 * **Математическое обоснование:**,
 * Чтобы вернуть матрицу в базовый вид, заполняем матрицу нулями, а затем добавляем элементы из CSR:
 * - Для строки `j` берём диапазон ненулевых элементов из `_row_ptr`.
 * - Для каждого элемента по индексу `_column_idx` ставим его значение из `_values`.
 */
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

/**
 * @brief Вычисляет определитель матрицы рекурсивным методом разложения по строке.
 *
 * Математический принцип:
 * Определитель матрицы — это число, которое характеризует свойства квадратной матрицы.
 * Для матрицы размера n×n определитель рассчитывается через разложение по строке или столбцу:
 * - Выбираем строку (в данном случае первую).
 * - Формируем минор для каждого элемента строки. Минор — это подматрица, полученная удалением строки и столбца элемента.
 * - Рекурсивно вычисляем определитель минора.
 * Формула:
 * det(A) = Σ (-1)^(i+j) * A[0][j] * det(minor(A[0][j]))
 * где i=0 (номер строки), j - номер столбца, A[0][j] - элемент в первой строке и j-ом столбце.
 *
 * Алгоритм:
 * 1. Если матрица 1×1, возвращаем единственный элемент.
 * 2. Если 2×2, используем упрощённую формулу det(A) = ad - bc.
 * 3. Для матриц большего размера:
 *    a. Перебираем элементы первой строки.
 *    b. Формируем минор для каждого элемента.
 *    c. Рекурсивно вызываем функцию для минора.
 *    d. Суммируем результаты с учётом знака (-1)^(i+j).
 *
 * @param matrix Матрица, для которой нужно вычислить определитель.
 * @return Определитель матрицы.
 */
double Matrix::_determinant_recursive(const std::vector<std::vector<double>>& matrix) {
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
