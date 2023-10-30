#include <iostream>
#include "../header/fileOperation.h"
//#include "D:\Cpp\stlFile\Gnu_Plots_Meshing\header\Read_File.h"

using namespace std;

int main()
{
    FileOperation mem;
    mem.extractCoordinates();
    mem.getPoints();
    return 0;
}