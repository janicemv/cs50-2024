from cs50 import get_int

# Prompt user for height between 1 and 8
while True:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break  # exit the loop when conditions are met, continue

# Print pyramid
for i in range(0, h, 1):  # rows
    for j in range(0, h + i + 3, 1):  # columns
        if (j == h or j == h + 1 or i + j < h - 1):
            print(" ", end="")
        else:
            print("#", end="")
    print()
