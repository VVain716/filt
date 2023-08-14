#include "helpers.h"
#include "math.h"
#include "stdio.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int buffer = round((image[i][j].rgbtGreen + image[i][j].rgbtBlue + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtGreen = buffer;
            image[i][j].rgbtRed = buffer;
            image[i][j].rgbtBlue = buffer;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int buffer = 255;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed =  round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            int sepiaGreen =  round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            if (sepiaRed > buffer)
            {
                sepiaRed = buffer;
            }
            if (sepiaBlue > buffer)
            {
                sepiaBlue = buffer;
            }
            if (sepiaGreen > buffer)
            {
                sepiaGreen = buffer;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (float)width / (float)2 ; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float green;
    float blue;
    float red;
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                red = (original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) /
                      4.0;
                blue = (original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) /
                       4.0;
                green = (original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j +
                         1].rgbtGreen) / 4.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);
            }
            else if (i == 0 && j == width - 1)
            {
                red = (original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed) / 4.0;
                blue = (original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue) /
                       4.0;
                green = (original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i + 1][j -
                         1].rgbtGreen) / 4.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);
            }
            else if (i == height - 1 && j == 0)
            {

                red = (original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed) / 4.0;
                blue = (original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue) /
                       4.0;
                green = (original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j +
                         1].rgbtGreen) / 4.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);
            }
            else if (i == height - 1 && j == width - 1)
            {

                red = (original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j - 1].rgbtRed) / 4.0;
                blue = (original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue) /
                       4.0;
                green = (original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j -
                         1].rgbtGreen) / 4.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);
            }
            else if (i == 0)
            {
                red = (original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j - 1].rgbtRed +
                       original[i + 1][j].rgbtRed + original[i + 1][j + 1].rgbtRed) / 6.0;
                blue = (original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue +
                        original[i + 1][j].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / 6.0;
                green = (original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen +
                         original[i + 1][j].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / 6.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);

            }
            else if (i == height - 1)
            {
                red = (original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j - 1].rgbtRed +
                       original[i - 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed) / 6.0;
                blue = (original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue +
                        original[i - 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue) / 6.0;
                green = (original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen +
                         original[i - 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen) / 6.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);
            }
            else if (j == 0)
            {
                red = (original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j].rgbtRed +
                       original[i][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) / 6.0;
                blue = (original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j + 1].rgbtBlue +
                        original[i - 1][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) / 6.0;
                green = (original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j + 1].rgbtGreen +
                         original[i - 1][j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen) / 6.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);
            }
            else if (j == height - 1)
            {
                red = (original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed +
                       original[i - 1][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed) / 6.0;
                blue = (original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue +
                        original[i - 1][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue) / 6.0;
                green = (original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen +
                         original[i - 1][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen) / 6.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);
            }
            else
            {
                red = (original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i + 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed +
                       original[i][j - 1].rgbtRed +
                       original[i + 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed + original[i][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed) /
                      9.0;
                blue = (original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue +
                        original[i][j - 1].rgbtBlue +
                        original[i + 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue + original[i][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue) /
                       9.0;
                green = (original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen +
                         original[i][j - 1].rgbtGreen +
                         original[i + 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen + original[i][j + 1].rgbtGreen + original[i + 1][j +
                                 1].rgbtGreen) / 9.0;
                image[i][j].rgbtRed = round(red);
                image[i][j].rgbtBlue = round(blue);
                image[i][j].rgbtGreen = round(green);
            }
        }
    }
    return;
}
