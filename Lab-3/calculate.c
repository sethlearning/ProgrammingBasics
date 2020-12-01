#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logo.c"

void ExitProgram(char*);

void DefineArrayManual(int*, int);
void DefineArrayAuto(int*, int);
void PrintArray(int*, int);
void CountNegatives(int*, int, int*, int*);

int main(int argc, char* argv[])
{
    int count, negativesCount=0, negativesSumma=0, i;
    char mode[7], example[150];

    logo();
    printf("Лабораторная работа №3.\nПодсчет количества отрицательных чисел и их суммы.\n\n");
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
    printf("Количество элементов: %d\n", count);

    int array[count];
    if(!strcmp(mode, "manual"))
    {
        printf("Метод ввода массива: %s\n\n", mode);
        DefineArrayManual(array, count);
    }
    else if (!strcmp(mode, "auto"))
    {
        printf("Метод ввода массива: %s\n\n", mode);
        DefineArrayAuto(array, count);
    }
    else
    {
        printf("Неверные параметры.\n");
        ExitProgram(example);
    }

    PrintArray(array, count);
    CountNegatives(array, count, &negativesCount, &negativesSumma);

    printf("Количество отрицательных элементов: %d\nСумма отрицательных элементов: %d\n\n", negativesCount, negativesSumma);
}

void DefineArrayManual(int* array, int count)
{
    int i;
    char input[10];
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
    srand(time(NULL));
    for (i=0; i < count; i++)
    {
        array[i] = rand() % 100 - 50;
    }
}

void PrintArray(int* array, int count)
{
    int i;
    printf("Содержимое массива:\n");
    for (i=0; i < count; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

void CountNegatives(int* array, int count, int* negativesCount, int* negativesSumma)
{
    int i;
    for (i=0; i < count; i++)
    {
        if (array[i] < 0)
        {
            *negativesCount += 1;
            *negativesSumma += array[i];
        }
    }
}

void ExitProgram(char* message)
{
    printf("%s\n", message);
    printf("Нажмите Enter!");
    getchar();
    exit(0);
}
