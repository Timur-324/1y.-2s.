#include <stdio.h>

int main(int argc, char * argv[]) 
{
    if(argc != 2)
    {
        printf("Error! There is no path to file :(\n");
        return -1;
    }

    // Step_1: Creating file and putting data inside
    const char *filename = argv[1];
    unsigned char data[11] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int data_size = sizeof(data) / sizeof(data[0]);

    FILE *file = fopen(filename, "wb");  // wb = write binary
    if(!file)
    {
        return 1;
    }

    fwrite(data, sizeof(unsigned char), data_size, file);
    fclose(file);
    printf("File has been successfully created and filled in with data!\n");


    /* Step_2: Opening and reading this file
    with byte-by-byte output of the contents of this file to the console */
    file = fopen(filename, "rb");
    if (!file)
    {
        return 2;
    }
    printf("---Byte-by-byte reading---\n");
    unsigned char byte;
    while(fread(&byte, sizeof(unsigned char), 1, file) == 1)
    {
        printf("Read byte: %d\n", byte);
        printf("Position: %ld\n", ftell(file));
        printf("feof: %s\n", feof(file) ? "Yes" : "No");
        printf("ferror: %s\n", ferror(file) ? "Yes" : "No");
        printf("\n");
    }
    fclose(file);


    // Step_3: Moving pointers using fseek
    file = fopen(filename, "rb");
    if (!file)
    {
        return 3;
    }
    if(fseek(file, 3, SEEK_SET) != 0)
    {
        fclose(file);
        return 4;
    }
    printf("---Reading four bytes from third position---\n");
    unsigned char buffer[4];
    int i;
    size_t read_cnt = fread(buffer, sizeof(unsigned char), 4, file);

    printf("Read %zu bytes.\n", read_cnt);
    printf("Buffer сontents: ");
    for(i = 0; i < read_cnt; ++i)
    {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    fclose(file);
    return 0;
}