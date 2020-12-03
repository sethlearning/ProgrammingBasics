#include <stdlib.h>
#include <stdio.h>
#include "logo.c"


int main(int argc, char* argv[])
{
    char ipconfig[] = "ipconfig";
    char countCommand[] = "ls /dev/ | grep --regexp tty[[:digit:]] --count";
    char busyCountCommand[] = "w | tail -n +3 | wc -l";
    char usersCommand[] = "w | tail -n +3 | awk '{print $2 \": \" $1}'";
    char count[16], busyCount[16];
    FILE* pipe;

    logo();
    printf("Лабораторная работа №8.\n");
    printf("Получить количество возможных виртуальных терминалов, задействованных терминалов и пользователей, за ними работающих.\n\n");

    pipe = popen(countCommand, "r");
    fgets(count, sizeof(count), pipe);
    pclose(pipe);
    printf("Количество возможных терминалов: %s\n", count);

    pipe = popen(busyCountCommand, "r");
    fgets(busyCount, sizeof(busyCount), pipe);
    pclose(pipe);
    printf("Количество задействованных терминалов: %s\n", busyCount);

    printf("Используемые терминалы и имена пользователей: \n");
    system(usersCommand);
}
