#include <bits/stdc++.h>
#include "Image_Class.h"

using namespace std;

void rotateImage(Image& image, string saveName)     //By Yaseen El-Olemy: 20230468
{
    int toRotate;       //placeholder to specify
    cout<<"to rotate 90 Degrees Clockwise[1]\nto rotate 180 Degrees[2]\nto rotate 270 Degrees Clockwise[3]\n-> ";
    cin>>toRotate;

    if(toRotate == 1)
    {

        Image ninetied(image.height, image.width);
        for(int i = image.width -1 ; i>=0; --i)
        {
            for(int j = image.height -1; j>=0; --j)
            {
                for(int k = 0; k < image.channels; ++k)
                {
                    ninetied(j , i ,k) = image(i, j, k);
                }
            }
        }
        Image inverted(ninetied.width, ninetied.height);
        for(int i = 0; i < ninetied.width; ++i)
        {
            for(int j = 0; j < ninetied.height; ++j)
            {
                for(int k = 0; k < ninetied.channels; ++k)
                {
                    inverted(i, j, k) = ninetied((ninetied.width -1) - i,(ninetied.height-1) - j,k);
                }
            }
        }

        inverted.saveImage(saveName);
    }

    if(toRotate == 2)
    {
        Image inverted(image.width, image.height);
        for(int i = 0; i < image.width; ++i)
        {
            for(int j = 0; j < image.height; ++j)
            {
                for(int k = 0; k < image.channels; ++k)
                {
                    inverted(i, j, k) = image((image.width -1) - i,(image.height-1) - j,k);
                }
            }
        }
        inverted.saveImage(saveName);
    }

    if(toRotate == 3)
    {
        Image ninetied(image.height, image.width);
        for(int i = image.width -1 ; i>=0; --i)
        {
            for(int j = image.height -1; j>=0; --j)
            {
                for(int k = 0; k < image.channels; ++k)
                {
                    ninetied(j , i ,k) = image(i, j, k);
                }
            }
        }

        ninetied.saveImage(saveName);
    }

}

void invertImage(Image& image, string saveName)     //By Yaseen El-Olemy: 20230468
{
    for(int i =0; i < image.width; ++i)
    {
        for(int j = 0; j < image.height; ++j)
        {
            for(int k =0; k<image.channels; ++k)
            {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
    image.saveImage(saveName);
}
void grayscale(Image& image)
{
    for(int i = 0; i<image.width;i++)
    {
        for(int j = 0; j<image.height;j++)
        {
            unsigned int avg = 0;
            // accumulate the pixels value
            for(int k = 0; k<image.channels;k++)
            {
                avg += image(i,j,k);
            }
            // calculate the average
            avg/= 3;
            for(int k = 0;k<3;k++)
            {
                // changing all the colors to the average
                image.setPixel(i,j,k,avg);
            }

        }
    }
}
/*
 *needs to be modified and add the resize function to it to resize both images before merging them

void merge_images (Image& image1, string saveName)
{
    // Prompt the user for the name of the second image
    string image2Name;
    cout << "Please enter the directory of the second image: ";
    cin >> image2Name;

    // Load the second image
    Image image2(image2Name);

    // Determine the dimensions of the new image
    int newWidth = max(image1.width, image2.width);
    int newHeight = max(image1.height, image2.height);

    // Create the new image with the larger dimensions
    Image newImage(newWidth, newHeight);

    // Copy the pixel data from the first image into the new image
    for (int i = 0; i < image1.width; ++i)
    {
        for (int j = 0; j < image1.height; ++j)
        {
            for (int k = 0; k < image1.channels; ++k)
            {
                newImage(i, j, k) = image1(i, j, k);
            }
        }
    }

    // Calculate the starting position for the second image in the new image
    int startX = (newWidth - image2.width) / 2;
    int startY = (newHeight - image2.height) / 2;

    // Copy the pixel data from the second image into the new image
    for (int i = 0; i < image2.width; ++i)
    {
        for (int j = 0; j < image2.height; ++j)
        {
            for (int k = 0; k < image2.channels; ++k)
            {
                // Calculate the coordinates in the new image
                int newX = startX + i;
                int newY = startY + j;

                // Check if the coordinates are within the bounds of the new image
                if (newX >= 0 && newX < newWidth && newY >= 0 && newY < newHeight)
                {
                    // Average the pixel values of the two images
                    newImage(newX, newY, k) = (newImage(newX, newY, k) + image2(i, j, k)) / 2;
                }
            }
        }
    }

    // Save the new image
    newImage.saveImage(saveName);
}
*/

void darken_and_lighten(Image& image)
{
    string choice;
    cout<<"Do you want to darken or lighten the image? (darken/lighten): ";
    cin>>choice;
    bool darken = (choice == "darken");

    for(int i = 0; i<image.width;i++)
    {
        for(int j = 0; j<image.height;j++)
        {
            for(int k = 0;k<3;k++)
            {
                // Get the current color value
                unsigned int color = image(i,j,k);
                if(darken)
                {
                    // Reduce the color value by 50% to darken the image
                    image.setPixel(i,j,k,color/2);
                }
                else
                {
                    // Increase the color value by 50% to lighten the image, but not exceeding 255
                    image.setPixel(i,j,k,min(color + color/2, (unsigned int)255));
                }
            }
        }
    }
}

void detect_edges(Image& image)
{
    for(int i = 0; i<image.width;i++)
    {
        for(int j = 0; j<image.height;j++)
        {
            for(int k = 0;k<3;k++)
            {
                // Get the current color value
                unsigned int color = image(i,j,k);
                // Get the color value of the pixel to the right
                unsigned int right = image(i+1,j,k);
                // Get the color value of the pixel below
                unsigned int below = image(i,j+1,k);
                // Calculate the difference between the current pixel and the pixel to the right
                int diff1 = abs((int)color - (int)right);
                // Calculate the difference between the current pixel and the pixel below
                int diff2 = abs((int)color - (int)below);
                // Set the pixel to black if the difference is greater than 50, otherwise set it to white
                image.setPixel(i,j,k,(diff1 > 50 || diff2 > 50) ? 0 : 255);
            }
        }
    }
}

void convertToBlackandWhite(Image& image)
{
    for(int i = 0; i<image.width;i++)
    {
        for(int j = 0; j<image.height;j++)
        {
            unsigned int avg = 0;
            // accumulate the pixels value
            for(int k = 0; k<image.channels;k++)
            {
                avg += image(i,j,k);
            }
            // calculate the average
            avg/= 3;
            for(int k = 0;k<3;k++)
            {
                // checking the brightness of each pixel to see if we will change the color to black or white
                if(avg < 128)
                {
                    // changing all the colors to black
                    image.setPixel(i,j,k,0);
                }
                else
                {
                    // changing all the colors to white
                    image.setPixel(i,j,k,255);

                }
            }

        }
    }
}

int main()
{
    string image_name_before, image_name;
    cout<<"Welcome to Editing Photo Program"<<endl;
    while(image_name_before != "exit")
    {

        /*
             cout<<"PLs choose the filter you want: ";
             here we will insert the filters because
             there's a filter that requires two images so the user must choose the filter he wants to apply first

             */

        image_name.clear();
        cout<<"Pls enter the directory of the image you want to edit (or exit): ";
        cin>>image_name_before;
        if(image_name!= "exit" )
        {
            Image image(image_name_before);



            cout<<"Enter the new directory and name of the photo you want ";
            cout<<"with the format .jpg, .bmp, .png, .tga:";
            cin>>image_name;
            // when we activate the filters
            // we can here make a choice to the user if he wants to save the new photo with the same name and same file or new file with new name

        }

    }
    return 0;

}