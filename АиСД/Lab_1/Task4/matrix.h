#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <iomanip>

class matrix final
{
private: 
    double ** data;
    size_t rows;
    size_t cols;

    // вспомогательные функции 
    void destruct();
    void copy(
        matrix const & from);

public:

    class IndexOutOfBoundsException final: public std::runtime_error 
    {
    public:
        explicit IndexOutOfBoundsException(size_t r, size_t c, size_t rows, size_t cols)
            : std::runtime_error("Matrix index out of range!"){}
    };

    class matrix_index final
    {
    public:
        size_t row;
        size_t col;
    };

    // конструктор
    matrix(
        size_t r, 
        size_t c);

    //правило трёх
    ~matrix() noexcept;

    matrix & operator=(
        matrix const & other);

    //конструктор копирования
    matrix(
        matrix const & other);

    
    //Операторные методы
    matrix & operator+=(
        matrix const & summand) &;
    
    matrix operator+(
        matrix const & summand) const;

    matrix & operator-=(
        matrix const & subtrahend) &;
    
    matrix operator-(
        matrix const & subtrahend) const;

    matrix & operator*=(
        matrix const & multiplier) &;

    matrix operator*(
        matrix const & multiplier) const;

    matrix operator*(
        double scalar) const;

    friend matrix operator*(
        double scalar, 
        matrix const & m);

    //транспонированная матрица
    matrix transposed() const;

    //определитель методом Гаусса
    double determinant() const;

    //Обратная матрица
    matrix inverse_matrix() const;

    //Оператор []
    double & operator[](
        matrix_index const & i) const;

    // Геттеры
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }

    // Дружественный оператор вывода
    friend std::ostream & operator<<(
        std::ostream & os, 
        matrix const & m);
};


#endif