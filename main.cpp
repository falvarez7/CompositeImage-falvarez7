//Author: Frederick Alvarez
#include<string>
#include<iostream>
#include<vector>
#include"bitmap.h"

using namespace std;

//function prototypes
bool sameSize(string, string);
int colSize(Bitmap);
int rowSize(Bitmap);
bool validFile(string);
vector <vector <Pixel> > compositor(vector <string>);
void averager(vector <vector <Pixel> > &,int);

//variable declaration
const int MAX_FILES = 10;
vector<string> fileVector;
bool tester,tester1,tester2;
string filename,filename1;
int size;
Bitmap picture;

int main()
{
//Initial file entry, seperate in order to define a base image size. 
    do
    {
        cout<<"Enter up to 10 bitmap files or DONE when finished. "<<endl;
        cin>>filename1;
        tester = validFile(filename1);
        if(tester ==true)
            {
            fileVector.push_back(filename1);
            }
        else
            {
            cout<<"Error: Invalid file type or the file does not exist, try again."<<endl;
            };
    }
    while(tester!=true);
//File entry for the remaining files. 
    while(fileVector.size()<MAX_FILES || filename != "DONE")
    {
        if(fileVector.size()<MAX_FILES)
        {
            cout<<"Enter another bitmap file or enter DONE when finished"<<endl;
            cin>>filename;
            if(filename=="DONE")
            {
                cout<<"DONE has been selected. Composition initialized."<<endl;
                break;
            }
            else if(filename !="DONE" && fileVector.size()<MAX_FILES )
            {
                tester1 = validFile(filename);
                if(tester1 == true)
                {
                    tester2 = sameSize(filename,filename1);
                    if(tester2==true)
                    {
                        fileVector.push_back(filename);
                    }
                    else
                    {
                        cout<<"Error: Image files are not the same dimensions."<<endl;
                    }
                }   
                else
                {
                    cout<<"Error: invalid file type or file does not exist"<<endl;
                }

            }  
        }
        //Condition is when the length of the file Vector meets the maximum amount of files.
        else
        {
            cout<<"The maximum amount of Images has been loaded. Composition Initialized."<<endl;
            break;
        }
    }
    vector< vector <Pixel> > compositeMatrix = compositor(fileVector);
    if(fileVector.size()>=2)
    {
        picture.fromPixelMatrix(compositeMatrix);
        picture.save("composite-falvarez7.bmp");
    }
    else
    {
         cout<<"Error: This program requires a minimum of two images in order to make a composite image. Program Terminated. "<<endl;

    }
return 0; 
}

//function definitions
//simply checks if the filename provided is a valid bitmap file.
bool validFile(string file)
{
    bool valid;
    Bitmap pic;
    pic.open(file);
    valid = pic.isImage();
    return valid;
}
//checks if two entered filenames refer to two equal dimensioned bitmap and gives a booleon in return. 
bool sameSize(string file1,string file2)
{
        Bitmap bit1, bit2;
        bit1.open(file1);
        bit2.open(file2);
        int width1 = colSize(bit1);
        int width2 = colSize(bit2);
        int height1 = rowSize(bit1);
        int height2 = rowSize(bit2);
        if (width1==width2 && height1 == height2)
           {
           return true;
           }
        else
           {
           return false;
           }
}
//Checks the row size of a given bitmap. For use in sameSize.
int rowSize(Bitmap bitmap)
{
    vector< vector<Pixel> > pixelMatrix = bitmap.toPixelMatrix();
    return pixelMatrix.size();
}
//Checks the column size of a given bitmap. For use in sameSize.
int colSize(Bitmap bitmap)
{
    vector< vector<Pixel> > pixelMatrix = bitmap.toPixelMatrix();
    return pixelMatrix[0].size();
}
//Compositor recieves the string vector of file names and opens and sums all of the pixel rgb values for the bitmap files. Needs averager to average these values once completed.
vector <vector <Pixel> > compositor(vector <string> fileVec )
{
        vector <vector <Pixel> > sumMatrix;
        vector <vector <Pixel> > iterMatrix;
        Bitmap initBitmap,iterBitmap;
        Pixel dot1,dot2;

        initBitmap.open(fileVec[0]);
        sumMatrix = initBitmap.toPixelMatrix();
        for(int i = 1;i<fileVec.size();i++)
        {
            iterBitmap.open(fileVec[i]);
            iterMatrix = iterBitmap.toPixelMatrix();
            for(int j = 0;j<sumMatrix.size();j++)
            {
                for(int k = 0;k<sumMatrix[j].size();k++)
                {
                dot1 = sumMatrix[j][k];
                dot2 = iterMatrix[j][k];
                dot1.red=dot1.red+dot2.red;
                dot1.blue=dot1.blue+dot2.blue;
                dot1.green=dot1.green+dot2.green;
                sumMatrix[j][k] = dot1;

                }
            }
        cout<<"Image "<<i+1<<" of "<<fileVec.size()<<" has been processed. "<<endl;
    
        }
        averager(sumMatrix,fileVec.size());
        return sumMatrix;
}
//averager simply takes each pixel in the sumMatrix and divides it by the number of bitmap files entered in order to get an average. It uses pass by reference. 
void averager(vector <vector <Pixel> > & compMat,int size)
{
    Pixel dot;
    for(int i = 0;i<compMat.size();i++)
    {
        for(int j =0;j<compMat[i].size();j++)
        {
        dot = compMat[i][j];
        dot.red = dot.red/size;
        dot.blue = dot.blue/size;
        dot.green = dot.green/size;
        compMat[i][j] = dot;

        }
    }
}




