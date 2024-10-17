#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_CARD 512 // memory cards store data in blocks of 512 bytes | 8 bits = 1 byte

int main(int argc, char *argv[])
{
    // Make sure program runs with just one command-line argument

    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r"); // r = read info from the file (input file)

    // If the file cannot be found or opened
    if (card == NULL)
    {
        printf("File not available\n");
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[MEMORY_CARD];
    int img_counter = 0;                       // track number of images found
    FILE *output = NULL;                       // file pointer to handle recovered images
    char *filename = malloc(8 * sizeof(char)); // allocate memory to each filename

    // Read every 512 byte chunk od the memory card into the buffer
    while (fread(buffer, 1, MEMORY_CARD, card) == MEMORY_CARD)
    {
        // JPG stars with 0xff 0xd8 0xff | fourth byte 0xe0, 0xe1.... 0xef
        //  Check if it is the start of new JPG:
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // if not the first JPG, close the previous one
            if (output != NULL)
            {
                fclose(output);
            }

            // create new filename with 3 digits
            sprintf(filename, "%03i.jpg", img_counter);

            // open the output file to write on it
            output = fopen(filename, "w");

            // write data found in memory card into output file
            fwrite(buffer, 1, MEMORY_CARD, output);
            img_counter++; // update number of images
        }

        // if it is the same file, continue writing on it
        else if (output != NULL)
        {
            fwrite(buffer, 1, MEMORY_CARD, output);
        }
    }

    // Close last output file, if open
    if (output != NULL)
    {
        fclose(output);
    }

    // free memory space (malloc)
    free(filename);

    // close files
    fclose(card);

    return 0;
}
