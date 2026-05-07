#ifndef LOGICAL_VALUES_ARRAY_H
#define LOGICAL_VALUES_ARRAY_H
#include <iostream>
#include <stdexcept>

class logical_values_array
{
private:
    //значение массива логических величин
    unsigned int  _value;

public:
    //аксесор для поля _value
    unsigned int get_value() const;
    
    //конструктор
    explicit logical_values_array(unsigned int param = 0):
        _value(param){}

    //Логические операции базовые:
    //инверсия
    logical_values_array operator~() const;
    
    //конъюнкция
    logical_values_array operator&(
        const logical_values_array & other) const;

    //дизъюнкция
    logical_values_array operator|(
        const logical_values_array & other) const;

    //XOR
    logical_values_array operator^(
        const logical_values_array & other) const;

    //Остальные операции будут реализованы через базовые:
    //Импликация
    logical_values_array implies(
        const logical_values_array & other) const;

    //Коимплиция
    logical_values_array co_implies(
        const logical_values_array & other) const;

    //Эквивалентность
    logical_values_array equivalence(
        const logical_values_array & other) const;
    
    //Штрих Шеффера(NAND)
    logical_values_array nand(
        const logical_values_array & other) const;
    
    //Стрелка Пирса(NOR)
    logical_values_array nor(
        const logical_values_array & other) const;


    //метод equals, сравнивающий два объекта по отношению эквивалентности
    static bool equals(
        const logical_values_array & first, 
        const logical_values_array & second);

    //Метод, который возращает значение  бита по его позиции
    unsigned int get_bit(
        size_t position) const;

    //Перегруженный оператор []
    unsigned int operator[](
        size_t position) const;

    //Метод записывает бинарное представление поле _value в виде строки в С
    void to_binary_string(
        char * buffer) const;
};

#endif