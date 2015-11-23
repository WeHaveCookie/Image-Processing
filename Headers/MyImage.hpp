#ifndef MYIMAGE_H
#define MYIMAGE_H
//#ifndef WX_PRECOMP
#include <wx/wx.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <wx/wxprec.h>
#include <stdlib.h>

//------------------------------//
//          CLASS IMAGE         //
//------------------------------//

typedef struct {
    unsigned char R, G, B;
} RGBColor;

typedef struct {
    char R, G, B;
} RGBColorError;

typedef struct {
    int sizePal;
    RGBColor* table;
} RGBPalette;


class MyImage: public wxImage
{
public:
    MyImage();
    MyImage(wxString fileName);
    MyImage(wxImage image);
    MyImage(const MyImage& image);
    MyImage(unsigned char* image, int height, int width);
    ~MyImage();
    void negative();
    void desaturate();
    void threshold(int seuil);
    void mirror(bool horizontally);
    wxImage rotate90(bool boolean);
    void rotateTest(bool boolean);
    void posterize(/*unsigned char*/int bitCount);
    wxImage dither();
    void ditherTest();
    int countPixelColor();
    void enhenceContrast(unsigned int minValue, unsigned int maxValue);
    void enhenceContrast(int value);

protected:
    RGBPalette* createPalette();
    RGBColor colorProx(RGBColor color, RGBPalette* palette);
    //MyHistorogram* m_histogram;
private:
};

class Color
{
public:
    Color() {}
    Color(float color) {setColor(color);}
    void setColor(float newvalue);
    inline unsigned char getColor() {return m_color;}
protected:
private:
    unsigned char m_color;
};

#endif
