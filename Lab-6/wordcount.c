#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// #include <time.h>
#include "logo.c"

void ExitProgram(char*);

int main(int argc, char* argv[])
{
    char example[150], filename[256], c;
    FILE* file;
    int wordcount = 0, sameword = 0;

    logo();
    printf("Лабораторная работа №6.\nПодсчет количества слов в текстовом файле.\n\n");
    snprintf(example, 200, "Пример использования:\n%s file.txt", argv[0]);

    if (argc < 2)
    {
        printf("Недостаточно параметров.\n");
        ExitProgram(example);
    }

    if((file = fopen(argv[1], "r")) == NULL)
    {
        printf("Файла не существует.\n");
        ExitProgram(example);
    }
    
    puts("Содержимое файла:");
    while(1)
    {
        c = getc(file);
        if(feof(file)) break;
        putchar(c);

        if ((c >= 65 && c <=90) || (c >= 97 && c <= 122))
        {
            if (!sameword)
            {
                wordcount++;
                sameword = 1;
            }
        }
        else sameword = 0;
    }

    fclose(file);
    printf("\nКоличество слов: %d\n\n", wordcount);
}

void ExitProgram(char* message)
{
    printf("%s\n", message);
    printf("Нажмите Enter!");
    getchar();
    exit(0);
}
