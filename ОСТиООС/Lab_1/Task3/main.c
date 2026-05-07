#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define BUFFER_SIZE (4096)

int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        printf("Error! Not enough arguments!");
        return -1;
    }

    const char * src = argv[1];
    const char * dst = argv[2];


    /*
    TODO !!!
    Нужно сюда впихнуть новый алгоритм проверки!!!

    Сперва получить пути к файлам. 
    После приводить их к абсолютным и уже только тогда проверять на самоприсваивание
    */


    // // проверка на инноды 
    // struct stat st_src, st_dst;

    // // Получаем информацию об исходном файле
    // if (stat(src, &st_src) != 0)
    // {
    //     printf("Error: cannot access source file '%s'\n", src);
    //     return -2;
    // }

    // // Проверяем, существует ли destination
    // if (stat(dst, &st_dst) == 0)
    // {
    //     // Если destination существует — проверяем, не тот ли это же файл
    //     if (st_src.st_dev == st_dst.st_dev && st_src.st_ino == st_dst.st_ino)
    //     {
    //         printf("Error: source and destination are the same file (including hard links)!\n");
    //         return -3;
    //     }
    // }

    FILE * in;
    FILE * out;

    if((in = fopen(src, "rb")) == 0)
    {
        printf("Error of opening source file!");
        return -4;
    }
    if((out = fopen(dst, "wb")) == 0)
    {
        printf("Error of opening destination file!");
        return -4;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, in)) != 0)
    {
        if(fwrite(buffer, 1, bytesRead, out) != bytesRead)
        {
            printf("Error in writing in destination file!");
            fclose(in);
            fclose(out);
            return 1;
        }
    }

    if(ferror(in))
    {
        printf("Error in writing in source file!");
        fclose(in);
        fclose(out);
        return 2;
    }

    fclose(in);
    fclose(out);

    printf("File copied successfuly: %s -> %s\n", src, dst);
    return 0;
}