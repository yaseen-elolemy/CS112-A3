#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;


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
    string image_name;
    cout<<"Welcome to Editing Photo Program"<<endl;
    while(image_name != "exit")
    {
        image_name.clear();
        cout<<"Pls enter the name of the image you want to edit or(exit): ";
        cin>>image_name;
        if(image_name!= "exit" )
            {
            Image image(image_name);

            /*
             cout<<"PLs choose the filter you want: ";
             here we will insert the filters

             */
            cout<<"Enter the new name of the photo you want ";
            cout<<"and the format .jpg, .bmp, .png, .tga:";
            cin>>image_name;
            // when we activate the filters
                // we can here make a choice to the user if he wants to save the new photo with the same name and same file or new file with new name
            if(image.saveImage(image_name))
            {
                cout<<"changes saved successfully"<<endl;
            }
        }
        
    }
    return 0;

}
