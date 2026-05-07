#include "matrix.h"

void matrix::destruct()
{
    if (data) 
    {
        for (size_t i = 0; i < rows; ++i) 
        {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

void matrix::copy(
    matrix const & other)
{
    rows = other.rows;
    cols = other.cols;

    data = new double*[rows];
    
    size_t constructed_rows = 0;

    try 
    {
        for (int i = 0; i < rows; ++i) 
        {
            data[i] = new double[cols];
            ++constructed_rows;
        }

        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < cols; ++j) 
            {
                data[i][j] = other.data[i][j];
            }
        }
    }
    catch (...) 
    {
        for (int i = 0; i < constructed_rows; ++i) 
        {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
        throw;
    }
}

// конструктор
matrix::matrix(size_t r, size_t c) : 
    rows(r), cols(c)
{
    if(r == 0 || c == 0) //запрет на только строку или только столбец
    {
        throw std::invalid_argument("Size of matrix should be more then 0!");
    }
    data = new double*[rows];
    for (size_t i = 0; i < rows; ++i) 
    {
        data[i] = new double[cols](); // автоматическое обнуление
    }
}

matrix::~matrix() noexcept
{
    destruct();
}

matrix::matrix(
    matrix const & other) :
    rows(other.rows), cols(other.cols)
{
    copy(other);
}

matrix & matrix::operator=(
    matrix const & other)
{
    if (this == &other) {return *this;}

    destruct();

    copy(other);
    return *this;
}

matrix & matrix::operator+=(
    matrix const & summand) &
{
    if(rows != summand.rows && cols != summand.cols)
    {
        throw std::invalid_argument("Rows and cols of matrices must be the same!");
    }

    for(int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            data[i][j] += summand.data[i][j];
        }
        
    }

    return *this;
}
    
matrix matrix::operator+(
    matrix const & summand) const
{
    matrix result(*this);
    result += summand;
    return result;
}

matrix & matrix::operator-=(
    matrix const & subtrahend) &
{
    if(rows != subtrahend.rows && cols != subtrahend.cols)
    {
        throw std::invalid_argument("Rows and cols of matrices must be the same!");
    }

    for(int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            data[i][j] -= subtrahend.data[i][j];
        }
        
    }

    return *this;   
}
    
matrix matrix::operator-(
    matrix const & subtrahend) const
{
    matrix result(*this);
    result -= subtrahend;
    return result;
}

matrix & matrix::operator*=(
    matrix const & multiplier) &
{
    if (cols != multiplier.rows) 
    {
        throw std::invalid_argument("Matrix multiplication not possible!");
    }

    matrix result(rows, multiplier.cols);

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < multiplier.cols; ++j) 
        {
            double sum = 0.0;
            for (int k = 0; k < cols; ++k) 
            {
                sum += data[i][k] * multiplier.data[k][j];
            }
            result.data[i][j] = sum;
        }
    }

    std::swap(data, result.data);
    std::swap(rows, result.rows);
    std::swap(cols, result.cols);

    return *this;
}

matrix matrix::operator*(
    matrix const & multiplier) const
{
    matrix result(*this);
    result *= multiplier;
    return result;
}

matrix matrix::operator*(
    double scalar) const
{
    if (std::isnan(scalar)) 
    {
        throw std::invalid_argument("Scalar cannot be NaN");
    }
    if (std::isinf(scalar)) 
    {
        throw std::invalid_argument("Scalar cannot be infinite");
    }
    matrix result(*this);
    for(int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            result.data[i][j] *= scalar;
        }
        
    }
    return result;
}

matrix operator*(
    double scalar, 
    matrix const & m)
{
    return m * scalar;
}


matrix matrix::transposed() const
{
    matrix result(cols, rows); 

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            result.data[j][i] = data[i][j];
        }
    }

    return result;
}

double matrix::determinant() const
{
    if (rows != cols) 
    {
        throw std::invalid_argument("Determinant is only defined for square matrices");
    }

    if (rows == 0) 
    {
        return 1.0;
    }

    if (rows == 1) 
    {
        return data[0][0];
    }

    matrix temp(*this);
    double det = 1.0;
    int sign = 1;

    for (int col = 0; col < cols; ++col) 
    {
        size_t pivot_row = col;
        for (int i = col + 1; i < rows; ++i) 
        {
            if (std::abs(temp.data[i][col]) > std::abs(temp.data[pivot_row][col])) 
            {
                pivot_row = i;
            }
        }

        if (std::abs(temp.data[pivot_row][col]) < 1e-12) 
        {
            return 0.0;
        }

        if (pivot_row != col) 
        {
            std::swap(temp.data[col], temp.data[pivot_row]);
            sign = -sign;
        }

        for (int i = col + 1; i < rows; ++i) 
        {
            double factor = temp.data[i][col] / temp.data[col][col];

            for (int j = col; j < cols; ++j) 
            {
                temp.data[i][j] -= factor * temp.data[col][j];
            }
        }
    }

    for (int i = 0; i < rows; ++i) 
    {
        det *= temp.data[i][i];
    }

    return det * sign;
}

matrix matrix::inverse_matrix() const
{
    if (rows != cols)
    {
        throw std::invalid_argument("Inverse is only defined for the square matrices!");
    }

    size_t n = rows;

    if (n == 0) 
    {
        return matrix(0, 0);
    }

    double det = determinant();
    if(std::abs(det) < 1e-12)
    {
        throw std::invalid_argument("Determinant is zero");
    }

    matrix augmented(n, 2 * n);

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            augmented.data[i][j] = data[i][j];
            augmented.data[i][j + n] = (i == j) ? 1.0 : 0.0;
        }
    }

    for (size_t col = 0; col < n; ++col) 
    {
        size_t pivot_row = col;
        for (int i = col + 1; i < n; ++i) 
        {
            if (std::abs(augmented.data[i][col]) > std::abs(augmented.data[pivot_row][col])) 
            {
                pivot_row = i;
            }
        }

        if (std::abs(augmented.data[pivot_row][col]) < 1e-12) 
        {
            throw std::invalid_argument("Matrix is singular during inversion");
        }

        if (pivot_row != col) 
        {
            std::swap(augmented.data[col], augmented.data[pivot_row]);
        }

        double pivot = augmented.data[col][col];
        for (int j = 0; j < 2 * n; ++j) 
        {
            augmented.data[col][j] /= pivot;
        }

        for (int i = 0; i < n; ++i) 
        {
            if (i == col){continue;}
            double factor = augmented.data[i][col];
            for (int j = 0; j < 2 * n; ++j) 
            {
                augmented.data[i][j] -= factor * augmented.data[col][j];
            }
        }
    }

    matrix inverse(n, n);
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            inverse.data[i][j] = augmented.data[i][j + n];
        }
    }
    return inverse;
}

double & matrix::operator[](
    matrix_index const & i) const
{
    if (i.row >= rows || i.col >= cols) 
    {
        throw IndexOutOfBoundsException(i.row, i.col, rows, cols);
    }

    return data[i.row][i.col]; 
}

std::ostream & operator<<(std::ostream& os, const matrix& m) 
{
    for (size_t i = 0; i < m.getRows(); ++i) 
    {
        for (size_t j = 0; j < m.getCols(); ++j) 
        {
            os << std::setw(10) << std::setprecision(3) << m[matrix::matrix_index{i, j}];
        }
        os << '\n';
    }
    return os;
}


//Может ли сложение двух матриц у которых определитель отличен от нуля в ответе 100% дать матрицу у которой определитель также не 0. 
// Ответ нет. Т.к может в ответе быть матрица у которой определитель 0 - значит нет замкнутости - а отсюда следует что это не ялвяться никакой алгербаической структурой