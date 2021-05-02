#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate average of red, green and blue values
            float average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            // Change type from unsigned integer to float because of multiplying with real numbers
            float sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            float sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            float sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

            // Cap the values at 255 if they are greater
            if (sepiaRed > 255) sepiaRed = 255;
            if (sepiaGreen > 255) sepiaGreen = 255;
            if (sepiaBlue > 255) sepiaBlue = 255;

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue; 
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Last index of the array
        int last = width - 1;

        // If the row has even number of elements
        // loop for half of the array
        if (width % 2 == 0)
        {
            for (int j = 0, n = width / 2; j < n; j++)
            {
                //Store the byte to swap temporarily
                RGBTRIPLE tmp = image[i][j];

                // Swap the two bytes horizontally
                image[i][j] = image[i][last - j];
                image[i][last - j] = tmp;
            }
        }
        // Else loop for one last than half of the array
        else 
        {
            for (int j = 0, n = floor(width / 2); j < n; j++)
            {
                //Store the byte to swap temporarily
                RGBTRIPLE tmp = image[i][j];

                // Swap the two bytes horizontally
                image[i][j] = image[i][last - j];
                image[i][last - j] = tmp;
            }
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    // Make copy of the image to not change the original pixel values 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    } 

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Start and end positions for height and width
            int hstart = i - 1, hend = i + 1, wstart = j - 1, wend = j + 1;

            
            float red = 0, green = 0, blue = 0;
            int count = 0;

            // Add surrounding pixels' red, green and blue values
            for (int k = hstart; k <= hend; k++)
            {
                for (int l = wstart; l <= wend; l++)
                {
                    // Check if start and end points go out of index
                    if (!((k < 0 || k > height - 1) || (l < 0 || l > width - 1)))
                    {
                        red += copy[k][l].rgbtRed;
                        green += copy[k][l].rgbtGreen;
                        blue += copy[k][l].rgbtBlue;

                        count++;
                    }
                }
            }

            // Calculate average and assign the values
            image[i][j].rgbtRed = round(red / (float) count);
            image[i][j].rgbtGreen = round(green / (float) count);
            image[i][j].rgbtBlue = round(blue / (float) count);
        }
    }
}