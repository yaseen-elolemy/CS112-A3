#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;


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
