#pragma once
#include<iostream>
#include<string>

class FileOperation
{
    public :

        FileOperation();
        ~FileOperation();
        void extractCoordinates();
        void getPoints();
        double calculateDistance(double,double,double,double,double,double);
};