from cs50 import get_int

# Prompt user for height between 1 and 8
while True:
    h = get_int("Height: ")
    if h > 0 and h < 9:
        break                   # exit the loop when conditions are met, continue

# Print pyramid
for hashes in range(1, h + 1):
    spaces = h - hashes

    print(" " * spaces, end="") # Left side
    print("#" * hashes, end="")
    print("  ", end="")         # Gap
    print("#" * hashes)         # Right side
