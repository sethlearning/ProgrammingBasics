#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logo.c"

void exitprogram(char *);

int main(int argc, char* argv[])
{
    char inFileName[128], outFileName[128];
    char message[256];
    char c;
    FILE *in, *out;

    logo();
    printf("Транслит с русского языка в кодировке UTF-8.\n\n");

    if (argc < 3)
    {
        sprintf(message, "Недостаточно аргументов.\nПример запуска программы:\n: %s in.txt out.txt\n", argv[0]);
        exitprogram(message);
    }

    strcpy(inFileName, argv[1]);
    strcpy(outFileName, argv[2]);

    // printf("inFileName: %s\noutFileName: %s\n\n", inFileName, outFileName);

    // open files
    if ( (in = fopen(inFileName, "r")) == NULL )
    {
        sprintf(message, "Ошибка открытия исходного файла: %s.\n", inFileName);
        exitprogram(message);
    }

    if ( (out = fopen(outFileName, "w")) == NULL )
    {
        fclose(in);
        sprintf(message, "Ошибка открытия результирующего файла: %s.\n", outFileName);
        exitprogram(message);
    }

    // process
    while (1)
    {
        c = getc(in);
        if ( feof(in) ) break;

        printf("%hhu\n", c);
        // putchar(c);

        // fputc(c, result);

    }
    // close files
    fclose(in);
    fclose(out);

}

void processConfig(FILE *config, int *autof, int *size, int *additional)
{
    char buffer[128];
    char fillmethod[7], useAdditionalFunctions[4];

    memset(fillmethod, '\0', sizeof(fillmethod));
    memset(useAdditionalFunctions, '\0', sizeof(useAdditionalFunctions));

    fgets(buffer, 128, config);

    if ( strcmp(buffer, "#!Config file for lists\n") )
        exitprogram("Ошибка заголовка файла конфигурации.\nОжидаемое значение: #!Config file for lists\n");

    while(1)
    {
        if ( fgets(buffer, 128, config) == NULL ) break;

        if (buffer[0] == '#') continue;

        if (buffer[0] == '!')
        {
            puts(buffer + 1);
            continue;
        }

        if ( strstr(buffer, "listsize=") )
        {
            *size = atoi( buffer + strlen("listsize=") );
            continue;
        }

        if ( strstr(buffer, "fillmethod=") )
        {
            strncpy(fillmethod, buffer + strlen("fillmethod="), 6);
            continue;
        }

        if ( strstr(buffer, "useAdditionalFunctions=") )
        {
            strncpy(useAdditionalFunctions, buffer + strlen("useAdditionalFunctions="), 3);
            continue;
        }
    }

    if ( !strcmp(fillmethod, "auto") || !strcmp(fillmethod, "auto\n"))
        *autof = 1;
    else if ( !strcmp(fillmethod, "manual") )
        *autof = 0;

    if (*size <= 0 || *autof < 0)
        exitprogram("Ошибка файла конфигурации.\nФайл должен содержать правильные значения параметов listsize и fillmethod.\n");

    if ( !strcmp(useAdditionalFunctions, "yes") )
        *additional = 1;
}


void exitprogram(char *message)
{
    puts(message);
    exit(1);
}
