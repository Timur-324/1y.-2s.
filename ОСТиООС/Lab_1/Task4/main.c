#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_prime(unsigned char n) 
{
    if (n < 2) {return 0;}
    if (n == 2) {return 1;}
    if (n % 2 == 0) {return 0;}
    for (int i = 3; i * i <= n; i += 2) 
    {
        if (n % i == 0) {return 0;}
    }
    return 1;
}

int main(int argc, char * argv[])
{
    if(argc < 3)
    {
        printf("Error! Not enougth arguments!\n");
        printf("Usage: %s <file_path> <flag> [mask_value]\n", argv[0]);
        return -1;
    }

    char * PathToFile = argv[1];
    char * flag = argv[2];
    FILE * file;

    if((file = fopen(PathToFile, "rb")) == NULL)
    {
        printf("Error of opening file!");
        return 1;
    }

    // обработка флага xor8(or)
    if(strcmp(flag, "xor8") == 0)
    {
        unsigned char byte;
        unsigned char result = 0;
        size_t bytesRead;

        while((bytesRead = fread(&byte, 1, 1, file)) == 1)
        {
            result ^= byte;
        }

        printf("xor8 result: 0x%02X\n", result);
    }

    else if (strcmp(flag, "xorodd") == 0)
    {
        unsigned char buffer[4];
        unsigned int value;
        unsigned int xor_result = 0;
        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, 4, file)) == 4)
        {
            if(is_prime(buffer[0]) || is_prime(buffer[1]) ||
                is_prime(buffer[2]) || is_prime(buffer[3]))
            {
                value = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
                xor_result ^= value;

            }
        }

        printf("xorodd result: 0x%08X\n", xor_result);
        
    }

    // Всю эту ересь мне ещё предстоит понять и в слуяае чего переписать
    else if (strcmp(flag, "mask") == 0)
    {
        if (argc != 4)
        {
            printf("Usage: %s <file> mask <hex_value>\n", argv[0]);
            fclose(file);
            return -2;
        }

        // Парсим hex-маску
        char *endptr;
        unsigned int mask = (unsigned int)strtol(argv[3], &endptr, 16);
        if (*endptr != '\0')
        {
            printf("Invalid hex mask: %s\n", argv[3]);
            fclose(file);
            return -1;
        }

        unsigned char buffer[4];
        unsigned int value;
        unsigned int count = 0;
        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, 4, file)) == 4)
        {
            // Преобразуем 4 байта в little-endian uint32_t
            value = ((unsigned int)buffer[0]) |
                    (((unsigned int)buffer[1]) << 8) |
                    (((unsigned int)buffer[2]) << 16) |
                    (((unsigned int)buffer[3]) << 24);

            // Проверяем соответствие маске: (value & mask) == mask
            if ((value & mask) == mask)
            {
                count++;
            }
        }

        printf("mask count: %u\n", count);
    }

    else
    {
        printf("Unknown flag: %s\n", flag);
        printf("Supported flags: xor8, xorodd, mask <hex>\n");
    }
    
    fclose(file);
    return 0;
}