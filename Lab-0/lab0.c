#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void PressEnter();

int main(int argc, char *argv[])
{
    // logo
    printf("\n");
    printf("     /   /  *****  ***** ***** *   *\n");
    printf("    /   /   *      *       *   *   *\n");
    printf("   /   /    *****  ****    *   *****\n");
    printf("  /   /         *  *       *   *   *\n");
    printf(" /   /      *****  *****   *   *   *\n");
    printf("                   Автор: Васин С.В.\n\n");

    printf("Лабораторная работа №0.\nВывод сообщений в зависимости от указанных аргументов.\n\n");

    // No arguments
    if (argc < 2)
    {
        printf("Не хватает аргументов!!!\n");
        printf("Используйте %s hawk/griffin\n", argv[0]);
        PressEnter();
    }

    // hawk
    if (!strcmp(argv[1], "hawk"))
    {
        printf("Long Live Atreides!\n");
        PressEnter();
    }

    // griffin
    if (!strcmp(argv[1], "griffin"))
    {
        printf("Viva la Harkonnen!\n");
        PressEnter();
    }

    // undocumented feature - worm
    if (!strcmp(argv[1], "worm"))
    {
        printf("The King of the Dune!\n");
        PressEnter();
    }

    // not one of the aforementioned
    printf("На Арракисе не встречается!\n");
    PressEnter();
}

// Press Enter and close the program
void PressEnter()
{
    printf("Нажмите Enter!\n");
    getchar();
    exit(0);
}