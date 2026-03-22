#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstdlib>
#include <new> // нужно для того, чтобы new не выкидывал ошибку, если памяти нет

// class TEST
// {
//     int i = 100;

// public: 
//     int get_i();
// };

// Перечисление ошибок (без использования STL)
enum class EncoderError 
{
    NullKey,
    InvalidKeySize,
    MemoryAllocationFailed,
    InputFileOpenError,
    OutputFileOpenError
};

const char * errorMessage(EncoderError e);

class encoder
{
private: 
    unsigned char * key;
    int keySize;
public:
    // Конструктор
    encoder(const unsigned char * key, int keySize);

    // Деструктор
    ~encoder();

    // Конструктор копирования
    encoder(const encoder & other);

    // Оператор присваивания
    encoder & operator=(const encoder & other);

    // mutator(setter) - метод, используемый для изменения закрытого состояния (поля) объекта.
    bool setKey(const unsigned char * newKey, int newSize);

    bool encode(const char * inputFile, const char * outputFile, bool decrypt);
};

#endif