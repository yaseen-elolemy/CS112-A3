#include <bits/stdc++.h>
#include "Image_Class.h"
using namespace std;

void to_exit()
{
    cout<<"To exit the program pls enter (Exit)";
    string to_exit;cin.ignore();
    getline(cin,to_exit);
    if (toupper(to_exit[0]) == 'E' && toupper(to_exit[1]) == 'X' && toupper(to_exit[2]) == 'I' && toupper(to_exit[3]) == 'T')
    {
        cout << "Thank you for using Editing Photo Program!" << endl;
        exit(0);
    }
}

int main()
{
    cout<<"Welcome to Editing Photo Program"<<endl;
    while(true)
    {

        cout<<"Pls enter the name of the image you want to edit: ";
        string image_name;
        cin>>image_name;
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
        // a function to exit program
        to_exit();

    }





}
