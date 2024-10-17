#include <cs50.h>
#include <stdio.h>

// declare function that will appear later on
void print_row(int spaces, int bricks);

int main(void)
{
    // Prompt the user for the pyramid's height
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Print a pyramid of that height
    for (int i = 0; i < n; i++)
    {
        // Print row of bricks
        int spaces = n - i - 1;
        int bricks = i + 1;
        print_row(spaces, bricks);
    }
}

// Function to print row of the pyramid
void print_row(int spaces, int bricks)
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

    // Print new line
    printf("\n");
}