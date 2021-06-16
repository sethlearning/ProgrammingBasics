#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logo.c"
#include "listsfunctions.c"

void exitprogram(char*);
void processConfig(FILE *, int *, int *, int *);
void fillInListAuto(struct thelist *, int);
void fillInListManual(struct thelist *, int);
void countNegatives(struct thelist *, int *, int *);

int main(int argc, char* argv[])
{
    char *configFileName = "lists.conf";
    char message[256];

    int listsize = 0;
    int autofill = -1;
    int additional = 0;

    FILE *config;

    struct thelist *alist;

    int i, t;
    int ncount = 0, nsum = 0;

    logo();
    printf("Лабораторная работа №3.\nВ списке целых ненулевых чисел инвертировать N элементов начиная с K.\n\n");

    if ( (config = fopen(configFileName, "r")) == NULL )
    {
        sprintf(message, "Ошибка открытия файла конфигурации: %s.\n", configFileName);
        exitprogram(message);
    }

    processConfig(config, &autofill, &listsize, &additional);
    printf("Значения параметров:\n    listsize = %i\n    autofill = %i\n\n", listsize, autofill);

    // create
    alist = create();

    if (autofill)
        fillInListAuto(alist, listsize);
    else
        fillInListManual(alist, listsize);

    printf("Содержимое списка:\n");
    print(alist);

    if (additional)
    {
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
    }

    // negatives
    countNegatives(alist, &ncount, &nsum);
    printf("Количество отрицательных элементов: %i \nИх сумма: %i\n\n", ncount, nsum);

    // destroy
    destroy(alist);
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

void fillInListAuto(struct thelist *alist, int size)
{
    int i, t;

    srand(time(NULL));

    for (i = 1; i <= size; i++)
        append(alist, rand() % 100 - 50);
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
}

void exitprogram(char *message)
{
    puts(message);
    exit(1);
}
