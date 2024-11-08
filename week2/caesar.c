#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument

    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Define key
    string key = argv[1];

    // Make sure every character i n argv[1] is a digit

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

    }

    // Convert argv[1] from a string to an int

    int k = atoi(key);

    // Prompt user for plaintext

    string plaintext = get_string("Plaintext: ");

    printf("Ciphertext: ");

    // Cipher

    // Rotate the character if it's a letter

    for (int j = 0; j < strlen(plaintext); j++)

    {

        // Case sensitive: ASCII A to Z is from 65 to 90
        if (isupper(plaintext[j]))
        {
            printf("%c", (((plaintext[j] - 65 + k) % 26) + 65));
        }

        // Case sensitive: ASCII a to z is from 97 to 122
        else if (islower(plaintext[j]))
        {
            printf("%c", (((plaintext[j] - 97 + k) % 26) + 97));
        }

        else
        {
            printf("%c", plaintext[j]);
        }

     }

      printf("\n");

}

