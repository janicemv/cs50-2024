from cs50 import get_int

# Prompt user for height between 1 and 8
while True:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break  # exit the loop when conditions are met, continue

# Print the pyramid aligned to the right
for i in range(0, h, 1):  # line - from position 0 to total height, 1 by 1
    for j in range(0, h, 1):  # column - from position 0 to total height, 1 by 1
        if (i + j < h - 1):  # print spaces
            print(" ", end="")  # end: so it doesn't print next line
        else:
            print("#", end="")
    print() # new line
