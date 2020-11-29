from cs50 import get_float


def main():
    while True:
        dollars = get_float("Change owed: ")

        if dollars > 0:
            break

    cents = round(dollars * 100)
    change = 0

    while cents > 0:
        if cents >= 25:
            change += 1
            cents -= 25
        elif cents >= 10:
            change += 1
            cents -= 10
        elif cents >= 5:
            change += 1
            cents -= 5
        else:
            change += cents
            cents = 0

    print(change)


main()