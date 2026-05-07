#include "logical_values_array.h"

unsigned int logical_values_array::get_value () const
{
    return _value;
}

//Инверсия
logical_values_array logical_values_array::operator~() const 
{
    return logical_values_array(~_value);
}

//Конъюнкция
logical_values_array logical_values_array::operator&(
    const logical_values_array & other) const 
{
    return logical_values_array(_value & other._value);
}

//Дизъюнкция
logical_values_array logical_values_array::operator|(
    const logical_values_array & other) const 
{
    return logical_values_array(_value | other._value);
}

//XOR
logical_values_array logical_values_array::operator^(
    const logical_values_array & other) const 
{
    return logical_values_array(_value ^ other._value);
}

//Импликация: a → b = ¬a ∨ b
logical_values_array logical_values_array::implies(
    const logical_values_array & other) const 
{
    return (~(*this)) | other;
}

//Коимпликация: b → a = ¬b ∨ a
logical_values_array logical_values_array::co_implies(
    const logical_values_array & other) const 
{
    return (~other) | (*this);
}

//Эквивалентность: a ≡ b = ¬(a ⊕ b)
logical_values_array logical_values_array::equivalence(
    const logical_values_array & other) const 
{
    return ~(*this ^ other);
}

//Штрих Шеффера: a ↑ b = ¬(a ∧ b)
logical_values_array logical_values_array::nand(
    const logical_values_array & other) const 
{
    return ~(*this & other);
}

//Стрелка Пирса: a ↓ b = ¬(a ∨ b)
logical_values_array logical_values_array::nor(
    const logical_values_array & other) const 
{
    return ~(*this | other);
}

bool logical_values_array::equals(
        const logical_values_array & first, 
        const logical_values_array & second)
{
    return first._value == second._value;
}

unsigned int logical_values_array::get_bit(
    size_t position) const 
{
    if (position >= sizeof(unsigned int) * 8)
    {
        throw std::out_of_range("Bit position must be less than: " + std::to_string(sizeof(unsigned int) * 8) );
    }
    return (_value >> position) & 1;
}

unsigned int logical_values_array::operator[](
    size_t position) const 
{
    return get_bit(position);
}

void logical_values_array::to_binary_string(
    char * buffer) const 
{
    if (buffer == nullptr) 
    {
        throw std::invalid_argument("Buffer pointer cannot be null in to_binary_string.");
    }

    int BITS = (sizeof(unsigned int) * 8);
    for (int i = 0; i < BITS; ++i) 
    {
        buffer[i] = ((_value >> (BITS - 1 - i)) & 1) ? '1' : '0';
    }
    buffer[BITS] = '\0';
}