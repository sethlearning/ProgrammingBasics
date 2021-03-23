#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

// 65-90 AZ
// 97-122 az

void help(char[], int);
int prepareKey(char[]);
int isAlpha(char);

int main(int argc, char* argv[])
{
    int i = 0, k = 0;
    int encrypt = 0, decrypt = 0, offset = 65;
    int sourceLength = 0, keyLength = 0;
    char source[1000] = "", result[1000] = "", key[100] = "", originalKey[100] = "";

    // Arguments
    if (argc > 2)
    {
        for (i = 1; i < argc; i++)
        {
            if (strstr(argv[i], "encrypt")) encrypt = 1;
            if (strstr(argv[i], "decrypt")) decrypt = 1;
            if (strstr(argv[i], "source=")) strcpy(source, argv[i] + 7);
            if (strstr(argv[i], "key=")) strcpy(key, argv[i] + 4);
        }
    }
    else help(argv[0], 0);

    // Lengths
    sourceLength = strlen(source);
    keyLength = strlen(key);

    // Check arguments
    if ((encrypt && decrypt) || sourceLength == 0 || keyLength == 0) help(argv[0], 0);

    // Prepare key
    strcpy(originalKey, key);
    if (prepareKey(key)) help(argv[0], 1);

    // Encryption/Decryption
    for (i = 0; i < sourceLength; i++)
    {
        if (isAlpha(source[i]))
        {
            if (source[i] == toupper(source[i])) offset = 65;
            else offset = 97;

            if (! decrypt) result[i] = (source[i] - offset + key[k]) % 26 + offset; // encrypt (! decrypt - because encrypt is by default)
            else result[i] = (source[i] - offset - key[k] + 26) % 26 + offset;      // decrypt

            if (++k == keyLength) k = 0;
        }

        else result[i] = source[i]; // not letters, copy as it is
    }
    result[i] = 0x0;

    // Output
    if (! decrypt)
    {
        printf("\nШифрование методом Виженера\n\n");
        printf("Исходный текст: %s\n", source);
    }
    else
    {
        printf("\nРасшифровка методом Виженера\n\n");
        printf("Зашифрованный текст: %s\n", source);
    }
    printf("Ключ: %s\n", originalKey);
    printf("Результат: %s\n\n", result);
}

// Help and exit
void help(char commandName[], int keyError)
{
    printf("\nШифрование методом Виженера\n\n");
    if (keyError) printf("Ключ должен содержать только буквы.\n\n");
    printf("Примеры использования:\n    %s encrypt source=AaAaZzZz key=abc\n    %s decrypt source=AbCaAbZa key=abc\n\n", commandName, commandName);
    printf("    %s encrypt \"source=Aa Aa Zz Zz\" key=abc\n    %s decrypt \"source=Ab Ca Ab Za\" key=abc\n\n", commandName, commandName);
    exit(0);
}

// Prepare key for usage
int prepareKey(char key[])
{
    int i = 0;
    while (key[i])
    {
        if (isAlpha(key[i]))
        {
            key[i] = toupper(key[i]);   // Bring key to uppercase
            key[i] -= 65;               // Bring key to numbers A-0, B-1, ..., Z-25
            i++;
        }
        else return 1;
    }
    return 0;
}

// Is it a letter
int isAlpha(char c)
{
    if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return 1;
    else return 0;
}
