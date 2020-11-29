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
    while(dollars <= 0);

    int cents = round(dollars * 100);


    if (cents >= 25)
    {
        change += cents / 25;
        cents = cents % 25;
    }

    if (cents >= 10)
    {
        change += cents / 10;
        cents = cents % 10;
    }

    if (cents >= 5)
    {
        change += cents / 5;
        cents = cents % 5;
    }

    change += cents;


    printf("%d\n", change);
}