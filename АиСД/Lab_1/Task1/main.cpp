#include "utils.h"

int main()
{
    // TEST ob;
    // std::cout << ob.get_i();

    const unsigned char key[] = "MyRC4SuperKey16";
    int keySize = 16;

    printf("RC4 Encoder Demo\n");
    printf("========================================\n");

    try 
    {
        encoder enc(key, keySize);

        // === Текстовый файл ===
        printf("Test 1: Text file\n");

        if (enc.encode("docs/text/test.txt", "docs/text/test_encrypted.bin", false)) 
        {
            printf(" ✅ encrypted -> test_encrypted.bin\n");

            if (enc.encode("docs/text/test_encrypted.bin", "docs/text/test_decrypted.txt", true)) 
            {
                printf(" ✅ decrypted -> test_decrypted.txt\n");
            } 
            else 
            {
                printf(" ❌ Decryption error!\n");
            }
        } 
        else 
        {
            printf(" ❌ Encryption error!\n");
        }
        printf("\n");



        // === Image ===
        printf("Test 2: Image\n");

        if (enc.encode("docs/image/image.png", "docs/image/image_encrypted.bin", false)) 
        {
            printf(" ✅ encrypted -> image_encrypted.bin\n");

            if (enc.encode("docs/image/image_encrypted.bin", "docs/image/image_decrypted.png", true)) 
            {
                printf(" ✅ decrypted -> image_decrypted.png\n");
            } 
            else 
            {
                printf(" ❌ Decryption error!\n");
            }
        } 
        else 
        {
            printf(" ❌ Encryption error!\n");
        }
        printf("\n");



        // === Audio  ===
        printf("Test 3:  Audio\n");

        if (enc.encode("docs/audio/audio.mp3", "docs/audio/audio_encrypted.bin", false)) 
        {
            printf(" ✅ encrypted -> audio_encrypted.bin\n");

            if (enc.encode("docs/audio/audio_encrypted.bin", "docs/audio/audio_decrypted.mp3", true)) 
            {
                printf(" ✅ decrypted -> audio_decrypted.mp3\n");
            } 
            else 
            {
                printf(" ❌ Decryption error!\n");
            }
        } 
        else 
        {
            printf(" ❌ Encryption error!\n");
        }
        printf("\n");



        // === Program ===
        printf("Test 4: Program\n");

        if (enc.encode("docs/program/program.exe", "docs/program/program_encrypted.bin", false)) 
        {
            printf(" ✅ encrypted -> program_encrypted.bin\n");

            if (enc.encode("docs/program/program_encrypted.bin", "docs/program/program_decrypted.exe", true)) 
            {
                printf(" ✅ decrypted -> program_decrypted.exe\n");
            } 
            else 
            {
                printf(" ❌ Decryption error!\n");
            }
        } 
        else 
        {
            printf(" ❌ Encryption error!\n");
        }
        
        printf("\n\n");

    }
    catch (EncoderError e) 
    {
        printf("❌ Critical error: %s\n", errorMessage(e));
        return -1;
    }
    catch (...) 
    {
        printf("❌ Undefined encoder error\n");
        return -2;
    }

    return 0;
}