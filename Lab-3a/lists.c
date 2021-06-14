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
void countNegatives(struct thelist *, int *, int *);

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
    int ncount = 0, nsum = 0;

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

    // create
    alist = create();

    if (autofill)
        fillInListAuto(alist, listsize);
    else
        fillInListManual(alist, listsize);

    print(alist);

    // insert
    printf("Insert\n");
    insert(alist, 3, 100);
    insert(alist, 15, 200);
    print(alist);

    // replace
    printf("Replace\n");
    replace(alist, 3, alist->info);
    print(alist);

    // remove
    printf("Remove\n");
    removeElement(alist, 3);
    removeElement(alist, alist->info);
    print(alist);

    // negatives
    countNegatives(alist, &ncount, &nsum);
    printf("Количество отрицательных элементов: %i \nИх сумма: %i\n\n", ncount, nsum);

    // destroy
    destroy(alist);

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
        t = rand() % 100 - 50;
        printf("%i  ", t);
        append(alist, t);
        // append(alist, rand() % 100 - 50);
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

void countNegatives(struct thelist *alist, int *ncount, int *nsum)
{
    int i, value;

    for (i = 1; i <= alist->info; i++)
    {
        value = getValue(alist, i);
        if (value < 0)
        {
            (*ncount)++;
            *nsum += value;
        }
    }
    printf("Count: %i, Sum: %i\n", *ncount, *nsum);
}

void exitprogram(char *message)
{
    puts(message);
    exit(1);
}
