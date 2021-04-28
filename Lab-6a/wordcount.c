#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logo.c"

int isAlpha(char);
void logging(FILE*, char*);
void timestamp(FILE*);
void help(char*, char*);

int main(int argc, char* argv[])
{
    char filename[512], logfilename[512], message[512], example[512], word[128];
    char c;
    FILE *file, *log;
    int wordcount = 0, sameword = 0, alpha = 0;
    int i;

    logo();
    printf("Лабораторная работа №6.\nПодсчет количества слов в текстовом файле.\n\n");
    snprintf(example, 200, "Пример использования:\n%s filename=file.txt logfile=log.txt", argv[0]);


    // Arguments
    if (argc < 3)
        help("Недостаточно параметров.", example);

    for (i = 0; i < argc; i++)
    {
        if (strstr(argv[i], "filename=")) strcpy(filename, argv[i] + 9);
        if (strstr(argv[i], "logfile=")) strcpy(logfilename, argv[i] + 8);
    }

    // Logfile
    if ((log = fopen(logfilename, "w")) == NULL)
    {
        sprintf(message, "Ошибка открытия файла журнала: %s", logfilename);
        help(message, example);
    }

    logging(log, "Начало работы.");

    // Textfile
    if ((file = fopen(filename, "r")) == NULL)
    {
        sprintf(message, "Ошибка открытия файла: %s", filename);

        logging(log, message);
        logging(log, "Завершение работы");
        fclose(log);

        help(message, example);
    }

    sprintf(message, "Файл открыт: %s", filename);
    logging(log, message);

    printf("Содержимое файла %s:\n", filename);

    i = 0;
    while(1)
    {
        c = getc(file);
        if ( feof(file) ) break;

        alpha = isAlpha(c);

        if ( alpha && !sameword ) // New word begins
        {
            sameword = 1;
            word[i] = c;
            i++;
        }

        else if ( alpha && sameword ) // The word continues
        {
            word[i] = c;
            i++;
        }

        else if (!alpha && sameword) // The word ended on previous symbol, current symbol is not a part of it
        {
            word[i] = '\0';
            printf("%s", word);
            wordcount++;
            sameword = 0;
            i = 0;
            word[i] = '\0';
            printf("%c", c);
        }

        else if (!alpha && !sameword) // Not a part of a word
            printf("%c", c);
    }

    if (sameword)   // There was a word in processing, print and count it. (The case, where file ends with letter and not with non-word symbol.)
    {
        word[i] = '\0';
        printf("%s", word);
        wordcount++;
    }

    sprintf(message, "Количество слов в файле: %i", wordcount);
    printf("\n\n%s\n\n", message);
    logging(log, message);

    logging(log, "Завершение работы.");

    // Close files
    fclose(file);
    fclose(log);
}

int isAlpha(char c)
{
    char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_@&";

    if ( strchr(letters, c) )
        return 1;
    else
        return 0;
}

void timestamp(FILE *log)
{
    time_t t;
    time(&t);
    fprintf(log, "%s", ctime(&t));
}

void help(char *message, char *example)
{
    printf("%s\n\n%s\n\n", message, example);
    exit(0);
}

void logging(FILE *log, char *message)
{
    timestamp(log);
    fprintf(log, "%s\n\n", message);
}
