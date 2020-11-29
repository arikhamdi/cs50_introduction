#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    int change = 0;
    float dollars;

    do
    {
         dollars = get_float("Change owed: ");
    }
    while (dollars <= 0);

    int cents = round(dollars * 100);

    while (cents > 0)
    {
        if (cents >= 25)
        {
            change ++;
            cents = cents - 25;
        }
        else if (cents >= 10)
        {
            change ++;
            cents = cents - 10;
        }
        else if (cents >= 5)
        {
            change ++;
            cents = cents - 5;
        }
        else
        {
            change += cents;
            cents = 0;
        }
    }

    printf("%d\n", change);
}