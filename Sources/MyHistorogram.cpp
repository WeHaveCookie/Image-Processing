#include "MyHistorogram.h"
#include <iostream>

//////////////////////////////////////////////////////////////
MyHistorogram::MyHistorogram(MyImage *image)
{
    m_histogram = (unsigned int*) calloc(255,sizeof(unsigned int));
    buildHistogram(image);
}

//////////////////////////////////////////////////////////////
MyHistorogram::~MyHistorogram()
{
    //dtor
}

//////////////////////////////////////////////////////////////
void MyHistorogram::reloadHistogram(MyImage *image)
{
    buildHistogram(image);
}

//////////////////////////////////////////////////////////////
void MyHistorogram::buildHistogram(MyImage *image)
{
    int taille = image->GetWidth() * image->GetHeight() * 3;
    int grayLvl;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = image->GetData();
    for (int i(0);i<taille;i+=3)
    {
        grayLvl = 0.299*inBuffer[i]+0.587*inBuffer[i+1]+0.114*inBuffer[i+2];
        m_histogram[grayLvl]++;
    }
    /*std::cout << "-------------" << std::endl;
    std::cout << "- Histogram -" << std::endl;
    std::cout << "-------------" << std::endl << std::endl;
    for (int i(0);i<255;i++)
    {
            std::cout << "Val : " << i << " = " << m_histogram[i] << std::endl;
    }*/
}

//////////////////////////////////////////////////////////////
void MyHistorogram::getBorderValues(unsigned int* minValue, unsigned int* maxValue)
{
    *minValue = 255;
    *maxValue = 0;
    int lastKnow;
    for (int i(0);i<255;i++)
    {
        if (m_histogram[i] > 0 && i < *minValue) {*minValue = i;}
        if (i!=0)
        {
            if (m_histogram[i] == 0 && m_histogram[i-1]>0) {*maxValue = i;}
        }
    }
    if (m_histogram[254] > 0 ) {*maxValue = 254;}
    std::cout << "Min : " << *minValue << std::endl;
    std::cout << "Max : " << *maxValue << std::endl;
}


