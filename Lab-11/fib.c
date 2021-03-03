#include <stdio.h>
#include <stdlib.h>

void main(int argc, char* argv[])
{
    int i, l, count = 30;
    long long s, f[30], multiply;

    f[0] = f[1] = 1;

    for (i=2; i < count; i++)
    {
        f[i] = f[i-1] + f[i-2];
    }

    s = f[0] + f[1];

    for (i=2; i < count; i++)
    {
        if(i%3 == 1) s += f[i];

        else if (i%3 == 2) s -= f[i];

        else s -= f[i-1] * (f[i]-1);

        printf("N: %d   S: %lld\n", i+1, s);
    }
}
