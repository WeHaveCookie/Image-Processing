#ifndef MYHISTOROGRAM_H
#define MYHISTOROGRAM_H
#include "MyImage.hpp"

class MyHistorogram
{
    public:
        MyHistorogram(MyImage *image);
        virtual ~MyHistorogram();
        void getBorderValues(unsigned int* minValue, unsigned int* maxValue);
        void reloadHistogram(MyImage *image);
    protected:
        void buildHistogram(MyImage *image);
    private:
        unsigned int* m_histogram;
};

#endif // MYHISTOROGRAM_H
