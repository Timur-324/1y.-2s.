#include "utils.h"

// int TEST::get_i()
// {
//     return this->i;
// }

// Функция для перевода ошибки в строку
const char * errorMessage(
    EncoderError e) 
{
    switch (e) 
    {
        case EncoderError::NullKey:
            return "Key cannot be null";
        case EncoderError::InvalidKeySize:
            return "Key size must be positive";
        case EncoderError::MemoryAllocationFailed:
            return "Memory allocation failed";
        case EncoderError::InputFileOpenError:
            return "Cannot open input file";
        case EncoderError::OutputFileOpenError:
            return "Cannot create or write to output file";
        case EncoderError::NULLptr:
            return "The pointer is NULL";
        default:
            return "Unknown error";
    }
}

// static const int BUFFER_SIZE = 4096;


void encoder::ValidateKey(
    const unsigned char* key, 
    int keySize) const
{
    if (!key) 
    {
        throw EncoderError::NullKey;
    }
    if (keySize <= 0)
    {
        throw EncoderError::InvalidKeySize;
    }
}

void encoder::allocateKey(
    int keySize)
{
    if (!(key = new (std::nothrow) unsigned char[keySize])) 
    {
        throw EncoderError::MemoryAllocationFailed;
    }
}

void encoder::CopyKeyBytes(
    const unsigned char * key, 
    int keySize)
{
    for (int i = 0; i < keySize; ++i) 
    {
        this->key[i] = key[i];
    }
}

void encoder::allocateBuffer(
    unsigned char * & buffer, 
    size_t size)
{
    if(size <= 0)
    {
        throw EncoderError::InvalidKeySize;
    }

    if(!(buffer = new (std::nothrow) unsigned char[size]))
    {
        throw EncoderError::MemoryAllocationFailed;
    }
}

void encoder::CopyKeyBytes2(
    unsigned char * buffer, 
    const unsigned char * key, 
    int size)
{
    if(!buffer || !key)
    {
        throw EncoderError::NULLptr;
    }

    if(size <= 0)
    {
        throw EncoderError::InvalidKeySize;
    }

    for (int i = 0; i < size; ++i) 
    {
        buffer[i] = key[i];
    }
}


    
//  bool encoder::validateIO(const char * inFile, const char * outFile) const
//  {

//  }

// Конструктор
encoder::encoder(
    const unsigned char * key, 
    int keySize,
    size_t bufsize) :
    key(nullptr), keySize(0), buffer_size(bufsize)
{
    ValidateKey(key, keySize);

    allocateKey(keySize);

    CopyKeyBytes(key, keySize);

    this->keySize = keySize;
}

// Деструктор
encoder::~encoder()
{
    delete[] key;
    key = nullptr;
    keySize = 0;
}

// Конструктор копирования
encoder::encoder(
    const encoder & other) : 
    key(nullptr), keySize(0), buffer_size(other.buffer_size)
{
    ValidateKey(other.key, other.keySize);

    allocateKey(other.keySize);
    
    CopyKeyBytes(other.key, other.keySize);

    // Устанавливаем размер
    this->keySize = other.keySize;
}

// Оператор присваивания
encoder & encoder::operator=(
    const encoder & other)
{
    // 1. Проверка на самоприсваивание
    if(this == &other)
    {
        return *this;
    }

    // 2. Сохраняем старые данные, чтобы не потерять при ошибке
    unsigned char * oldKey = key;

    // 3. Подготавливаем новые данные
    unsigned char* newKey = nullptr;
    int newSize = 0;

    // 4. Валидируем и копируем
    if (other.key && other.keySize > 0) 
    {
        newSize = other.keySize;
        allocateBuffer(newKey, newSize);
        CopyKeyBytes2(newKey, other.key, newSize);
        // for (int i = 0; i < newSize; ++i) 
        // {
        //     newKey[i] = other.key[i];
        // }
    }

    // 5. Обновляем состояние 
    key = newKey;
    keySize = newSize;
    buffer_size = other.buffer_size;

    // 6. Удаляем старое состояние
    delete[] oldKey;

    // 7. Fluent API
    return *this;
}

/* mutator(setter) -
- метод, используемый для изменения закрытого состояния (поля) объекта.
*/
bool encoder::setKey(
    const unsigned char * newKey, 
    int newSize)
{
    ValidateKey(newKey, newSize);

    unsigned char * temp = nullptr;
    allocateBuffer(temp, newSize);

    CopyKeyBytes2(temp, newKey, newSize);
    // for (int i = 0; i < newSize; ++i) 
    // {
    //     temp[i] = newKey[i];
    // }

    delete[] key;

    key = temp;
    keySize = newSize;

    return true;
}

// вспомогательные функции для encode
// использую static, т.к вспомогательные функции нужны только для encode
static void rc4_init(
    unsigned char S[256], 
    const unsigned char * key, 
    int keySize) 
{
    for (int i = 0; i < 256; ++i) 
    {
        S[i] = static_cast<unsigned char>(i);
    }

    int j = 0;
    for (int i = 0; i < 256; ++i) 
    {
        j = (j + S[i] + key[i % keySize]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}

static unsigned char rc4_byte(
    unsigned char S[256], 
    int& i, 
    int & j) 
{
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;

    unsigned char temp = S[i];
    S[i] = S[j];
    S[j] = temp;

    int t = (S[i] + S[j]) % 256;
    return S[t];
}


bool encoder::encode(
    const char * inputFile, 
    const char * outputFile, 
    bool decrypt)
{
    if (!inputFile || !outputFile || !key || keySize <= 0) 
    {
        return false;
    }

    FILE* in = fopen(inputFile, "rb");
    if (!in) 
    {
        return false;
    }

    FILE* out = fopen(outputFile, "wb");
    if (!out) 
    {
        fclose(in);
        return false;
    }

    // Инициализация RC4
    unsigned char S[256];
    rc4_init(S, key, keySize);
    int i = 0, j = 0;

    // Буфер для чтения/записи
    unsigned char buffer[buffer_size];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), in)) > 0) 
    {
        // Применяем RC4 к каждому байту
        for (size_t idx = 0; idx < bytesRead; ++idx) 
        {
            unsigned char keystream = rc4_byte(S, i, j);
            buffer[idx] ^= keystream; // XOR — шифрование и дешифрование
        }

        // Записываем в выходной файл
        size_t written = fwrite(buffer, 1, bytesRead, out);
        if (written != bytesRead) 
        {
            fclose(in);
            fclose(out);
            return false; // ошибка записи
        }
    }

    fclose(in);
    fclose(out);
    return true;
}