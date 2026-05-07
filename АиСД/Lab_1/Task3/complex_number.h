#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H
#include <iostream>
#include <stdexcept>
#include <cmath>

class complex_number
{
private:
    double real; //действительная часть
    double imag; //мнимая часть

public:
    explicit complex_number(double r = 0.0, double i = 0.0):
        real(r), imag(i){}

    //Операторные методы
    complex_number & operator+=(
        complex_number const & summand) &;

    complex_number operator+(
        complex_number const & summand) const;
    
    complex_number & operator-=(
        complex_number const & subtrahend) &;

    complex_number operator-(
        complex_number const & subtrahend) const;
    
    complex_number & operator*=(
        complex_number const & multiplier) &;

    complex_number  operator*(
        complex_number const & multiplier) const;

    complex_number & operator/=(
        complex_number const & divider) &;

    complex_number operator/(
        complex_number const & divider) const;

    //иодуль числа
    double complexModulus(
        complex_number const & number);

    //аргумент числа
    double complexArgument(
        complex_number const & number);

    //оператор вставкив поток
    friend std::ostream & operator<<(
        std::ostream & os, 
        complex_number const & z);

    //оператор вывода из потока
    friend std::istream & operator>>(
        std::istream & is, 
        complex_number & z);
};

#endif 