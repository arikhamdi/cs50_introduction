#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;

    do
    {
        number = get_long("Number: ");
    }
    while (!number);

    int counter = 0;
    int first_set = 0;
    int second_set = 0;
    int remainder = 0;
    int start_number = 0;

    while (number > 0)
    {
        counter ++;
        if (number > 9)
        {
            start_number = number;
        }

        remainder = number % 10;

        if (counter % 2 == 0)
        {
            remainder *= 2;
            if (remainder > 9)
            {
                remainder = remainder % 10 + remainder / 10;
            }

            first_set += remainder;
        }
        else
        {
            second_set += remainder;
        }
        number = number / 10;
    }
    int sum = first_set + second_set ;

    if (sum % 10 == 0)
    {
        if (start_number / 10 == 4 && (counter == 13 || counter == 16))
        {
            printf("VISA\n");
        }
        else if ((start_number >= 51 && start_number <= 55)  && counter == 16)
        {
            printf("MASTERCARD\n");
        }
        else if ((start_number == 34 || start_number == 37) && counter == 15)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

