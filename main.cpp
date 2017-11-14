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
vector <vector <Pixel> > compositor(vector <string> fileVec );

void averager(vector <vector <Pixel> > & ,int);

//variable declaration
const int MAX_FILES = 10;
vector<string> fileVector;
bool tester;
string filename,filename1;
int size;
Bitmap picture;

int main()
{
    cout<<"Enter the name of 2 files."<<endl;
    do
    {
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
    }
    while(tester!=true);
    while(fileVector.size()<MAX_FILES || filename != "Done")

        {
        bool tester1,tester2;
        if(fileVector.size()<MAX_FILES)
        {
        cin>>filename;
        if(filename=="Done")
            {
            break;
            }
        else if(filename !="Done" && fileVector.size()<=MAX_FILES-1 )
            {tester1 = validFile(filename);
                if(tester1 == true)
                    {
                      tester2 = sameSize(filename,filename1);
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

         }
         }
        else
            {
        break;
        }

         size = fileVector.size();
        cout<<"size is: "<<size<<endl;
            }
        cout<<"You have finished this loop successfully"<<endl;
        vector< vector <Pixel> > compositeMatrix = compositor(fileVector);
        averager(compositeMatrix,fileVector.size());
        picture.fromPixelMatrix(compositeMatrix);
        picture.save("compositeImage.bmp");
        cout<<"Good Job! I like what you got!"<< endl;
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
    cout<<i+1<<" files have been processed. "<<endl;
    }
    return compMatrix;
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




