#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


bool check_command_line_argument(string cmd);
void shift_characters(string text, int key);


int main(int argc, string argv[])
{
    //GET KEY
    // accept a command line argument, non-negative integer
    string k = argv[1];

    // Ensure single command-line argument
    // make sure argument contains only digit characers
    if (argc != 2 || check_command_line_argument(k))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Convert argument to an integer
    int key = atoi(k);
    // GET PLAINTEXT

    // prompt the user to type in the plain text
    string plaintext = get_string("plaintext: ");


    // ENCIPHER
    // shifting all the letters by the key to get the cipher text result
    // verify if it is an alphabetic character, preserve case
    // PRINT CIPHERTEXT
    shift_characters(plaintext, key);


}

bool check_command_line_argument(string cmd)
{
    // check every single character in the string
    for (int i = 0; cmd[i] != '\0'; i++)
    {
        // make sure argument contains only digit characers
        if (cmd[i] < 47 || cmd[i] > 58)
        {
            return true;
        }
    }
    return false;
}

void shift_characters(string text, int key)
{
    printf("ciphertext: ");
    char c;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                c = ((text[i] - 65) + key) % 26;
                printf("%c", c + 65);
            }
            else if (islower(text[i]))
            {
                c = ((text[i] - 97) + key) % 26;
                printf("%c", c + 97);
            }
        }
        else
        {
            printf("%c", text[i]);
        }

    }
    printf("\n");
}