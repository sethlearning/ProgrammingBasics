#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "logo.c"

void exitprogram(char *);

int main(int argc, char* argv[])
{
    char inFileName[128], outFileName[128];
    char message[256];
    unsigned char c, cc;
    FILE *in, *out;

    logo();
    printf("Транслит с русского языка в кодировке UTF-8.\n\n");

    if (argc < 3)
    {
        sprintf(message, "Недостаточно аргументов.\nПример запуска программы:\n: %s in.txt out.txt\n", argv[0]);
        exitprogram(message);
    }

    strcpy(inFileName, argv[1]);
    strcpy(outFileName, argv[2]);

    // printf("inFileName: %s\noutFileName: %s\n\n", inFileName, outFileName);

    // open files
    if ( (in = fopen(inFileName, "r")) == NULL )
    {
        sprintf(message, "Ошибка открытия исходного файла: %s.\n", inFileName);
        exitprogram(message);
    }

    if ( (out = fopen(outFileName, "w")) == NULL )
    {
        fclose(in);
        sprintf(message, "Ошибка открытия результирующего файла: %s.\n", outFileName);
        exitprogram(message);
    }

    printf("Исходный файл: %s\nРезультирующий файл: %s\n\n", inFileName, outFileName);

    // process
    while (1)
    {
        c = getc(in);
        if ( feof(in) ) break;

        // printf("%hhu\n", c);

        if (c == 208)
        {
            cc = getc(in);

            switch(cc)
            {
                // А
                case 144:
                putc('A', out);
                break;
                // Б
                case 145:
                putc('B', out);
                break;
                // В
                case 146:
                putc('V', out);
                break;
                // Г
                case 147:
                putc('G', out);
                break;
                // Д
                case 148:
                putc('D', out);
                break;
                // Е
                case 149:
                putc('E', out);
                break;
                // Ё
                case 129:
                putc('Y', out);
                putc('o', out);
                break;
                // Ж
                case 150:
                putc('Z', out);
                putc('h', out);
                break;
                // З
                case 151:
                putc('Z', out);
                break;
                // И
                case 152:
                putc('I', out);
                break;
                // Й
                case 153:
                putc('Y', out);
                break;
                // К
                case 154:
                putc('K', out);
                break;
                // Л
                case 155:
                putc('L', out);
                break;
                // М
                case 156:
                putc('M', out);
                break;
                // Н
                case 157:
                putc('N', out);
                break;
                // О
                case 158:
                putc('O', out);
                break;
                // П
                case 159:
                putc('P', out);
                break;
                // Р
                case 160:
                putc('R', out);
                break;
                // С
                case 161:
                putc('S', out);
                break;
                // Т
                case 162:
                putc('T', out);
                break;
                // У
                case 163:
                putc('U', out);
                break;
                // Ф
                case 164:
                putc('F', out);
                break;
                // Х
                case 165:
                putc('H', out);
                break;
                // Ц
                case 166:
                putc('T', out);
                putc('s', out);
                break;
                // Ч
                case 167:
                putc('C', out);
                putc('h', out);
                break;
                // Ш
                case 168:
                putc('S', out);
                putc('h', out);
                break;
                // Щ
                case 169:
                putc('S', out);
                putc('c', out);
                putc('h', out);
                break;
                // Ъ
                case 170:
                putc('\'', out);
                break;
                // Ы
                case 171:
                putc('Y', out);
                break;
                // Ь
                case 172:
                putc('\'', out);
                break;
                // Э
                case 173:
                putc('E', out);
                break;
                // Ю
                case 174:
                putc('Y', out);
                putc('u', out);
                break;
                // Я
                case 175:
                putc('Y', out);
                putc('a', out);
                break;

                // а
                case 176:
                putc('a', out);
                break;
                // б
                case 177:
                putc('b', out);
                break;
                // в
                case 178:
                putc('v', out);
                break;
                // г
                case 179:
                putc('g', out);
                break;
                // д
                case 180:
                putc('d', out);
                break;
                // е
                case 181:
                putc('e', out);
                break;
                // ж
                case 182:
                putc('z', out);
                putc('h', out);
                break;
                // з
                case 183:
                putc('z', out);
                break;
                // и
                case 184:
                putc('i', out);
                break;
                // й
                case 185:
                putc('y', out);
                break;
                // к
                case 186:
                putc('k', out);
                break;
                // л
                case 187:
                putc('l', out);
                break;
                // м
                case 188:
                putc('m', out);
                break;
                // н
                case 189:
                putc('n', out);
                break;
                // о
                case 190:
                putc('o', out);
                break;
                // п
                case 191:
                putc('p', out);
                break;

                default:
                // printf("%hhu\n", cc);
                putc(c, out);
                putc(cc, out);
            }
        }
        else if (c == 209)
        {
            cc = getc(in);
            // printf("%hhu\n", cc);
            switch (cc)
            {
                // ё
                case 145:
                putc('y', out);
                putc('o', out);
                break;
                // р
                case 128:
                putc('r', out);
                break;
                // с
                case 129:
                putc('s', out);
                break;
                // т
                case 130:
                putc('t', out);
                break;
                // у
                case 131:
                putc('u', out);
                break;
                // ф
                case 132:
                putc('f', out);
                break;
                // х
                case 133:
                putc('h', out);
                break;
                // ц
                case 134:
                putc('t', out);
                putc('s', out);
                break;
                // ч
                case 135:
                putc('c', out);
                putc('h', out);
                break;
                // ш
                case 136:
                putc('s', out);
                putc('h', out);
                break;
                // щ
                case 137:
                putc('s', out);
                putc('c', out);
                putc('h', out);
                break;
                // ъ
                case 138:
                putc('\'', out);
                break;
                // ы
                case 139:
                putc('y', out);
                break;
                // ь
                case 140:
                putc('\'', out);
                break;
                // э
                case 141:
                putc('e', out);
                break;
                // ю
                case 142:
                putc('y', out);
                putc('u', out);
                break;
                // я
                case 143:
                putc('y', out);
                putc('a', out);
                break;

                default:
                // printf("%hhu\n", cc);
                putc(c, out);
                putc(cc, out);
            }
        }
        else
            putc(c, out);

        // putchar(c);

        // fputc(c, result);

    }
    // close files
    fclose(in);
    fclose(out);

}


/*
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
*/

void exitprogram(char *message)
{
    puts(message);
    exit(1);
}
