#include "helper.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Find the average of red, blue and green
            avg = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int val = roundf(avg);
            //Assign the average to each colour in each pixel
            image[i][j].rgbtBlue = val;
            image[i][j].rgbtGreen = val;
            image[i][j].rgbtRed = val;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        //Only loop width/2 times, since looping width times makes no diff
        for (int j = 0; j < (width / 2); j++)
        {
            //Swap the leftmost pixels with the rightmost
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a copy of the image so that the original is preserved
    RGBTRIPLE image1[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Array for middle pixels
            RGBTRIPLE temp[3][3];
            //Array for corner pixels
            RGBTRIPLE temp1[2][2];
            //Array for edge pixels
            RGBTRIPLE temp2[2][3];
            RGBTRIPLE temp3[3][2];

            //Create variables for each colour
            int sum_red = 0;
            int sum_blue = 0;
            int sum_green = 0;

            //For middle pixels
            if (i != 0 && j != 0 && i != height - 1 && j != width - 1)
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int l = 0; l < 3; l++)
                    {
                        //Create 3x3 array of surrounding 9 pixels
                        temp[k][l] = image1[i + k - 1][j - 1 + l];

                        //Find the sum of the nine pixels for each colour
                        sum_red += temp[k][l].rgbtRed;
                        sum_blue += temp[k][l].rgbtBlue;
                        sum_green += temp[k][l].rgbtGreen;
                    }
                }
                //Assign
                image[i][j].rgbtRed = roundf(sum_red / 9.0);
                image[i][j].rgbtBlue = roundf(sum_blue / 9.0);
                image[i][j].rgbtGreen = roundf(sum_green / 9.0);
            }
            else
            {
                //For upper left corner pixel
                if (i == 0 && j == 0)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            //Create 2x2 array for corner pixel
                            temp1[k][l] = image1[k][l];
                            sum_red += temp1[k][l].rgbtRed;
                            sum_blue += temp1[k][l].rgbtBlue;
                            sum_green += temp1[k][l].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = roundf(sum_red / 4.0);
                    image[i][j].rgbtBlue = roundf(sum_blue / 4.0);
                    image[i][j].rgbtGreen = roundf(sum_green / 4.0);
                }
                //For upper right corner pixel
                else if (i == 0 && j == width - 1)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            //Create 2x2 array for corner pixel
                            temp1[k][l] = image1[k][j - 1 + l];
                            sum_red += temp1[k][l].rgbtRed;
                            sum_blue += temp1[k][l].rgbtBlue;
                            sum_green += temp1[k][l].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = roundf(sum_red / 4.0);
                    image[i][j].rgbtBlue = roundf(sum_blue / 4.0);
                    image[i][j].rgbtGreen = roundf(sum_green / 4.0);
                }
                //For bottom left pixel
                else if (i == height - 1 && j == 0)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            temp1[k][l] = image1[i - 1 + k][l];
                            sum_red += temp1[k][l].rgbtRed;
                            sum_blue += temp1[k][l].rgbtBlue;
                            sum_green += temp1[k][l].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = roundf(sum_red / 4.0);
                    image[i][j].rgbtBlue = roundf(sum_blue / 4.0);
                    image[i][j].rgbtGreen = roundf(sum_green / 4.0);
                }
                //For bottom right pixel
                else if (i == height - 1 && j == width - 1)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            temp1[k][l] = image1[i - 1 + k][j - 1 + l];
                            sum_red += temp1[k][l].rgbtRed;
                            sum_blue += temp1[k][l].rgbtBlue;
                            sum_green += temp1[k][l].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = roundf(sum_red / 4.0);
                    image[i][j].rgbtBlue = roundf(sum_blue / 4.0);
                    image[i][j].rgbtGreen = roundf(sum_green / 4.0);
                }
                //For bottom edge pixels
                else if (i == height - 1 && j != 0 && j != width - 1)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = 0; l < 3; l++)
                        {
                            temp2[k][l] = image1[i - 1 + k][j - 1 + l];
                            sum_red += temp2[k][l].rgbtRed;
                            sum_blue += temp2[k][l].rgbtBlue;
                            sum_green += temp2[k][l].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = roundf(sum_red / 6.0);
                    image[i][j].rgbtBlue = roundf(sum_blue / 6.0);
                    image[i][j].rgbtGreen = roundf(sum_green / 6.0);
                }
                //For top edge pixels
                else if (i == 0 && j != 0 && j != width - 1)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int l = 0; l < 3; l++)
                        {
                            temp2[k][l] = image1[i + k][j - 1 + l];
                            sum_red += temp2[k][l].rgbtRed;
                            sum_blue += temp2[k][l].rgbtBlue;
                            sum_green += temp2[k][l].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = roundf(sum_red / 6.0);
                    image[i][j].rgbtBlue = roundf(sum_blue / 6.0);
                    image[i][j].rgbtGreen = roundf(sum_green / 6.0);
                }
                //For leftmost pixels
                else if (i != 0 && j == 0 && i != height - 1)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            temp3[k][l] = image1[i - 1 + k][j + l];
                            sum_red += temp3[k][l].rgbtRed;
                            sum_blue += temp3[k][l].rgbtBlue;
                            sum_green += temp3[k][l].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = roundf(sum_red / 6.0);
                    image[i][j].rgbtBlue = roundf(sum_blue / 6.0);
                    image[i][j].rgbtGreen = roundf(sum_green / 6.0);
                }
                //For rightmost pixels
                else if (i != 0 && j == width - 1 && i != height - 1)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        for (int l = 0; l < 2; l++)
                        {
                            temp3[k][l] = image1[i - 1 + k][j - 1 + l];
                            sum_red += temp3[k][l].rgbtRed;
                            sum_blue += temp3[k][l].rgbtBlue;
                            sum_green += temp3[k][l].rgbtGreen;
                        }
                    }
                    image[i][j].rgbtRed = roundf(sum_red / 6.0);
                    image[i][j].rgbtBlue = roundf(sum_blue / 6.0);
                    image[i][j].rgbtGreen = roundf(sum_green / 6.0);
                }
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a copy of the image so that it is preserved
    RGBTRIPLE image1[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image1[i][j] = image[i][j];
        }
    }
    //Gx and Gy kernels
    int gx[3][3] = { {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };
    int gy[3][3] = { {-1, -2, -1}, {0, 0, 0}, {1, 2, 1} };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE temp[3][3];
            int sum_red_x = 0;
            int sum_red_y = 0;
            int sum_blue_x = 0;
            int sum_blue_y = 0;
            int sum_green_x = 0;
            int sum_green_y = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int m = i - 1 + k;
                    int n = j - 1 + l;
                    //For pixels out of bounds
                    if (m < 0 || n < 0 || m > (height - 1) || n > (width - 1))
                    {
                        //Assign out of bound pixels black
                        temp[k][l].rgbtRed = 0;
                        temp[k][l].rgbtBlue = 0;
                        temp[k][l].rgbtGreen = 0;
                    }
                    //For middle pixels
                    else
                    {
                        temp[k][l] = image1[m][n];
                    }
                    sum_red_x += (temp[k][l].rgbtRed * gx[k][l]);
                    sum_red_y += (temp[k][l].rgbtRed * gy[k][l]);
                    sum_blue_x += (temp[k][l].rgbtBlue * gx[k][l]);
                    sum_blue_y += (temp[k][l].rgbtBlue * gy[k][l]);
                    sum_green_x += (temp[k][l].rgbtGreen * gx[k][l]);
                    sum_green_y += (temp[k][l].rgbtGreen * gy[k][l]);
                }
            }
            //Round to nearest whole number
            int red = roundf(sqrtf((sum_red_x * sum_red_x) + (sum_red_y * sum_red_y)));
            int blue = roundf(sqrtf((sum_blue_x * sum_blue_x) + (sum_blue_y * sum_blue_y)));
            int green = roundf(sqrtf((sum_green_x * sum_green_x) + (sum_green_y * sum_green_y)));

            //Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;
        }
    }
    return;
}

