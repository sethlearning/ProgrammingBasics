#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    /*
    sums
        [0] = 3
        [1] = 5
        [2] = 7
        [3] = 9
        [4] = 11
        [5] = 13
        [6] = 15
        [7] = 17
        [8] = 19
        [9] = 21
        [10] = 23
        [11] = 25
    */
    int sums[12], numberStart = 10000, numberEnd = 99999, number, i, divisorsCount, middle;

    for (number = numberStart; number <= numberEnd; number++)
    {
        divisorsCount = 0;
        middle = number / 2;  // not going to check the second half, will add number itself later
        for (i = 1; i <= middle; i++)
        {
            if (!(number % i))
            {
                divisorsCount++;
            }
        }
        divisorsCount++; // number itself

        if ((divisorsCount % 2) && (divisorsCount >= 3) && (divisorsCount <= 25))
        {
            sums[divisorsCount/2-1] += number;
            printf ("Number: %i DivisorsCount: %i\n", number, divisorsCount);
        }
    }

    printf("\n");
    for (i = 0; i <= 11; i++)
    {
        printf("Делителей: %i, Сумма: %i\n", (i+1)*2+1, sums[i]);
    }
    printf("\n");
}
