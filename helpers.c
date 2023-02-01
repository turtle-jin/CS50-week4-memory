#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to turquoise
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE *pixel = &image[i][j];  //make sure use pointers so the variable is "global"
            if ((*pixel).rgbtBlue == 0x00 && (*pixel).rgbtGreen == 0x00 && (*pixel).rgbtRed == 0x00)
            {
                (*pixel).rgbtBlue = 0xD0;
                (*pixel).rgbtGreen = 0xE0;
                (*pixel).rgbtRed = 0x40;
            }
        }
    }
}
