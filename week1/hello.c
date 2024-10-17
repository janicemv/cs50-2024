#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for name
    string first_name = get_string("What's your name? ");
    // Print "Hello, name!"
    printf("Hello, %s!\n", first_name);
}