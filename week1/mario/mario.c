#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int blocks;

    do
    {
        blocks = get_int("Height: ");
    }
    while (blocks < 1 || blocks > 8);

    for (int i = 0; i < blocks; i++)
    {
        for (int j = 0; j < blocks - (i + 1) ; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        printf("\n");

    }
}



