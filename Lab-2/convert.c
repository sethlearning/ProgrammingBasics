#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "logo.c"

int main(int argc, char *argv[])
{
  const double ratio = 453.6;
  double funts;
  int kilogramms, gramms, grammsTotal;
    
  logo();
  printf("Лабораторная работа №2.\nПеревод массы из фунтов в килограммы и граммы.\n\n");
  
  printf("Введите массу в фунтах ==> ");
  scanf("%lf", &funts);

  grammsTotal = funts * ratio;
  kilogramms = grammsTotal / 1000;
  gramms = grammsTotal % 1000;

  printf("Килограммов: %d, граммов: %d\n\n", kilogramms, gramms);

}