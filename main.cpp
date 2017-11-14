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
        //Condition is when the file Vector excedes the maximum amount of files.
        else
        {
            cout<<"The maximum amount of Images has been loaded. Composition Initialized."<<endl;
            break;
        }
    }
    vector< vector <Pixel> > compositeMatrix = compositor(fileVector);
    averager(compositeMatrix,fileVector.size());
    if(fileVector.size()>2)
    {
        picture.fromPixelMatrix(compositeMatrix);
        picture.save("composite-falvarez7.bmp");
    }
    else
    {
    }
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


//4.)Inside the continue loop, have the first image converted into a pixel matrix and set the variable composite matrix  equal to the first pixel matrix. After this initial conversion has occured, the rest of the bitmaps will be converted and averaged into the composite matrix in a function called Compositor within a for loop. This loop will also print out how many bitmaps have been converted. 

//Compositor recieves the composite pixel matrix and one of the iterated Bitmaps. First it converts the iterated bitmap into a pixel matrix. It then averages the two pixel matrices and sets compMatrix equal to the new matrix(Why it's pass-by-reference).
vector <vector <Pixel> > compositor(vector <string> fileVec )
{
    if(fileVec.size()<2)
    {   vector< vector<Pixel> > emptyMatrix;
        cout<<"Error: This program requires a minimum of two images in order to make a composite image. Program Terminated. "<<endl;
        return emptyMatrix;
    }
    else
    {
        vector <vector <Pixel> > compMatrix;
        vector <vector <Pixel> > tempMatrix;
        Bitmap bitmap,iterBitmap;
        bitmap.open(fileVec[0]);
        Pixel dot1, dot2;
        compMatrix = bitmap.toPixelMatrix();
        for(int i = 1;i<fileVec.size();i++)
        {
            iterBitmap.open(fileVec[i]);
            tempMatrix = iterBitmap.toPixelMatrix();
            for(int j = 0;j<compMatrix.size();j++)
            {
                for(int k = 0;k<compMatrix[j].size();k++)
                {
                dot1 = compMatrix[j][k];
                dot2 = tempMatrix[j][k];
                dot1.red=dot1.red+dot2.red;
                dot1.blue=dot1.blue+dot2.blue;
                dot1.green=dot1.green+dot2.green;
                compMatrix[j][k] = dot1;

                }
            }
        cout<<"Image "<<i+1<<" of "<<fileVec.size()<<" has been processed. "<<endl;
    
        }
    
        return compMatrix;
    }
}
//Make this one pass by reference once tested
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




