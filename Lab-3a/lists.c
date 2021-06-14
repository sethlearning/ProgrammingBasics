#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logo.c"
#include "listsfunctions.c"

void exitprogram(char*);
void processConfig(FILE *config, int *autof, int *size);
void fillInListAuto(struct thelist *, int);
void fillInListManual(struct thelist *, int);




/*
void ExitProgram(char*);

void DefineArrayManual(int*, int);
void DefineArrayAuto(int*, int);
void PrintArray(int*, int);
void CountNegatives(int*, int, int*, int*);
*/



int main(int argc, char* argv[])
{
    char *configFileName = "lists.conf";
    // char buffer[128];
    // char fillmethod[7];
    char message[256];

    int listsize = 0;
    int autofill = -1;

    FILE *config;

    struct thelist *alist;

    int i, t;

    // memset(fillmethod, '\0', sizeof(fillmethod));

    logo();
    printf("Лабораторная работа №3.\nВ списке целых чисел подсчитать количество отрицательных элементов и их сумму.\n\n");

    if ( (config = fopen(configFileName, "r")) == NULL )
    {
        sprintf(message, "Ошибка открытия файла конфигурации: %s.\n", configFileName);
        exitprogram(message);
    }

    processConfig(config, &autofill, &listsize);
    printf("Значения параметров:\n    listsize = %i\n    autofill = %i\n\n", listsize, autofill);
    // printf("autofill = %i\n", autofill);

    alist = create();

    if (autofill)
        fillInListAuto(alist, listsize);
    else
        fillInListManual(alist, listsize);

    print(alist);
    destroy(alist);

/*
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
*/
}

void processConfig(FILE *config, int *autof, int *size)
{
    char buffer[128];
    char fillmethod[7];

    memset(fillmethod, '\0', sizeof(fillmethod));

    fgets(buffer, 128, config);

    if ( strcmp(buffer, "#!Config file for lists\n") )
        exitprogram("Ошибка заголовка файла конфигурации.\nОжидаемое значение: #!Config file for lists\n");

    while(1)
    {
        if ( fgets(buffer, 128, config) == NULL ) break;
        // if ( feof(config) ) break;

        if (buffer[0] == '#') continue;

        if (buffer[0] == '!')
        {
            puts(buffer + 1);
            continue;
        }

        if ( strstr(buffer, "listsize=") )
        {
            *size = atoi( buffer + strlen("listsize=") );
            // printf("%i\n", listsize);
            continue;
        }

        if ( strstr(buffer, "fillmethod=") )
        {
            strncpy(fillmethod, buffer + strlen("fillmethod="), 6);
            // printf("%s", fillmethod);
            continue;
        }
    }

    if ( !strcmp(fillmethod, "auto") )
        *autof = 1;
    else if ( !strcmp(fillmethod, "manual") )
        *autof = 0;

    if (*size <= 0 || *autof < 0)
        exitprogram("Ошибка файла конфигурации.\nФайл должен содержать правильные значения параметов listsize и fillmethod.\n");
    
    // printf("Значения параметров:\n    listsize = %i\n    fillmethod = %s\n    autofill = %i\n\n", *size, fillmethod, *autof);
}

void fillInListAuto(struct thelist *alist, int size)
{
    int i, t;

    srand(time(NULL));

    for (i = 1; i <= size; i++)
    {
        t = rand() % 100 - 10;
        printf("%i  ", t);
        append(alist, t);
        // append(alist, rand() % 100 - 10);
    }
    printf("\n\n");
}

void fillInListManual(struct thelist *alist, int size)
{
    int i;
    char input[10];

    for (i = 1; i <= size; i++)
    {
        printf("Введите элемент %i: ", i);
        gets(input);
        append(alist, atoi(input));
    }
    printf("\n");
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
/*
void ExitProgram(char* message)
{
    printf("%s\n", message);
    printf("Нажмите Enter!");
    getchar();
    exit(0);
}
*/

void exitprogram(char *message)
{
    puts(message);
    exit(1);
}