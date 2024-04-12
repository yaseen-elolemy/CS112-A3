/*
 File: CS112_A3_T1_S21_20230074_20230465_20230468.cpp

Purpose: This is a program that allows the user to load an image, apply filters to it, and save the edited image.
                 The filters are: rotate, invert, convert to grayscale, darken or lighten, and convert to black and white.
                The user can choose to load a new image, apply a filter to the current image, save the current image, or exit the program.

 Author:    Eyad Tamer Naguib 20230074 - S21 -> Grayscale - Darken/Lighten - Detect Edges - purple filter - Merge Images Functions
            Yassin Ahmed Ali 20230465 - S21 -> Flipping the image and Convert to Black and White Function
            Yaseen Mohamed Kamal 20230468 - S21  ->  Invert the color Functions

 Emails: eyadmohandiss@gmail.com - yassinsawy@outlook.com - yaseen.elolemy@gmail.com

 */

#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;


Image resize_image_for_merge(Image &image, int newWidth, int newHeight)
{

    // Create a new Image object with the specified width and height
    Image newImage(newWidth, newHeight);

    // Calculate the scaling factors for the width and height
    double scaleX = static_cast<double>(image.width) / newWidth;
    double scaleY = static_cast<double>(image.height) / newHeight;

    // Loop over each pixel in the new image
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            // Calculate the corresponding pixel coordinates in the original image
            int x = static_cast<int>(i * scaleX);
            int y = static_cast<int>(j * scaleY);

            // Copy the pixel data from the original image to the new image
            for (int k = 0; k < image.channels; ++k) {
                newImage.setPixel(i, j, k, image.getPixel(x, y, k));
            }
        }
    }
    return newImage;

}


void mergeImages(Image& image1) {
    string image2_name;
    cout << "Please enter the directory or the name of the second image you want to merge with the first image\n";
    cout<<"with the format .jpg, .bmp, .png, .tga: ";
    cin >> image2_name;
    // Load the second image
    Image image2(image2_name);

    // Check if images have different dimensions
    if (image1.width != image2.width || image1.height != image2.height) {
        int merge_option;
        cout<<"The images have different dimensions. Please choose an option to resize the images:"<<endl;
        cout<<"1. Resize both images to the largest dimensions"<<endl;
        cout<<"2. Resize both images to the smallest dimensions"<<endl;
        cout<<"Please enter your choice: ";

        while (!(cin >> merge_option) || (merge_option < 1 || merge_option > 2))
        {
            cout << "Invalid option. Please try again." << endl;
            // Clear the error flags
            cin.clear();
            // Ignore the rest of the line
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if(merge_option==1) {
            // Option 1: Resize both images to the largest dimensions
            int maxWidth = max(image1.width, image2.width);
            int maxHeight = max(image1.height, image2.height);
            resize_image_for_merge(image1, maxWidth, maxHeight);
            resize_image_for_merge(image2, maxWidth, maxHeight);
        }
        else if(merge_option==2) {
            // Option 2: Resize both images to the smallest dimensions
            int minWidth = min(image1.width, image2.width);
            int minHeight = min(image1.height, image2.height);
            resize_image_for_merge(image1, minWidth, minHeight);
            resize_image_for_merge(image2, minWidth, minHeight);
        }
    }


    // Merge the images
    // For simplicity, let's just blend the images by averaging pixel values
    for (int i = 0; i < image1.width; i++) {
        for (int j = 0; j < image1.height; j++) {
            for (int k = 0; k < image1.channels; k++) {
                // Blend pixel values from both images
                int pixelValue = (image1.getPixel(i, j, k) + image2.getPixel(i, j, k)) / 2;
                // Set merged pixel value to the first image
                image1.setPixel(i, j, k, pixelValue);
            }
        }
    }
}

void purpleFilter(Image &image) {   //By Eyad Tamer Naguib: 20230074
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Get the original colors of the pixel
            int red = image.getPixel(i, j, 0);
            int blue = image.getPixel(i, j, 2);

            // Add purple tint
            red += 128;  // Increase red
            blue += 128; // Increase blue

            // Ensure color values are within valid range (0-255)
            red = min(255, max(0, red));
            blue = min(255, max(0, blue));

            // Set the new colors of the pixel
            image.setPixel(i, j, 0, red);
            image.setPixel(i, j, 2, blue);
        }
    }
}

void rotateImage(Image& image)     //By Yaseen El-Olemy: 20230468
{
    int toRotate;       //placeholder to specify
    cout<<"to rotate 90 Degrees Clockwise[1]\nto rotate 180 Degrees[2]\nto rotate 270 Degrees Clockwise[3]\n-> ";
    cin>>toRotate;
    string newname;
    cout<<"Enter name to save file in (or same to save in same file) with the format .jpg, .bmp, .png, .tga: ";
    cin>>newname;

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
        image = inverted;
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
        image = inverted;
    }

    if(toRotate == 3)
    {
        Image inverted(image.height, image.width);
        for(int i = image.width -1 ; i>=0; --i)
        {
            for(int j = image.height -1; j>=0; --j)
            {
                for(int k = 0; k < image.channels; ++k)
                {
                    inverted(j , i ,k) = image(i, j, k);
                }
            }
        }
        image = inverted;
    }
}


void detect_edges(Image& image) //By Eyad Tamer Naguib: 20230074
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

void crop(Image &image)   // By Yassin Ahmed Ali: 20230465
{
    int x, y,width,height;
    cout << "Enter the x-coordinate of the top-left corner of the crop area: ";
    cin >> x;
    cout << "Enter the y-coordinate of the top-left corner of the crop area: ";
    cin >> y;
    cout << "Enter the width of the crop area: ";
    cin >> width;
    cout << "Enter the height of the crop area: ";
    cin >> height;
    // Check if the crop dimensions are valid
    if (x < 0 || y < 0 || width <= 0 || height <= 0 || x + width > image.width || y + height > image.height) {
        cout << "Invalid crop dimensions." << endl;
        return;
    }

    // Create a new Image object with the specified width and height
    Image newImage(width, height);

    // Copy the pixel data from the original image to the new image
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                newImage.setPixel(i, j, k, image.getPixel(x + i, y + j, k));
            }
        }
    }
    image = newImage;
}
void resize(Image &image) //By Yassin Ahmed Ali: 20230465
{

    int newWidth, newHeight;
    cout << "Enter the new width: ";
    cin >> newWidth;
    cout << "Enter the new height: ";
    cin >> newHeight;
    // Check if the new dimensions are valid
    if (newWidth <= 0 || newHeight <= 0) {
        cout << "Invalid image dimensions." << endl;
        return;
    }

    // Create a new Image object with the specified width and height
    Image newImage(newWidth, newHeight);

    // Calculate the scaling factors for the width and height
    double scaleX = static_cast<double>(image.width) / newWidth;
    double scaleY = static_cast<double>(image.height) / newHeight;

    // Loop over each pixel in the new image
    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            // Calculate the corresponding pixel coordinates in the original image
            int x = static_cast<int>(i * scaleX);
            int y = static_cast<int>(j * scaleY);

            // Copy the pixel data from the original image to the new image
            for (int k = 0; k < image.channels; ++k) {
                newImage.setPixel(i, j, k, image.getPixel(x, y, k));
            }
        }
    }
    image = newImage;

}


void InfraredFilter(Image& image) { //By Yassin Ahmed Ali: 20230465

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i, j, 0) = min(image(i, j, 0) + 200, 255);
            image(i, j, 1) = min(image(i, j, 1) + 50, 255);
            image(i, j, 2) = min(image(i, j, 2) + 50, 255);
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
                cout << "1. Flip the image" << endl;
                cout << "2. Darken or lighten the image" << endl;
                cout << "3. Convert the image to black and white" << endl;
                cout << "4. Invert the color of the image" << endl;
                cout << "5. Convert the image to grayscale" << endl;
                cout << "6. Detect edges in the image" << endl;
                cout << "7. Merge the image with another image" << endl;
                cout << "8. Apply a purple filter to the image" << endl;
                cout<< "9. Crop Image" <<endl;
                cout<< "10. Resize Image" << endl;
                cout<<"11. Apply Infrared Filter" << endl;
                // the rest of the filters
                int filterOption;
                // Loop until a valid input is given
                while (!(cin >> filterOption) || (filterOption < 1 || filterOption > 8))
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
                    case 6:
                        detect_edges(*image);
                        break;
                    case 7:
                        mergeImages(*image);
                        break;
                    case 8:
                        purpleFilter(*image);
                        break;
                     case 9:
                        crop(*image);
                        break;
                    case 10:
                        resize(*image);
                        break;
                    case 11:
                        InfraredFilter(*image);
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
                    cout << "Image saved successfully!" << endl;
                }
                else if (saveOption == "new")
                {
                    cout << "Enter the directory and name of the photo you want to save with the format .jpg, .bmp, .png, .tga: ";
                    cin >> image_name;
                    image->saveImage(image_name);
                    cout << "Image saved successfully!" << endl;
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
                    if (saveCurrent=="no") {
                        goto last;
                    }

                    if (saveCurrent == "yes")
                    {
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
                            cout << "Image saved successfully!" << endl;
                        }
                        else if (saveOption == "new")
                        {
                            cout << "Enter the directory and name of the photo you want to save with the format .jpg, .bmp, .png, .tga: ";
                            cin >> image_name;
                            image->saveImage(image_name);
                            cout << "Image saved successfully!" << endl;
                        }
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
