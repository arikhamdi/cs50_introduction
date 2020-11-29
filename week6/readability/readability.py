from cs50 import get_string


def main():
    # Prompt the user for a string of text
    text = get_string("Text: ")

    # Count the number of letters (lower and uppercase)
    number_of_letters = count_letters(text)
    number_of_words = count_words(text)
    number_of_sentences = count_sentences(text)

    # L is the average number of letters per 100 words in the text
    l = (number_of_letters / number_of_words) * 100
    # S is the average number of sentences per 100 words
    s = (number_of_sentences / number_of_words) * 100

    # Putting it all together
    index = 0.0588 * l - 0.296 * s - 15.8
    grade = round(index)

    # Print the output "Grade X"
    if grade < 1:
        # If the index number is less than 1 => "Before Grade 1"
        print("Before Grade 1")
    elif grade > 16:
        # If the resulting index number is 16 or higher => "Grade 16+"
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


def count_letters(some_text):
    cpt = 0
    for i in some_text:
        if i.isalpha():
            cpt += 1
    return cpt


def count_words(some_text):
    cpt = 0
    for i in some_text:
        if i == " ":
            cpt += 1
    return cpt + 1


def count_sentences(some_text):
    cpt = 0
    for i in some_text:
        if i in ["!", ".", "?"]:
            cpt += 1
    return cpt


main()