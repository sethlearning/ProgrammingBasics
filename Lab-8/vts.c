#include <stdlib.h>
#include <stdio.h>
#include "logo.c"


int main(int argc, char* argv[])
{
    char ipconfig[] = "ipconfig";
    char countCommand[] = "ls /dev/ | grep --regexp tty[[:digit:]] --count";
    char usersCommand[] = "w | tail -n +3 | awk '{print $2 \": \" $1}'";
    char count[16];
    FILE* pipe;

    pipe = popen(countCommand, "r");
    fgets(count, sizeof(count), pipe);
    pclose(pipe);
    printf("Количество возможных терминалов: %s\n", count);

    printf("Используемые терминалы и имена пользователей: \n");
    system(usersCommand);
}
