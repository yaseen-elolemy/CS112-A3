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
        image_name.clear();
        cout<<"Pls enter the name of the image you want to edit or(exit): ";
        cin>>image_name_before;
        if(image_name!= "exit" )
        {
            Image image(image_name_before);




            cout<<"Enter the new name of the photo you want ";
            cout<<"and the format .jpg, .bmp, .png, .tga:";
            cin>>image_name;
            // when we activate the filters
            // we can here make a choice to the user if he wants to save the new photo with the same name and same file or new file with new name

           return 0;
        }

    }

}
