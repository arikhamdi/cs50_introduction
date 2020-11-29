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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // For each pixel
    // compute Gx and Gy for each channel of red, green, and blue
    // for pixels at the border, treat any pixel past the border as having all 0 values
    // Compute each new channel value as the square root of Gx² + Gy²
    RGBTRIPLE tmp[height][width];


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GxRed = 0;
            int GxGreen = 0;
            int GxBlue = 0;
            int GyRed = 0;
            int GyGreen = 0;
            int GyBlue = 0;

            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                sumRed += - 1 * image[i - 1][j - 1].rgbtRed;
                sumGreen += - 1 * image[i - 1][j - 1].rgbtGreen;
                sumBlue += - 1 * image[i - 1][j - 1].rgbtBlue;
            }
            if (i - 1 >= 0)
            {
                GyRed += - 2 * image[i - 1][j].rgbtRed;
                GyGreen += - 2 * image[i - 1][j].rgbtGreen;
                GyBlue += - 2 * image[i - 1][j].rgbtBlue;
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                GxRed += 1 * image[i - 1][j + 1].rgbtRed;
                GxGreen += 1 * image[i - 1][j + 1].rgbtGreen;
                GxBlue += 1 * image[i - 1][j + 1].rgbtBlue;

                GyRed += - 1 * image[i - 1][j + 1].rgbtRed;
                GyGreen += - 1 * image[i - 1][j + 1].rgbtGreen;
                GyBlue += - 1 * image[i - 1][j + 1].rgbtBlue;
            }
            if (j - 1 >= 0)
            {
                GxRed += - 2 * image[i][j - 1].rgbtRed;
                GxGreen += - 2 * image[i][j - 1].rgbtGreen;
                GxBlue += - 2 * image[i][j - 1].rgbtBlue;
            }
            if (j + 1 < width)
            {
                GxRed += 2 * image[i][j + 1].rgbtRed;
                GxGreen += 2 * image[i][j + 1].rgbtGreen;
                GxBlue += 2 * image[i][j + 1].rgbtBlue;
            }
            if (i + 1 < height && j - 1 >= 0)
            {
                GxRed += - 1 * image[i + 1][j - 1].rgbtRed;
                GxGreen += - 1 * image[i + 1][j - 1].rgbtGreen;
                GxBlue += - 1 * image[i + 1][j - 1].rgbtBlue;

                GyRed += 1 * image[i + 1][j - 1].rgbtRed;
                GyGreen += 1 * image[i + 1][j - 1].rgbtGreen;
                GyBlue += 1 * image[i + 1][j - 1].rgbtBlue;
            }
            if (i + 1 < height)
            {
                GyRed += 2 * image[i + 1][j].rgbtRed;
                GyGreen += 2 * image[i + 1][j].rgbtGreen;
                GyBlue += 2 * image[i + 1][j].rgbtBlue;
            }
            if (i + 1 < height && j + 1 < width)
            {
                sumRed += 1 * image[i + 1][j + 1].rgbtRed;
                sumGreen += 1 * image[i + 1][j + 1].rgbtGreen;
                sumBlue += 1 * image[i + 1][j + 1].rgbtBlue;
            }

            GxRed += sumRed;
            GxGreen += sumGreen;
            GxBlue += sumBlue;

            GyRed += sumRed;
            GyGreen += sumGreen;
            GyBlue += sumBlue;

            float gRed = sqrt((GxRed * GxRed) + (GyRed * GyRed));
            float gGreen = sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen));
            float gBlue = sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue));

            if (gRed > 255)
            {
                tmp[i][j].rgbtRed = 255;
            }
            else
            {
                tmp[i][j].rgbtRed = round(gRed);
            }

            if (gGreen > 255)
            {
                tmp[i][j].rgbtGreen = 255;
            }
            else
            {
                tmp[i][j].rgbtGreen = round(gGreen);
            }

            if (gBlue > 255)
            {
                tmp[i][j].rgbtBlue = 255;
            }
            else
            {
                tmp[i][j].rgbtBlue = round(gBlue);
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
