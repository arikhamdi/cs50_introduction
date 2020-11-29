#include <cs50.h>
#include <math.h>
#include <stdio.h>


int count_letters(string text);
int count_words(string some_text);
int count_sentences(string some_text);

int main(void)
{
    // Prompt the user for a string of text
    string text = get_string("Text: ");

    // Count the number of letters (lower and uppercase)
    int number_of_letters = count_letters(text);
    // Count the number of words (separated by space)
    int number_of_words = count_words(text);
    // Count the number of sentences (separated by period, exclamation point or question mark)
    int number_of_sentences = count_sentences(text);

    // L is the average number of letters per 100 words in the text
    float l = ((float)number_of_letters / number_of_words) * 100;
    // S is the average number of sentences per 100 words
    float s = ((float)number_of_sentences / number_of_words) * 100.00;
    // Putting it all together
    float index = 0.0588 * l - 0.296 * s - 15.8;
    int grade = round(index);

    // Print the output "Grade X"
    if (grade < 1)
    {
        // If the index number is less than 1 => "Before Grade 1"
        printf("Before Grade 1");
    }
    else if (grade > 16)
    {
        // If the resulting index number is 16 or higher => "Grade 16+"
        printf("Grade 16+");
    }
    else
    {
        printf("Grade %i", grade);
    }
    printf("\n");
}

int count_letters(string some_text)
{
    int letters = 0;
    for (int i = 0; some_text[i] != '\0'; i++)
    {
        if ((some_text[i] >= 65 && some_text[i] <= 90) || (some_text[i] >= 97 && some_text[i] <= 122))
        {
            letters++;
        }
    }
    return letters;
}

int count_words(string some_text)
{
    int words = 0;
    for (int i = 0; some_text[i] != '\0'; i++)
    {
        if (some_text[i] == ' ')
        {
            words++;
        }
    }
    return words + 1;
}

int count_sentences(string some_text)
{
    int sentences = 0;
    for (int i = 0; some_text[i] != '\0'; i++)
    {
        if (some_text[i] == '!' || some_text[i] == '.' || some_text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}