#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "logo.c"


int main(int argc, char* argv[])
{
    double x0 = 0.1, x8 = 0.8, h = 0.1, e = 0.00001, x, item;
    int n, i;
    int debug = 0;
    double result[8][2];

    logo();
    printf("Лабораторная работа №9.\nСоставить таблицу функции: (1/2) - (Pi/4) * abs(six(x))\n\n");

    x = x0;
    i = 0;
    while (x <= x8)
    {
        n = 1;
        result[i][0] = x;
        result[i][1] = 0;
        while (1)
        {
            item = cos(2*n*x)/(4*pow(n, 2)-1);
            result[i][1] += item;

            if ((item >= 0 && item < e) || (item < 0 && -item < e)) break;
            n++;
        }
        x+=h;
        i++;
    }

    printf(" X       F(x)\n");
    for (i=0; i < 8; i++)
    {
        printf("%.1f   % f\n", result[i][0], result[i][1]);
    }
    printf("\n");
}
