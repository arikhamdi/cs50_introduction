from cs50 import get_int

while(True):
    height = get_int("Height: ")
    if (height in range(1, 9)):
        break

for i in range(1, height+1):
    print(" " * (height - i) + "#" * i + "  " + "#" * i)