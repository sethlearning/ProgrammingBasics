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
    char sourceFileName[512] = "", resultFileName[512] = "", key[100] = "", originalKey[100] = "";
    char c;

    FILE *source, *result;

    // Arguments
    if (argc > 2)
    {
        for (i = 1; i < argc; i++)
        {
            if (!strcmp(argv[i], "encrypt")) encrypt = 1;
            if (!strcmp(argv[i], "decrypt")) decrypt = 1;
            if (strstr(argv[i], "sourcefile=")) strcpy(sourceFileName, argv[i] + 11);
            if (strstr(argv[i], "resultfile=")) strcpy(resultFileName, argv[i] + 11);
            if (strstr(argv[i], "key=")) strcpy(key, argv[i] + 4);
        }
    }
    else help(argv[0], 0);


    // Check arguments
    keyLength = strlen(key);

    if ((encrypt && decrypt) || strlen(sourceFileName) == 0 || strlen(resultFileName) == 0 || keyLength == 0)
        help(argv[0], 0);

    // Prepare key
    strcpy(originalKey, key);
    if (prepareKey(key)) help(argv[0], 1);

    // Files
    if ((source = fopen(sourceFileName, "r")) == NULL)
    {
        printf("File open error: %s", sourceFileName);
        help(argv[0], 0);
    }

    if ((result = fopen(resultFileName, "w")) == NULL)
    {
        fclose(source);
        printf("File open error: %s", resultFileName);
        help(argv[0], 0);
    }

    // Encryption/Decryption

    while(1)
    {
        c = fgetc(source);
        if ( feof(source) ) break;

        if ( isAlpha(c) )
        {
            if (c == toupper(c)) offset = 65;
            else offset = 97;

            if (! decrypt)
                c = (c - offset + key[k]) % 26 + offset;        // encrypt (! decrypt - because encrypt is by default)
            else
                c = (c - offset - key[k] + 26) % 26 + offset;   // decrypt

            if (++k == keyLength) k = 0;
        }

        fputc(c, result);
    }

    // Close files
    fclose(source);
    fclose(result);

    // Output
    if (! decrypt)
        printf("\nШифрование методом Виженера\n\n");
    else
        printf("\nРасшифровка методом Виженера\n\n");

    printf("Исходный файл: %s\n", sourceFileName);
    printf("Результат: %s\n", resultFileName);
    printf("Ключ: %s\n\n", originalKey);
}

// Help and exit
void help(char commandName[], int keyError)
{
    printf("\nШифрование методом Виженера\n\n");
    if (keyError) printf("Ключ должен содержать только буквы.\n\n");
    printf("Примеры использования:\n    %s encrypt sourcefile=source.txt resultfile=encrypt.txt key=abc\n    %s decrypt sourcefile=encrypt.txt resultfile=decrypt.txt key=abc\n\n", commandName, commandName);
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
