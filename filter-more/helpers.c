#include <math.h>

#include "helpers.h"

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

static int combine(int gx, int gy)
{
    int result = (int) round(sqrt((double) gx * gx + (double) gy * gy));
    return result > 255 ? 255 : result;
}

void edges(int height, int width, RGBTRIPLE image[height][width])
{
    const int kx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int ky[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

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
            int gxRed = 0, gxGreen = 0, gxBlue = 0;
            int gyRed = 0, gyGreen = 0, gyBlue = 0;

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
                    int wx = kx[di + 1][dj + 1];
                    int wy = ky[di + 1][dj + 1];
                    gxRed += wx * original[ni][nj].rgbtRed;
                    gxGreen += wx * original[ni][nj].rgbtGreen;
                    gxBlue += wx * original[ni][nj].rgbtBlue;
                    gyRed += wy * original[ni][nj].rgbtRed;
                    gyGreen += wy * original[ni][nj].rgbtGreen;
                    gyBlue += wy * original[ni][nj].rgbtBlue;
                }
            }

            image[i][j].rgbtRed = combine(gxRed, gyRed);
            image[i][j].rgbtGreen = combine(gxGreen, gyGreen);
            image[i][j].rgbtBlue = combine(gxBlue, gyBlue);
        }
    }
}