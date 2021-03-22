#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void main(int argc, char* argv[])
{
    int i, ii, r, s, total=0;
    int l = 1000;

    for (i=1; i <= l; i++)
    {
        ii = i;
        r = 0;
        s = 0;

        if(ii % 2) s += pow(3,r);

        while (ii /= 2)
        {
            r++;
            if(ii % 2) s += pow(3,r);
        }

        total += s;
        printf("I: %d S: %d Total: %d\n", i, s, total);
    }
}
