#include "complex_number.h"

const double eps = 1e-9;

complex_number & complex_number::operator+=(
    complex_number const & summand) &
{
    real += summand.real;
    imag += summand.imag;
    return *this;
}

complex_number complex_number::operator+(
    complex_number const & summand) const
{
    complex_number result(*this);
    result += summand;
    return result;
}

complex_number & complex_number::operator-=(
    complex_number const & subtrahend) &
{
    real -= subtrahend.real;
    imag -= subtrahend.imag;
    return *this;
}

complex_number complex_number::operator-(
    complex_number const & subtrahend) const
{
    complex_number result(*this);
    result -= subtrahend;
    return result;   
}

complex_number & complex_number::operator*=(
    complex_number const & multiplier) &
{
    double new_real = real * multiplier.real - imag * multiplier.imag;
    double new_imag = real * multiplier.imag + imag * multiplier.real;
    real = new_real;
    imag = new_imag;
    return *this;   
}

complex_number complex_number::operator*(
    complex_number const & multiplier) const
{
    complex_number result(*this);
    result *= multiplier;
    return result;
}

complex_number & complex_number::operator/=(
    complex_number const & divider) &
{
    double denom = divider.real * divider.real + divider.imag * divider.imag;
    if (fabs(denom) < eps) 
    {
        throw std::domain_error("Dividing nuber on zero complex number!");
    }
    double new_real = (real * divider.real + imag * divider.imag) / denom;
    double new_imag = (imag * divider.real - real * divider.imag) / denom;
    real = new_real;
    imag = new_imag;
    return *this;
}

complex_number  complex_number::operator/(
    complex_number const & divider) const
{
    complex_number result(*this);
    result /= divider;
    return result;
}

double complex_number::complexModulus(
    complex_number const & number)
{
    return std::sqrt((number.real * number.real) + (number.imag * number.imag));
}

double complex_number::complexArgument(
    complex_number const & number) 
{
    if (fabs(number.real) < eps && fabs(number.imag) < eps) 
    {
        throw std::domain_error("Argument is not findable in (0 + 0i)");
    }
    return std::atan2(number.imag, number.real);
}

std::ostream & operator<<(
    std::ostream & os, 
    complex_number const & z)
{
    os << z.real;
    if (z.imag >= 0) 
    {
        os << " + " << z.imag << "i";
    } 
    else 
    {
        os << " - " << -z.imag << "i";
    }
    return os;
}

std::istream & operator>>(
    std::istream & is, 
    complex_number & z)
{
    double r, i = 0.0;
    char ch;

    is >> r;

    if (is.peek() == 'i') 
    {
        is >> ch;
        z.real = 0.0;
        z.imag = r;
        return is;
    }

    if (is >> ch && (ch == '+' || ch == '-')) 
    {
        is >> i;
        if (is.peek() == 'i') 
        {
            is >> ch;
        }
        z.real = r;
        z.imag = (ch == '-') ? -i : i;
    } 
    else 
    {
        z.real = r;
        z.imag = 0.0;
    }

    return is;
}
