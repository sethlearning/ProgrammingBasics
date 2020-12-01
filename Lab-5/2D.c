#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logo.c"

void ExitProgram(char*);

int main(int argc, char* argv[])
{
    int rows, columns, i, row1, row2, minimalSum;
    char mode[7], example[150];

    logo();
    printf("Лабораторная работа №5.\nНахождение строк с минимальной суммой модулей поэлементной разности.\n\n");
    snprintf(example, 200, "Пример использования:\n%s Rows=number Columns=number ArrayEnteringMode=auto/manual", argv[0]);

    if (argc < 4)
    {
        printf("Недостаточно параметров.\n");
        ExitProgram(example);
    }

    for (i = 1; i < argc; i++)
    {
        if (strstr(argv[i], "ArrayEnteringMode="))
            strcpy(mode, argv[i] + 18);

        if (strstr(argv[i], "Rows="))
            rows = atoi(argv[i] + 5);

        if (strstr(argv[i], "Columns="))
            columns = atoi(argv[i] + 8);
    }

    if (rows < 2 || columns < 2)
    {
        printf("Неверные параметры.\n");
        ExitProgram(example);
    }

    int array[rows][columns];
    
    // Functions declaration
    void DefineArrayManual(int, int, int[rows][columns]);
    void DefineArrayAuto(int, int, int[rows][columns]);
    void PrintArray(int, int, int[rows][columns]);
    void Calculate(int, int, int[rows][columns], int*, int*, int*);

    if(!strcmp(mode, "manual"))
        DefineArrayManual(rows, columns, array);
    else if (!strcmp(mode, "auto"))
        DefineArrayAuto(rows, columns, array);
    else
    {
        printf("Неверные параметры.\n");
        ExitProgram(example);
    }

    printf("Содержимое массива:\n");
    PrintArray(rows, columns, array);
    Calculate(rows, columns, array, &row1, &row2, &minimalSum);
    printf("Строки с минимальной суммой модулей поэлементной разности: %d и %d\nМинимальная сумма: %d\n\n", row1, row2, minimalSum);
    printf("Адреса функций:\nmain: %p\nDefineArrayManual: %p\nDefineArrayAuto: %p\nPrintArray: %p\nCalculate: %p\nExitProgram: %p\n\n", main, DefineArrayManual, DefineArrayAuto, PrintArray, Calculate, ExitProgram);
}

void DefineArrayManual(int rows, int columns, int array[rows][columns])
{
    int i, j;
    char input[10];
    printf("Количество строк: %d\nКоличество столбцов:%d\n", rows, columns);
    printf("Метод ввода массива: manual\n\n");
    for (i=0; i < rows; i++)
    {
        for (j=0; j < columns; j++)
        {
            printf("Введите элемент [%d][%d]: ", i, j);
            gets(input);
            array[i][j] = atoi(input);
        }
    }
    printf("\n");
}

void DefineArrayAuto(int rows, int columns, int array[rows][columns])
{
    int i, j;
    printf("Количество строк: %d\nКоличество столбцов:%d\n", rows, columns);
    printf("Метод ввода массива: auto\n\n");
    srand(time(NULL));

    for (i=0; i < rows; i++)
    {
        for (j=0; j < columns; j++)
        {
            array[i][j] = rand() % 100;
        }
    }
}

void PrintArray(int rows, int columns, int array[rows][columns])
{
    int i, j;
    for (i=0; i < rows; i++)
    {
        for (j=0; j < columns; j++)
        {
            printf("%d \t", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Calculate(int rows, int columns, int array[rows][columns], int* row1, int* row2, int* minimalSum)
{
    int i, k, j, sum;
    for (i=0; i < rows-1; i++)
    {
        for (k=i+1; k < rows; k++)
        {
            sum = 0;
            for (j=0; j < columns; j++)
                sum += abs(array[i][j] - array[k][j]);

            if ((i==0 && k==1) || sum < *minimalSum)
            {
                *minimalSum = sum;
                *row1 = i;
                *row2 = k;
            }
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
