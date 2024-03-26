#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

void rotateImage(Image& image)     //By Yaseen El-Olemy: 20230468
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

    }

}

void invertImage(Image& image)     //By Yaseen El-Olemy: 20230468
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
void merge_images (Image& image1)
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

    // Scale and copy the pixel data from the first image into the new image
    for (int i = 0; i < newWidth; ++i)
    {
        for (int j = 0; j < newHeight; ++j)
        {
            for (int k = 0; k < image1.channels; ++k)
            {
                // Calculate the corresponding coordinates in the original image
                int oldX = i * image1.width / newWidth;
                int oldY = j * image1.height / newHeight;

                // Copy the pixel data
                newImage(i, j, k) = image1(oldX, oldY, k);
            }
        }
    }

    // Scale and copy the pixel data from the second image into the new image
    for (int i = 0; i < newWidth; ++i)
    {
        for (int j = 0; j < newHeight; ++j)
        {
            for (int k = 0; k < image2.channels; ++k)
            {
                // Calculate the corresponding coordinates in the original image
                int oldX = i * image2.width / newWidth;
                int oldY = j * image2.height / newHeight;

                // Average the pixel values of the two images
                newImage(i, j, k) = (newImage(i, j, k) + image2(oldX, oldY, k)) / 2;
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
    string image_name_before, image_name_after;
    cout<<"Welcome to Editing Photo Program"<<endl;
    while(true)
    {
        int choice,choice2;
        cout<<"1) Gray Scale filer\n2) Black and White filter\n3) Invert Image\n4) Merge two images\n";
        cout<<"5) Rotate Image\n6) Exit\n";
        cout<<"PLs choose the filter you want:";
        cin>>choice;
        while (choice > 6)
        {
            cout<<"Pls enter a valid choice: ";
            cin>>choice;
        }
        if (choice == 6)
        {
            cout<<"Thanks for using our program!";
            exit(0);
        }
        cout<<"Pls enter the name of the image you want to edit:";
        cin>>image_name_before;
        Image image(image_name_before);
        if (choice == 1)
        {
            cout<<"1) Save image in an existing file\n2) Save the image in new file"<<endl;
            cout<<"Pls enter your choice:";
            cin>>choice2;
            while (choice2 > 2)
            {
                cout<<"PLs enter a valid choice: ";
                cin>>choice2;
            }
            if (choice2 == 1)
            {
                grayscale(image);
                if(image.saveImage(image_name_before))
                    cout<<"The image was loaded successfully"<<endl;
            }
            else if (choice2 == 2)
            {

                cout<<"Enter the new directory or the name of the photo you want ";
                cout<<"with the format .jpg, .bmp, .png, .tga:";
                cin >> image_name_after;
                grayscale(image);
                if(image.saveImage(image_name_after))
                {
                    cout<<"The image was loaded successfully"<<endl;
                }

            }
        }
        else if (choice == 2 )
        {
            cout<<"1) Save image in an existing file\n2) Save the image in new file"<<endl;
            cout<<"Pls enter your choice:";
            cin>>choice2;
            while (choice2 > 2)
            {
                cout<<"PLs enter a valid choice: ";
                cin>>choice2;
            }
            if (choice2 == 1)
            {
                convertToBlackandWhite(image);
                if(image.saveImage(image_name_before))
                    cout<<"The image was loaded successfully"<<endl;
            }
            else if (choice2 == 2)
            {

                cout<<"Enter the new directory or the name of the photo you want ";
                cout<<"with the format .jpg, .bmp, .png, .tga:";
                cin >> image_name_after;
                convertToBlackandWhite(image);
                if(image.saveImage(image_name_after))
                {
                    cout<<"The image was loaded successfully"<<endl;
                }

            }
        }
        else if (choice == 3)
        {
            cout<<"1) Save image in an existing file\n2) Save the image in new file"<<endl;
            cout<<"Pls enter your choice:";
            cin>>choice2;
            while (choice2 > 2)
            {
                cout<<"PLs enter a valid choice: ";
                cin>>choice2;
            }
            if (choice2 == 1)
            {
                invertImage(image);
                if(image.saveImage(image_name_before))
                    cout<<"The image was loaded successfully"<<endl;
            }
            else if (choice2 == 2)
            {

                cout<<"Enter the new directory or the name of the photo you want ";
                cout<<"with the format .jpg, .bmp, .png, .tga:";
                cin >> image_name_after;
                invertImage(image);
                if(image.saveImage(image_name_after))
                {
                    cout<<"The image was loaded successfully"<<endl;
                }

            }
        }
        else if (choice == 4)
        {

            merge_images(image);
            cout<<"Enter the new directory or the name of the photo you want ";
            cout<<"with the format .jpg, .bmp, .png, .tga:";
            cin >> image_name_after;
            if(image.saveImage(image_name_after))
            {
                cout<<"The image was loaded successfully"<<endl;
            }

        }
        else if (choice == 5)
        {
            cout<<"1) Save image in an existing file\n2) Save the image in new file"<<endl;
            cout<<"Pls enter your choice:";
            cin>>choice2;
            while (choice2 > 2)
            {
                cout<<"PLs enter a valid choice: ";
                cin>>choice2;
            }
            if (choice2 == 1)
            {
                rotateImage(image);
                if(image.saveImage(image_name_before))
                    cout<<"The image was loaded successfully"<<endl;
            }
            else if (choice2 == 2)
            {

                cout<<"Enter the new directory or the name of the photo you want ";
                cout<<"with the format .jpg, .bmp, .png, .tga:";
                cin >> image_name_after;
                rotateImage(image);
                if(image.saveImage(image_name_after))
                {
                    cout<<"The image was loaded successfully"<<endl;
                }
            }
        }
    }
}
