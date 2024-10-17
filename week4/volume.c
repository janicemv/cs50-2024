// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44; // reference number of bytes of header

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r"); // open input file
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w"); // open output file
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Scale volume
    float factor = atof(argv[3]); // 3rd argument to a float

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];          // buffer array called header with 44 bytes (HEADER_SIZE)
    fread(header, HEADER_SIZE, 1, input); // read the header from input to this buffer
    fwrite(header, HEADER_SIZE, 1, output); // write these contents to output

    // TODO: Read samples from input file and write updated data to output file

    // Create a buffer for a single sample
    int16_t buffer; // Stores 2-byte sample

    // Read single sample from input into buffer while there are samples left to read
    while (fread(&buffer, sizeof(int16_t), 1, input) !=
           0) // read from input, passing value (2 bytes) to buffer
    {
        // Update volume of sample
        buffer *= factor;

        // Write updated sample to output file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
