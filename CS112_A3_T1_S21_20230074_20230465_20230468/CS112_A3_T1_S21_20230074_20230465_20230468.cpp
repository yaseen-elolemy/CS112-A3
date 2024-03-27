/*
 File: CS112_A3_T1_S21_20230074_20230465_20230468.cpp

Purpose: This is a program that allows the user to load an image, apply filters to it, and save the edited image.
                 The filters are: rotate, invert, convert to grayscale, darken or lighten, and convert to black and white.
                The user can choose to load a new image, apply a filter to the current image, save the current image, or exit the program.

 Author:    Eyad Tamer Naguib 20230074 - S21 -> Grayscale and Darken/Lighten Functions
            Yassin Ahmed Ali 20230465 - S21 -> Flipping the image and Convert to Black and White Function
            Yaseen Mohamed Kamal 20230468 - S21  ->  Invert the color Functions

 Emails: eyadmohandiss@gmail.com - yassinsawy@outlook.com - yaseen.elolemy@gmail.com

 */

#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

void flipImage(Image& image) {  //By Yassin Ahmed Ali: 20230465
    int flipOption;
    cout << "Please choose a flip option:" << endl;
    cout << "1. Flip the image horizontally" << endl;
    cout << "2. Flip the image vertically" << endl;

    // Loop until a valid input is given
    while (!(cin >> flipOption) || (flipOption < 1 || flipOption > 2)) {
        cout << "Invalid option. Please try again." << endl;
        // Clear the error flags
        cin.clear();
        // Ignore the rest of the line
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    switch (flipOption) {
        case 1: // Flip horizontally
            for (int i = 0; i < image.width / 2; ++i) {
                for (int j = 0; j < image.height; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        // Swap pixels horizontally
                        int temp = image.getPixel(i, j, k);
                        image.setPixel(i, j, k, image.getPixel(image.width - i - 1, j, k));
                        image.setPixel(image.width - i - 1, j, k, temp);
                    }
                }
            }
            break;
        case 2: // Flip vertically
            for (int i = 0; i < image.width; ++i) {
                for (int j = 0; j < image.height / 2; ++j) {
                    for (int k = 0; k < image.channels; ++k) {
                        // Swap pixels vertically
                        int temp = image.getPixel(i, j, k);
                        image.setPixel(i, j, k, image.getPixel(i, image.height - j - 1, k));
                        image.setPixel(i, image.height - j - 1, k, temp);
                    }
                }
            }
            break;
    }
}

void invertImageColor(Image& image)     //By Yaseen El-Olemy: 20230468
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

void grayscale(Image& image) //By Eyad Tamer Naguib: 20230074
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

void darken_and_lighten(Image& image) //By Eyad Tamer Naguib: 20230074
{
    string choice;
    cout << "Do you want to darken or lighten the image? (darken/lighten): ";
    cin >> choice;
    // Convert the input to lowercase
    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
// Loop until a valid input is given
    while (choice != "darken" && choice != "lighten")
    {
        cout << "Invalid option. Please try again." << endl;
        cin >> choice;
        // Convert the input to lowercase
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
    }

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

void convertToBlackandWhite(Image& image) //By Yassin Ahmed Ali: 20230465
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
    string image_name;
    // Initialize image pointer to null
    Image* image = nullptr;

    cout << "Welcome to Editing Photo Program" << endl;
// Loop forever until user exits
    while (true)
    {
        cout<<"What would you like to do?"<<endl;
        cout << "1. Load a new image" << endl;
        cout << "2. Apply a filter to the current image" << endl;
        cout << "3. Save the current image" << endl;
        cout << "4. Exit" << endl;
        cout << "Please choose an option:" << endl;

        int option;
        // Loop until a valid input is given
        while (!(cin >> option) || (option < 1 || option > 4))
        {
            cout << "Invalid option. Please try again." << endl;
            // Clear the error flags
            cin.clear();
            // Ignore the rest of the line
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (option)
        {
            // Load a new image
            case 1:
            {
                // If there is a current image
                if (image != nullptr)
                {
                    cout << "Do you want to save the current image before loading a new one? (yes/no): ";
                    string saveCurrent;
                    cin >> saveCurrent;
                    // Convert the input to lowercase
                    transform(saveCurrent.begin(), saveCurrent.end(), saveCurrent.begin(), ::tolower);
                    // Loop until a valid input is given
                    while (saveCurrent != "yes" && saveCurrent != "no")
                    {
                        cout << "Invalid option. Please try again." << endl;
                        cin >> saveCurrent;
                        // Convert the input to lowercase
                        transform(saveCurrent.begin(), saveCurrent.end(), saveCurrent.begin(), ::tolower);
                    }

                    if (saveCurrent == "yes")
                    {
                        cout << "Enter the directory and name of the photo you want to save with the format .jpg, .bmp, .png, .tga: ";
                        cin >> image_name;
                        image->saveImage(image_name);
                    }
                }
                cout << "Please enter the directory or the name of the image you want to edit\n";
                cout<<"with the format .jpg, .bmp, .png, .tga:"<<endl;
                cin >> image_name;
                // Delete the old image if it exists
                delete image;
                // Load the new image
                image = new Image(image_name);
                break;
            }
                // Apply a filter
            case 2:
            {
                if (image == nullptr)
                {
                    cout << "No image loaded. Please load an image first." << endl;
                    break;
                }
                cout << "Please choose a filter to apply:" << endl;
                cout << "1. Rotate the image" << endl;
                cout << "2. Darken or lighten the image" << endl;
                cout << "3. Convert the image to black and white" << endl;
                cout << "4. Invert the color of the image" << endl;
                cout << "5. Convert the image to grayscale" << endl;

                int filterOption;
                // Loop until a valid input is given
                while (!(cin >> filterOption) || (filterOption < 1 || filterOption > 5))
                {
                    cout << "Invalid option. Please try again." << endl;
                    // Clear the error flags
                    cin.clear();
                    // Ignore the rest of the line
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                switch (filterOption)
                {
                    case 1:
                        flipImage(*image);
                        break;
                    case 2:
                        darken_and_lighten(*image);
                        break;
                    case 3:
                        convertToBlackandWhite(*image);
                        break;
                    case 4:
                        invertImageColor(*image);
                        break;
                    case 5:
                        grayscale(*image);
                        break;
                }
                cout<<"Filter applied successfully!"<<endl;
                break;
            }
                // Save the image
            case 3:
            {
                if (image == nullptr)
                {
                    cout << "No image to save. Please load an image first." << endl;
                    break;
                }
                cout << "Do you want to save the image in the same file or in a new file? (same/new): ";
                string saveOption;
                cin >> saveOption;
                // Convert the input to lowercase
                transform(saveOption.begin(), saveOption.end(), saveOption.begin(), ::tolower);
                // Loop until a valid input is given
                while (saveOption != "same" && saveOption != "new")
                {
                    cout << "Invalid option. Please try again." << endl;
                    cin >> saveOption;
                    // Convert the input to lowercase
                    transform(saveOption.begin(), saveOption.end(), saveOption.begin(), ::tolower);
                }

                if (saveOption == "same")
                {
                    image->saveImage(image_name);
                }
                else if (saveOption == "new")
                {
                    cout << "Enter the directory and name of the photo you want to save with the format .jpg, .bmp, .png, .tga: ";
                    cin >> image_name;
                    image->saveImage(image_name);
                }
                break;
            }
                // Exit the program
            case 4:
            {
                // If there is a current image
                if (image != nullptr)
                {
                    cout << "Do you want to save the current image before exiting? (yes/no): ";
                    string saveCurrent;
                    cin >> saveCurrent;
                    // Convert the input to lowercase
                    transform(saveCurrent.begin(), saveCurrent.end(), saveCurrent.begin(), ::tolower);
                    // Loop until a valid input is given
                    while (saveCurrent != "yes" && saveCurrent != "no")
                    {
                        cout << "Invalid option. Please try again." << endl;
                        cin >> saveCurrent;
                        // Convert the input to lowercase
                        transform(saveCurrent.begin(), saveCurrent.end(), saveCurrent.begin(), ::tolower);
                    }

                    if (saveCurrent == "yes")
                    {
                        cout << "Enter the directory and name of the photo you want to save with the format .jpg, .bmp, .png, .tga: ";
                        cin >> image_name;
                        image->saveImage(image_name);
                    }
                }
                last:
                // Delete the image before exiting
                delete image;
                cout<<"Thank you for using our program!"<<endl;
                return 0;
            }
        }
    }
}
