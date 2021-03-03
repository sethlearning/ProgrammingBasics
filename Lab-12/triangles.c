#include <stdlib.h>
#include <stdio.h>

int isTriangle(int, int, int);

void main(int argc, char* argv[])
{
    int a=1, b=1, c=0, n=0, i;
    int l=2100;

    for (i=3; i <= l; i++)
    {
        while (1)
        {
            if (a==i)
            {
                printf("I: %d, N: %d\n", i, n);
                a = b = 1;
                n = 0;
                break;
            }

            c = i - a - b;

            if (c >= b)
            {
                if (isTriangle(a,b,c)) n++;
                b++;
            }
            else
            {
                a++;
                b = a;
            }
        }
    }
}

int isTriangle(int a, int b, int c)
{
    if (a < b + c && b < a + c && c < a + b) return 1;
    else return 0;
}
