#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++) // row
    {
        for (int j = 0; j < width; j++) // column
        {
            // Take average of red, green, and blue - a float assures a more precise average
            int average = round((float) (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);

            // Update pixel values
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++) // row
    {
        for (int j = 0; j < width; j++) // column
        {
            // Compute sepia values using formula
            int sepiaRed = round((image[i][j].rgbtRed * 0.393) + (image[i][j].rgbtGreen * 0.769) +
                                 (image[i][j].rgbtBlue * 0.189));
            int sepiaGreen = round((image[i][j].rgbtRed * 0.349) + (image[i][j].rgbtGreen * 0.686) +
                                   (image[i][j].rgbtBlue * 0.168));
            int sepiaBlue = round((image[i][j].rgbtRed * 0.272) + (image[i][j].rgbtGreen * 0.534) +
                                  (image[i][j].rgbtBlue * 0.131));

            // Make sure it is a value between 0 and 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temporary variables to store content
    RGBTRIPLE temp[height][width];
    int last_pixel = width;
    int first_pixel;

    // Loop over all pixels
    for (int i = 0; i < height; i++) // rows
    {
        last_pixel = width - 1;
        first_pixel = 0;

        for (int j = 0; j < width / 2; j++) // columns (starts in the middle of the image)
        {
            // Swap pixels

            temp[0][0] = image[i][first_pixel];
            image[i][first_pixel] = image[i][last_pixel];
            image[i][last_pixel] = temp[0][0];

            last_pixel = last_pixel - 1;
            first_pixel = first_pixel + 1;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width]; // temporary file to store changed pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++) // rows
    {
        for (int j = 0; j < width; j++) // columns
        {
            int totalRed = 0; // total of colors of valid neighour pixels
            int totalBlue = 0;
            int totalGreen = 0;
            float number_pixels = 0.00; // counter: number of valid neighbour pixels

            // Get neighbour pixels - the pixel we are changing is position [0, 0]
            for (int x = -1; x < 2; x++) // go through range of neighbour pixels from each pixel =>
                                         // x (row) is between -1 and 1
            {
                for (int y = -1; y < 2; y++) // go through range of neighbour pixels from each pixel
                                             // => y (column) is between -1 and 1
                {
                    int currentX = i + x;
                    int currentY = j + y;

                    // Check if the neighbour pixels are valid
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 ||
                        currentY >
                            (width -
                             1)) // conditions for invalid pixels: when we reach image borders
                    {
                        continue; // skip and loop through other pixels
                    }

                    // Sum valid neighbor pixels - sums each color from all neighbour pixels (from
                    // the original image)
                    totalRed += image[currentX][currentY].rgbtRed;
                    totalGreen += image[currentX][currentY].rgbtGreen;
                    totalBlue += image[currentX][currentY].rgbtBlue;

                    number_pixels++; // add 1 for each neighbour pixel
                }

                // Get average of each color from neighbour pixels and changes the copy of the image
                // getting pixels from the original
                copy[i][j].rgbtRed = round(totalRed / number_pixels);
                copy[i][j].rgbtGreen = round(totalGreen / number_pixels);
                copy[i][j].rgbtBlue = round(totalBlue / number_pixels);
            }
        }
    }

    // Copy new values of pixels into image
    for (int i = 0; i < height; i++) // go through original image - rows
    {
        for (int j = 0; j < width; j++) // columns
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
    return; // finishes the function
}
