from cs50 import get_string


def main():
    while(True):
        number = get_string("Number: ")
        if int(number) > 0:
            break

    # Checksum
    # Multiply every other digit by 2, starting with second-last digit
    # Add those products' digits together
    # Add the sum to the sum of the digits that weren't multiplied by 2
    # if the total's last digit is 0, number is valid!
    first_set = 0
    second_set = 0

    for i in range(len(number), 0, -1):
        if (i - len(number)) % 2 != 0:
            other = int(number[i - 1]) * 2
            if other > 9:
                first_set += other % 10 + other // 10
            else:
                first_set += other
        else:
            second_set += int(number[i - 1])

    total = str(first_set + second_set)

    if total[-1] == "0":
        if number[0] == "4" and (len(number) == 13 or len(number) == 16):
            print("VISA")
        elif (number[0:2] >= "51" and number[0:2] <= "55") and len(number) == 16:
            print("MASTERCARD")
        elif (number[0:2] == "34" or number[0:2] == "37") and len(number) == 15:
            print("AMEX")
        else:
            print("INVALID")
    else:
        print("INVALID")


main()
