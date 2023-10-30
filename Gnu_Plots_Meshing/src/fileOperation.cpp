#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cmath>
#include<algorithm>
#include "D:\Cpp\stlFile\Gnu_Plots_Meshing\header\fileOperation.h"

FileOperation :: FileOperation(){}

FileOperation :: ~FileOperation(){}

// Function for exctracting co ordinates from stl file to text file..
void FileOperation :: extractCoordinates()
{
    //Storing file paths in string..

    std::string inputFile = "D:\\Cpp\\stlFile\\Gnu_Plots_Meshing\\src\\flowerpot.stl"; 
    std::string outputFile = "D:\\Cpp\\stlFile\\Gnu_Plots_Meshing\\output\\final.txt";

    //
    std::ifstream input(inputFile);
    std::ofstream output(outputFile);

    if (!input.is_open() || !output.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    std::string line;
    std::string firstLine = "";
    int count = 0;
    std::vector<std::string> coordinates;

    while (std::getline(input, line)) 
    {
       int index=-1;
        index=line.find("vertex");
        
        if(index!=-1)
        {
            if(count==0)
            {
                firstLine = line.substr(index+7);
            }
            count+=1;
            output << line.substr(index+7)<<std::endl;
        }
        if (count==3)
        {
            output <<firstLine<<std::endl;
            firstLine="";
            count =0;
        }

    }

    input.close();
    output.close();
}

void FileOperation :: getPoints()
{
    std::ifstream inputFile("D:\\Cpp\\stlFile\\Gnu_Plots_Meshing\\output\\final.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open the file." << std::endl;
    }

    std::vector<double> xCoordinates, yCoordinates, zCoordinates;
    std::string line;

    while (std::getline(inputFile, line)) {
        double x, y, z;
        if (sscanf(line.c_str(), "%lf %lf %lf", &x, &y, &z) == 3) { 
            xCoordinates.push_back(x);
            yCoordinates.push_back(y);
            zCoordinates.push_back(z);
        } else {
            std::cerr << "Error: Invalid line format: " << line << std::endl;
        }
    }

    // Now, xCoordinates, yCoordinates, and zCoordinates contain the values from the file.
    
    // You can access the values like this:
    // for (size_t i = 0; i < xCoordinates.size(); i++) {
    //     double x = xCoordinates[i];
    //     double y = yCoordinates[i];
    //     double z = zCoordinates[i];
    //     std::cout << "x: " << x << ", y: " << y << ", z: " << z << std::endl; 
    // }

    std::vector<double> vector_aspectRatio {};
    std::vector<double> vector_skewnessRatio {};

    for(int i=0; i< xCoordinates.size(); i++)
    {
        if( i % 4 == 0)
        {
            std::vector<double> sides {};
            for(int j=i; j<i + 3; j++)
            {
                double distance = calculateDistance(xCoordinates[j],yCoordinates[j],zCoordinates[j],xCoordinates[j+1],yCoordinates[j+1],zCoordinates[j+1]);
                sides.push_back(distance);
            }

            std::sort(sides.begin(),sides.end());

            // std::cout<<"------------------\n";
            // for(double s : sides)
            //      std::cout<<"sides : "<<s<<std::endl;
            // std::cout<<"------------------\n";

            double aspectRatio = sides[2] / sides[0];
            vector_aspectRatio.push_back(aspectRatio);

            
            double skewnessRatio = sides[2] / (sides[0] + sides[1]);
            vector_skewnessRatio.push_back(skewnessRatio);
            sides.clear();
            }
        }

        std::cout<<"Aspect ratios : "<<std::endl;
        int arCount = 0;
        int goodCount = 0;
        for(double va : vector_aspectRatio){
            //std::cout<<va<<std::endl;
            if(va<=5) {
               //std:: cout << "Aspect ratio is good"<< std:: endl;
               goodCount++;
            }
            else{
               // std:: cout << "Aspect ratio of this triangle is not upto the mark" << std:: endl;
                 arCount++;
            }
        }
        std :: cout << "There are : " << goodCount << "  triangles whose mesh quality is excellent" << std :: endl;
        std :: cout << "There are : " << arCount << "  triangles whose mesh quality is poor" << std :: endl;
        
        std::cout<<"==================================\n";
        std::cout<<"Skewness ratios : "<<std::endl;
        int skcount = 0;
        int goodSkewness = 0;
        for(double vs : vector_skewnessRatio){
             //std::cout<<vs<<std::endl;

            if(vs<0.9 && vs > 0.33 ){
                //std :: cout << "Skewness of this triangle is good" << std :: endl;
                goodSkewness++;
            }
            else{

                //std :: cout << "Skewness of this triangle is not upto the mark" << std :: endl;
                skcount++;
            }

        }
         std :: cout << "There are :  " << goodSkewness << " triangles whose skewness ratio is Excellent" << std :: endl;
    
        std :: cout << "There are :  " << skcount << " triangles whose skewness ratio is not appropriate" << std :: endl;
    
    // for(double v : sides)
    //     std::cout<<v<<std::endl;
    inputFile.close();
    
}

double FileOperation :: calculateDistance(double x1,double y1,double z1,double x2, double y2, double z2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dz = z2 - z1;
    
    double distance = std::sqrt(dx * dx + dy * dy + dz * dz);
    
    return distance;
}