#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // checking for black pixel in img
            if (image[i][j].rgbtBlue == 0  &&  image[i][j].rgbtGreen == 0  &&  image[i][j].rgbtRed == 0)
            {
                // coloring the black pixel into any color we want by using their RGB values
                image[i][j].rgbtBlue = 0;
                image[i][j].rgbtRed = 255;
                image[i][j].rgbtGreen = 50;
            }
        }
    }
}