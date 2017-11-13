//Author: Frederick Alvarez
#include<string>
#include<iostream>
#include<vector>
#include"bitmap.h"

using namespace std;
//function prototypes
bool sameSize(Bitmap, Bitmap);
int colSize(Bitmap);
int rowSize(Bitmap);
bool validFile(string);
//variable declaration
vector<string> fileVector;
Bitmap picture1, picture2;
bool tester;
bool rightSize = false;
string filename,filename1;
int height, width,size;
int main()
{
    cout<<"Enter the name of 2 files."<<endl;
    cin>>filename1;
    tester = validFile(filename1);
    if(tester ==true)
        {
        cout<<"cool."<<endl;
        fileVector.push_back(filename1);
        cout<<fileVector.size()<<endl;
        }
    else
        {
        cout<<"invalid file, try again"<<endl;
        };
    do
        {
        bool tester1,tester2;
        cin>>filename;
        tester1 = validFile(filename);
        if(tester1 == true)
            {
            picture1.open(filename1);
            picture2.open(filename);
            tester2 = sameSize(picture1,picture2);
            if(tester2==true)
                {
                fileVector.push_back(filename);
                cout<<fileVector.size()<<endl;
                }
            else
                {
                cout<<"These pictures are not the same size"<<endl;
                }
            }   
        else
            {
            cout<<"invalid File"<<endl;
            }
        size = fileVector.size();
        cout<<"size is: "<<size<<endl;
        }
    while(fileVector.size()<=9 || filename != "Done");
    cout<<"You have finished this loop successfully"<<endl;
return 0; 
}

//function definitions
bool validFile(string file)
{
    bool valid;
    Bitmap pic;
    pic.open(file);
    valid = pic.isImage();
    return valid;
}

bool sameSize(Bitmap file1,Bitmap file2)
{
        int width1 = colSize(file1);
        int width2 = colSize(file2);
        int height1 = rowSize(file1);
        int height2 = rowSize(file2);
        if (width1==width2 && height1 == height2)
           {
           return true;
           }
        else
           {
           return false;
           }
}
int rowSize(Bitmap bitmap)
{
    vector< vector<Pixel> > pixelMatrix = bitmap.toPixelMatrix();
    return pixelMatrix.size();
}

int colSize(Bitmap bitmap)
{
    vector< vector<Pixel> > pixelMatrix = bitmap.toPixelMatrix();
    return pixelMatrix[0].size();
}


//1.) A do while loop which has a boolean condition so it repeats until the correct amount of files or correct format have been entered, or the input is done. This loop will also check the size of the first image as reference for the following images. These images will be checked by a function called samesize.










    //a.) inside this loop, have an if statement which, if the format and size of the entered file is correct, adds 1 to the count of correctly entered files.
   
   //b.) inside this loop, have an else statement which prints an error message for any file format other than bmp
   

//2.) Have another if statment outside of this loop which will use the amount from 1.)a.) to check if more than 2 files have been correctly entered and then either return true or false. 

//3.)Have another if and else statment to either end the program if enough images are entered, or continue with the program. 

//4.)Inside the continue loop, have the first image converted into a pixel matrix and set the variable composite matrix  equal to the first pixel matrix. After this initial conversion has occured, the rest of the bitmaps will be converted and averaged into the composite matrix in a function called Compositor within a for loop. This loop will also print out how many bitmaps have been converted. 

//Compositor recieves the composite pixel matrix and one of the iterated Bitmaps. First it converts the iterated bitmap into a pixel matrix. It then averages the two pixel matrices and sets compMatrix equal to the new matrix(Why it's pass-by-reference).
//void compositor(vector< vector<Pixel> > &, Bitmap)

//Averages are not the sum of averages.
//5.)Once all the matrices have been ran through compositor, compMatrix will be converted back to a Bitmap. 


