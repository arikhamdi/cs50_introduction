#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>


bool check_for_alphabetic_chars(string sub_key);
void map_plaintext(string plaintext, string substitution_key);

int main(int argc, string argv[])
{
    // GET THE KEY
    // get the substition string as a command-line agrument, if there are more or less than one argument
    // remind the user ho to use the program : Usage: ./substitution key
    if (argc != 2)
    {
        printf("Usage: ./substitutiuon key\n");
        return 1;
    }
    string substitution_key = argv[1];

    // VALIDATE THE KEY
    // "Key must contain 26 characters." -> check the key length
    if (strlen(substitution_key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // return 1, to stop the program
    if (!check_for_alphabetic_chars(substitution_key))
    {
        return 1;
    }

    // GET PLAINTEXT
    // prompt the user to type some plain text
    string plaintext = get_string("plaintext: ");

    // ENCIPHER and PRINT CIPHERTEXT
    map_plaintext(plaintext, substitution_key);

}

bool check_for_alphabetic_chars(string sub_key)
{
    for (int i = 0; i < strlen(sub_key); i++)
    {
        // "Key must only cointain alphabetic characters."
        if (isalpha(sub_key[i]))
        {
            // "Key must not contain repeated characters."
            for (int j = 0; j < strlen(sub_key) ; j++)
            {
                if (i != j)
                {
                    if (isupper(sub_key[i]))
                    {
                        if (sub_key[i] == sub_key[j] || sub_key[i] + 32 == sub_key[j])
                        {
                            printf("Key must not contain repeated characters.\n");
                            return false;
                        }
                    }
                    else
                    {
                        if (sub_key[i] == sub_key[j] || sub_key[i] - 32 == sub_key[j])
                        {
                            printf("Key must not contain repeated characters.\n");
                            return false;
                        }
                    }
                }


            }
        }
        else
        {
            printf("Key must only cointain alphabetic characters.\n");
            return false;
        }
    }
    return true;
}

void map_plaintext(string plaintext, string substitution_key)
{
    printf("ciphertext: ");
    char c;
    // for each alphabetic character, determine what letter it maps to
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (islower(plaintext[i]))
        {
            c = substitution_key[plaintext[i] - 97];
            if (islower(c))
            {
                printf("%c", c);
            }
            else
            {
                printf("%c", c + 32);
            }

        }
        else if (isupper(plaintext[i]))
        {
            c = substitution_key[plaintext[i] - 65];
            if (isupper(c))
            {
                printf("%c", c);
            }
            else
            {
                printf("%c", c - 32);
            }

        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    // preserve case
    // leave non-alphabetic characters as-is
    printf("\n");

}