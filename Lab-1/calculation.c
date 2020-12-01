#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "logo.c"

int main(int argc, char *argv[])
{
    double a, b, c, x, t, y;

    logo();
    printf("Лабораторная работа №1.\nРасчет формулы.\n\n");

    printf("Введите значение X ==> ");
    scanf("%lf", &x);
    
    a = sin(x);
    b = pow(cos(x),2);
    c = 1 + tan(x);
    
    // Calculation
    t = a + b;          // (a+b)
    t = pow(t, 2);      // (a+b)^2
    t = (a * b) + t;    // a*b + (a+b)^2
    t = x * t;          // x((a*b + (a+b)^2)
    t = pow(c, 2) + t;  // c^2 + x((a*b + (a+b)^2)
    t = x * t;          // x(c^2 + x((a*b + (a+b)^2))
    t = pow(b, 2) + t;  // b^2 + x(c^2 + x((a*b + (a+b)^2))
    t = x * t;          // x(b^2 + x(c^2 + x((a*b + (a+b)^2)))

    y = 4 * pow(a, 2) + t;  // 4a^2 + x(b^2 + x(c^2 + x((a*b + (a+b)^2)))
    
    printf("y: %lf\n\n", y);
}