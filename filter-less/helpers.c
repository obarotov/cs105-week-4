#include <math.h>

#include "helpers.h"

static int cap(double value)
{
    int result = (int) round(value);
    return result > 255 ? 255 : result;
}

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            int average = (int) round(sum / 3.0);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
}

void blur(int height, int width, RGBTRIPLE image[height][width])
{
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
            int red = 0;
            int green = 0;
            int blue = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni < 0 || ni >= height || nj < 0 || nj >= width)
                    {
                        continue;
                    }
                    red += original[ni][nj].rgbtRed;
                    green += original[ni][nj].rgbtGreen;
                    blue += original[ni][nj].rgbtBlue;
                    count++;
                }
            }

            image[i][j].rgbtRed = (int) round((double) red / count);
            image[i][j].rgbtGreen = (int) round((double) green / count);
            image[i][j].rgbtBlue = (int) round((double) blue / count);
        }
    }
}

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = cap(0.393 * red + 0.769 * green + 0.189 * blue);
            image[i][j].rgbtGreen = cap(0.349 * red + 0.686 * green + 0.168 * blue);
            image[i][j].rgbtBlue = cap(0.272 * red + 0.534 * green + 0.131 * blue);
        }
    }
}