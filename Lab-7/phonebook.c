#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logo.c"

void GetCommand(char*);
void PrintAll(FILE*);
void Search(FILE*);
void Add(FILE*);
void Edit(FILE*, char*);
void Remove(FILE*, char*);
void SelectRecord(FILE*, char*);
void SwapFiles(FILE*, char*, FILE*, char*);
void GetChar(char*);
void GetString(char*);
void ExitProgram(char*);

int main(int argc, char* argv[])
{
    int quit = 0;
    char example[256], filename[256], str[256], command;
    FILE* file;

    logo();
    printf("Лабораторная работа №7.\nТелефонный справочник.\n\n");
    sprintf(example, "Пример использования:\n%s phonebook.txt", argv[0]);

    if (argc < 2)
    {
        printf("Недостаточно параметров.\n");
        ExitProgram(example);
    }

    file = fopen(argv[1], "r+");
    if (file == NULL)
    {
        printf("Файла не существует.\n");
        ExitProgram(example);
    }

    while (!quit)
    {
        GetCommand(&command);
        switch (command)
        {
            case 'P':
            case 'p':
                PrintAll(file);
                break;
            case 'Q':
            case 'q':
                quit = 1;
                break;
            case 'S':
            case 's':
                Search(file);
                break;
            case 'A':
            case 'a':
                Add(file);
                break;
            case 'E':
            case 'e':
                Edit(file, argv[1]);
                break;
            case 'R':
            case 'r':
                Remove(file, argv[1]);
                break;
        }
    }

    fclose(file);
}

void GetCommand(char* command)
{
    puts("Введите команду:");
    puts("[P] - Print All, [S] - Search, [A] - Add, [E] - Edit, [R] - Remove, [Q] - Quit");
    printf("Command: ");

    GetChar(command);
    printf("\n");
}

void PrintAll(FILE* file)
{
        char c;
        puts("Содержимое файла:");
        while(1)
        {
            c = fgetc(file);
            if ( feof(file) ) break;
            putchar(c);
        }
        puts("\n"); // equivalent to printf("\n\n");
        rewind(file);
}

void Search(FILE* file)
{
    char pattern[256], line[256];

    printf("Поиск\nВведите фамилию: ");
    
    GetString(pattern);

    while ( fgets(line, 256, file) != NULL )
    {
        if ( strstr(line, pattern) )
        printf("%s", line);
    }
    printf("\n");
    rewind(file);
}

void Add(FILE* file)
{
    char name[128], phone[128], line[256];

    printf("Добавление данных\nВведите фамилию: ");
    GetString(name);

    printf("Введите номер телефона: ");
    GetString(phone);

    sprintf(line, "%s\t%s\n", name, phone);

    while ( fgetc(file) != EOF);
    fputs(line, file);

    rewind(file);
}

void Edit(FILE* file, char* filename)
{
    // char pattern[256], name[128], phone[128], string[256], line[256], answer, newname[128], newphone[128], newline[256], tempFileName[128];
    char name[128], phone[128], string[256], line[256], answer, newname[128], newphone[128], newline[256], tempFileName[128];
    char* tabPointer;
    // int count=0, tabPosition;
    int tabPosition;
    FILE* tempfile;
    size_t length;

    printf("Изменение данных\nВведите фамилию: ");
    SelectRecord(file, line);

    printf("Изменяем найденную запись? [Y/N]: ");
    GetChar(&answer);
    if (answer != 'Y' && answer != 'y') return;

    // Get name and phone from line
    tabPointer = strchr(line, '\t');
    tabPosition = tabPointer - line;

    memset(name, '\0', sizeof(name));
    memset(phone, '\0', sizeof(phone));

    strncpy(name, line, tabPosition);
    length = strlen(tabPointer + 1);
    strncpy(phone, tabPointer + 1, length - 1); //Removing closing \n character

    // Get new name and phone from user
    printf("Введите фамилию (Enter - если фамилия не изменяется): ");
    gets(newname);
    if (newname[0] == '\0') strcpy(newname, name);

    printf("Введите телефон (Enter - если телефон не изменяется): ");
    gets(newphone);
    if (newphone[0] == '\0') strcpy(newphone, phone);

    // Creating newline
    sprintf(newline, "%s\t%s\n", newname, newphone);

    // Creating tempfile
    sprintf(tempFileName, "_%s", filename);
    tempfile = fopen(tempFileName, "w");
    if (tempfile == NULL)
    {
        printf("Error creating temporary file\n");
        return;
    }

    // Changing the line in the tempfile
    while ( fgets(string, 265, file) != NULL )
    {
        if ( strcmp(string, line) )
            fputs(string, tempfile);
        else
            fputs(newline, tempfile);
    }

    SwapFiles(file, filename, tempfile, tempFileName);
}

void Remove(FILE* file, char* filename)
{
    char line[256], string[256], tempFileName[128], answer;
    FILE* tempfile;

    printf("Удаление данных\nВведите фамилию: ");

    SelectRecord(file, line);

    printf("Удаляем найденную запись? [Y/N]: ");
    GetChar(&answer);
    if (answer != 'Y' && answer != 'y') return;

    // Creating tempfile
    sprintf(tempFileName, "_%s", filename);
    tempfile = fopen(tempFileName, "w");
    if (tempfile == NULL)
    {
        printf("Error creating temporary file\n");
        return;
    }

    // Changing the line in the tempfile
    while ( fgets(string, 265, file) != NULL )
    {
        if ( strcmp(string, line) )
            fputs(string, tempfile);
    }

    SwapFiles(file, filename, tempfile, tempFileName);
}

// Removing original file and renaming temp file
void SwapFiles(FILE* file, char* filename, FILE* tempfile, char* tempFileName)
{
    fclose(tempfile);
    fclose(file);
    remove(filename);
    rename(tempFileName, filename);
    file = fopen(filename, "r+");
}

// Selecting unique line, used by Edit and Remove functions
void SelectRecord(FILE* file, char* line)
{
    char pattern[256], string[256];
    int count;

    while (count != 1)
    {
        GetString(pattern);

        while ( fgets(string, 256, file) != NULL )
        {
            if ( strstr(string, pattern) )
            {
                printf("%s", string);
                strcpy(line, string);
                count++;
            }
        }
        printf("\n");

        if (count == 0)
        {
            printf("Введенные данные не соответствуют ни одной записи\nУточните данные: ");
        }
        else if (count > 1)
        {
            printf("Введенные данные соответствуют более чем одной записи\nВведите уникальное значение: ");
            count = 0;
        }

        rewind(file);
    }
}

void GetString(char* line)
{
    do gets(line);
    while (line[0] == '\0');
}

void GetChar(char* c)
{
    while ( (*c = getc(stdin)) == '\n' );   // Discard previous \n symbols and get command code
    while ( (getc(stdin)) != '\n' );            // Discard following symbols and closing \n symbol
}

void ExitProgram(char* message)
{
    printf("%s\n", message);
    printf("Нажмите Enter!");
    getchar();
    exit(0);
}
