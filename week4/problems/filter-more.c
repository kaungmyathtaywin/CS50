#include "helpers.h"
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

            // Check if start and end points go out of index
            if (hstart < 0) hstart = 0;
            if (hend > height - 1) hend = hend - 1;
            if (wstart < 0) wstart = 0;
            if (wend > width - 1) wend = wend - 1; 

            float red = 0, green = 0, blue = 0;
            int count = 0;

            // Add surrounding pixels' red, green and blue values
            for (int k = hstart; k <= hend; k++)
            {
                for (int l = wstart; l <= wend; l++)
                {
                    red += copy[k][l].rgbtRed;
                    green += copy[k][l].rgbtGreen;
                    blue += copy[k][l].rgbtBlue;

                    count++;
                }
            }

            // Calculate average and assign the values
            image[i][j].rgbtRed = round(red / (float) count);
            image[i][j].rgbtGreen = round(green / (float) count);
            image[i][j].rgbtBlue = round(blue / (float) count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    #include "helpers.h"
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
    // Make copy of the original image
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

            // Check if surrounding pixels are out of index
            if (hstart < 0) hstart = 0;
            if (hend > height - 1) hend = hend - 1;
            if (wstart < 0) wstart = 0;
            if (wend > width - 1) wend = wend - 1; 

            float red = 0, green = 0, blue = 0;
            int count = 0;

            // Add surrounding pixels' red, green and blue values
            for (int k = hstart; k <= hend; k++)
            {
                for (int l = wstart; l <= wend; l++)
                {
                    red += copy[k][l].rgbtRed;
                    green += copy[k][l].rgbtGreen;
                    blue += copy[k][l].rgbtBlue;

                    count++;
                }
            }

            // Calculate average and assign the values
            image[i][j].rgbtRed = round(red / (float) count);
            image[i][j].rgbtGreen = round(green / (float) count);
            image[i][j].rgbtBlue = round(blue / (float) count);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    // Make copy of the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    // Gx and Gy kernels
    int gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Start and end indices of surrounding pixels
            int hstart = i - 1, hend = i + 1, wstart = j - 1, wend = j + 1;
            double x_red = 0, x_green = 0, x_blue = 0, y_red = 0, y_green = 0, y_blue = 0;

            for (int k = hstart, m = 0; k <= hend; k++)
            {
                for (int l = wstart, n = 0; l <= wend; l++)
                {
                    // Check if surrounding pixels are out of index
                    if (!((k < 0 || k > height - 1) || (l < 0 || l > width - 1)))
                    {
                        // Calculate gx for red, green and blue
                        x_red += copy[k][l].rgbtRed * gx[m][n];
                        x_green += copy[k][l].rgbtGreen * gx[m][n];
                        x_blue += copy[k][l].rgbtBlue * gx[m][n];

                        // Calculate gy for red, green and blue
                        y_red += copy[k][l].rgbtRed * gy[m][n];
                        y_green += copy[k][l].rgbtGreen * gy[m][n];
                        y_blue += copy[k][l].rgbtBlue * gy[m][n];
                    }
                    // Tracking index for gx and gy kernel
                    n++;
                }
                // Tracking index for gx and gy kernel
                m++;
            }

            int red, green, blue;

            // Combine both gx and gy for each channel
            red = (int) round(sqrt(pow(x_red, 2) + pow(y_red, 2)));
            green = (int) round(sqrt(pow(x_green, 2) + pow(y_green, 2)));
            blue = (int) round(sqrt(pow(x_blue, 2) + pow(y_blue, 2)));

            // If the combined value goes greater than 255, cap them at 255
            if (red > 255) red = 255;
            if (green > 255) green = 255;
            if (blue > 255) blue = 255;

            // Assign the calculated values
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
}