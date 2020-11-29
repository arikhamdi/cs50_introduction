#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Make the average of the three color for each pixel
    // Ensure the result is an integer
    float avg;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel
    // Calculate each new color value using the Sepia formula
    // Ensure the result is an integer between 0 and 255, inclusive
    int sepiaRed;
    int sepiaGreen;
    int sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(image[i][j].rgbtRed * 0.393 + image[i][j].rgbtGreen * 0.769 + image[i][j].rgbtBlue * 0.189);
            sepiaGreen = round(image[i][j].rgbtRed * 0.349 + image[i][j].rgbtGreen * 0.686 + image[i][j].rgbtBlue * 0.168);
            sepiaBlue = round(image[i][j].rgbtRed * 0.272 + image[i][j].rgbtGreen * 0.534 + image[i][j].rgbtBlue * 0.131);

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else if (sepiaRed < 0)
            {
                image[i][j].rgbtRed = 0;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else if (sepiaGreen < 0)
            {
                image[i][j].rgbtGreen = 0;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else if (sepiaBlue < 0)
            {
                image[i][j].rgbtBlue = 0;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For every row
    // Swap pixels on horizontally opposite sides.
    RGBTRIPLE tmp[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[j] = image[i][j];
        }
        for (int k = 0; k < width; k++)
        {
            image[i][k] = tmp[width - (1 + k)];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    int sumRed, sumGreen, sumBlue;
    float cpt;

    for (int i = 0; i < height; i++)
    {


        for (int j = 0; j < width; j++)
        {
            cpt = 1.0;
            sumRed = image[i][j].rgbtRed;
            sumGreen = image[i][j].rgbtGreen;
            sumBlue = image[i][j].rgbtBlue;

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sumRed += image[i - 1][j - 1].rgbtRed;
                sumGreen += image[i - 1][j - 1].rgbtGreen;
                sumBlue += image[i - 1][j - 1].rgbtBlue;
                cpt++;
            }
            if (i - 1 >= 0)
            {
                sumRed += image[i - 1][j].rgbtRed;
                sumGreen += image[i - 1][j].rgbtGreen;
                sumBlue += image[i - 1][j].rgbtBlue;
                cpt++;
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                sumRed += image[i - 1][j + 1].rgbtRed;
                sumGreen += image[i - 1][j + 1].rgbtGreen;
                sumBlue += image[i - 1][j + 1].rgbtBlue;
                cpt++;
            }
            if (j - 1 >= 0)
            {
                sumRed += image[i][j - 1].rgbtRed;
                sumGreen += image[i][j - 1].rgbtGreen;
                sumBlue += image[i][j - 1].rgbtBlue;
                cpt++;
            }
            if (j + 1 < width)
            {
                sumRed += image[i][j + 1].rgbtRed;
                sumGreen += image[i][j + 1].rgbtGreen;
                sumBlue += image[i][j + 1].rgbtBlue;
                cpt++;
            }
            if (i + 1 < height && j - 1 >= 0)
            {
                sumRed += image[i + 1][j - 1].rgbtRed;
                sumGreen += image[i + 1][j - 1].rgbtGreen;
                sumBlue += image[i + 1][j - 1].rgbtBlue;
                cpt++;
            }
            if (i + 1 < height)
            {
                sumRed += image[i + 1][j].rgbtRed;
                sumGreen += image[i + 1][j].rgbtGreen;
                sumBlue += image[i + 1][j].rgbtBlue;
                cpt++;
            }
            if (i + 1 < height && j + 1 < width)
            {
                sumRed += image[i + 1][j + 1].rgbtRed;
                sumGreen += image[i + 1][j + 1].rgbtGreen;
                sumBlue += image[i + 1][j + 1].rgbtBlue;
                cpt++;
            }

            if (round(sumRed / cpt) > 255)
            {
                tmp[i][j].rgbtRed = 255;
            }
            else
            {
                tmp[i][j].rgbtRed = round(sumRed / cpt);
            }
            if (round(sumGreen / cpt) > 255)
            {
                tmp[i][j].rgbtGreen = 255;
            }
            else
            {
                tmp[i][j].rgbtGreen = round(sumGreen / cpt);
            }
            if (round(sumBlue / cpt) > 255)
            {
                tmp[i][j].rgbtBlue = 255;
            }
            else
            {
                tmp[i][j].rgbtBlue = round(sumBlue / cpt);
            }



        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
