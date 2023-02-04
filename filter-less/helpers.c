#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // find the average for grey
            float average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            // update pixels
            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtBlue = round(average);
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
            int ori_red = image[i][j].rgbtRed;
            int ori_green = image[i][j].rgbtGreen;
            int ori_blue = image[i][j].rgbtBlue;

            // converting each pixel to sepia
            float sepia_red = .393 * ori_red + .769 * ori_green + .189 * ori_blue;
            float sepia_green = .349 * ori_red + .686 * ori_green + .168 * ori_blue;
            float sepia_blue = .272 * ori_red + .534 * ori_green + .131 * ori_blue;

            // make sure all the values are capped at 255
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }

            // update pixels
            image[i][j].rgbtRed = round(sepia_red);
            image[i][j].rgbtGreen = round(sepia_green);
            image[i][j].rgbtBlue = round(sepia_blue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) //iterate through the midpoint of the array
        {
            // mirroring at midpoint, swap j with (width - j - 1)
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;

        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            float total_pixel_count = 0;
            float total_red = 0;
            float total_green = 0;
            float total_blue = 0;

            // create and loop through 3x3 grid
            for (int m = i - 1; m <= i + 1; m++)
            {
                for (int n = j - 1; n <= j + 1; n++)
                {
                    if (m >= 0 && m <= height - 1 && n >= 0 && n <= width - 1) //when pixel is within the grid range
                    {
                        total_pixel_count++;  // update the pixel count
                        total_red += image[m][n].rgbtRed;  // find the sum of each color
                        total_green += image[m][n].rgbtGreen;
                        total_blue += image[m][n].rgbtBlue;
                    }
                }
            }
            copy[i][j].rgbtRed = round((total_red / total_pixel_count));  // find the average, update new color to copy
            copy[i][j].rgbtGreen = round((total_green / total_pixel_count));
            copy[i][j].rgbtBlue = round((total_blue / total_pixel_count));
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];  // iterate and write the new color to image

        }
    }
}
