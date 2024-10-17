#include <cs50.h>
#include <stdio.h>

// Declare functions
void print_left(int spaces, int bricks);
void print_right(int bricks);

int main(void)
{
    // Prompt user for height (n) of the pyramid
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Print a pyramid of that height (p = position)
    for (int p = 0; p < n; p++)
    {
        // Left side
        int left = n - p - 1;
        int bricks = p + 1;
        print_left(left, bricks);

        // Gap
        printf("  ");

        // Right side
        int right = p + 1;
        print_right(right);

        // New row
        printf("\n");
    }
}

// Function to the left side of the pyramid
void print_left(int spaces, int bricks)
{
    // Print spaces to the left
    for (int j = 0; j < spaces; j++)
    {
        printf(" ");
    }

    // Print bricks
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}

// Function to the right side of the pyramid
void print_right(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}