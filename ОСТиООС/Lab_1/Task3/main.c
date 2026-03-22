#include <stdio.h>
#define BUFFER_SIZE (4096)

int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        printf("Error! Not enougth arguments!");
        return -1;
    }

    const char * src = argv[1];
    const char * dst = argv[2];

    FILE * in;
    FILE * out;

    if((in = fopen(src, "rb")) == 0)
    {
        printf("Error of opening source file!");
        return 1;
    }
    if((out = fopen(dst, "wb")) == 0)
    {
        printf("Error of opening destination file!");
        return 2;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, in)) > 0)
    {
        if(fwrite(buffer, 1, bytesRead, out) != bytesRead)
        {
            printf("Error in writing in destination file!");
            fclose(in);
            fclose(out);
            return 3;
        }
    }

    if(ferror(in))
    {
        printf("Error in writing in source file!");
        fclose(in);
        fclose(out);
        return 4;
    }

    fclose(in);
    fclose(out);

    printf("File copied successfuly: %s -> %s\n", src, dst);
    return 0;
}