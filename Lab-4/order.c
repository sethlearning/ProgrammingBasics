#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logo.c"

void ExitProgram(char*);

void DefineArrayManual(int*, int);
void DefineArrayAuto(int*, int);
void PrintArray(int*, int);
void OrderArray(int*, int);

int main(int argc, char* argv[])
{
    int count, i;
    char mode[7], example[150];

    logo();
    printf("Лабораторная работа №4.\nУпорядочивание элементов массива по признаку четности.\n\n");
    snprintf(example, 200, "Пример использования:\n%s NumberOfElements=number ArrayEnteringMode=auto/manual", argv[0]);

    if (argc < 3)
    {
        printf("Недостаточно параметров.\n");
        ExitProgram(example);
    }

    for (i = 1; i < argc; i++)
    {
        if (strstr(argv[i], "ArrayEnteringMode="))
            strcpy(mode, argv[i] + 18);

        if (strstr(argv[i], "NumberOfElements="))
            count = atoi(argv[i] + 17);
    }

    if (count < 2)
    {
        printf("Неверные параметры.\n");
        ExitProgram(example);
    }

    int array[count];
    if(!strcmp(mode, "manual"))
        DefineArrayManual(array, count);
    else if (!strcmp(mode, "auto"))
        DefineArrayAuto(array, count);
    else
    {
        printf("Неверные параметры.\n");
        ExitProgram(example);
    }

    printf("Исходный массив:\n");
    PrintArray(array, count);
    OrderArray(array, count);
    printf("Упорядоченный массив:\n");
    PrintArray(array, count);
}

void DefineArrayManual(int* array, int count)
{
    int i;
    char input[10];
    printf("Количество элементов: %d\n", count);
    printf("Метод ввода массива: manual\n\n");
    for (i=0; i < count; i++)
    {
        printf("Введите элемент %d: ", i);
        gets(input);
        array[i] = atoi(input);
    }
    printf("\n");
}

void DefineArrayAuto(int* array, int count)
{
    int i;
    printf("Количество элементов: %d\n", count);
    printf("Метод ввода массива: auto\n\n");
    srand(time(NULL));

    for (i=0; i < count; i++)
    {
        array[i] = rand() % 100;
    }
}

void PrintArray(int* array, int count)
{
    int i;
    for (i=0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

void OrderArray(int* array, int count)
{
    int changed, i, temp;

    do
    {
        changed = 0;
        for (i = 0; i < count-1; i++)
        {
            if (!(array[i] % 2) && (array[i+1] % 2))
            {
                changed = 1;
                temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
            }
        }
    }
    while (changed);
}

void ExitProgram(char* message)
{
    printf("%s\n", message);
    printf("Нажмите Enter!");
    getchar();
    exit(0);
}
