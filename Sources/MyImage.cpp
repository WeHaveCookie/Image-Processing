#include "MyImage.hpp"
#include <iostream>

//////////////////////////////////////////////////////////////
MyImage::MyImage()
: wxImage()
{
}

//////////////////////////////////////////////////////////////
MyImage::MyImage(wxString fileName)
: wxImage(fileName)
{
    //m_histogram = new MyHistorogram(this)
}

//////////////////////////////////////////////////////////////
MyImage::MyImage(wxImage image)
:wxImage(image)
{
    //m_histogram = new MyHistorogram(this)
}

MyImage::MyImage(const MyImage& image)
:wxImage(image)
{

}

MyImage::MyImage(unsigned char* image, int height, int width)
:wxImage(width,height)
{
    this->SetData(image);
}

//////////////////////////////////////////////////////////////
MyImage::~MyImage()
{

}

//////////////////////////////////////////////////////////////
void MyImage::negative()
{
    int taille = GetWidth() * GetHeight() * 3;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    for(int i(0);i<taille;i+=3)
    {
        outBuffer[i] = 255-inBuffer[i];
        outBuffer[i+1] = 255-inBuffer[i+1];
        outBuffer[i+2] = 255-inBuffer[i+2];
    }
    SetData(outBuffer);
}

//////////////////////////////////////////////////////////////
void MyImage::desaturate()
{
    int taille = GetWidth() * GetHeight() * 3;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    float li;
    unsigned char buffTemp;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    for(int i(0);i<taille;i+=3)
    {
        li = 0.2126*inBuffer[i] + 0.7152*inBuffer[i+1] + 0.0722*inBuffer[i+2];
        buffTemp = (float)(li+0.5);
        outBuffer[i] = buffTemp;
        outBuffer[i+1] = buffTemp;
        outBuffer[i+2] = buffTemp;
    }
    SetData(outBuffer);
}

//////////////////////////////////////////////////////////////
void MyImage::threshold(int seuil)
{
    desaturate();
    int taille = GetWidth() * GetHeight() * 3;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    for(int i(0);i<taille;i++)
    {
        outBuffer[i] = inBuffer[i];
        if (inBuffer[i] <= seuil)
        {
            outBuffer[i] = 0;
        }
    }
    SetData(outBuffer);
}

//////////////////////////////////////////////////////////////
void MyImage::mirror(bool horizontally)
{
    int largeur = GetWidth();
    int hauteur = GetHeight();
    int taille = largeur * hauteur * 3;
    int hc = 0;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    if (!horizontally)
    {
        for(int i(0);i<taille;i+=3)
        {

            if ((i/3)%largeur==0) {hc++;}
            outBuffer[i] = inBuffer[((hauteur-hc)*(largeur*3))+(((i/3)%largeur)*3)];
            outBuffer[i+1] = inBuffer[(((hauteur-hc)*(largeur*3))+(((i/3)%largeur)*3))+1];
            outBuffer[i+2] = inBuffer[(((hauteur-hc)*(largeur*3))+(((i/3)%largeur)*3))+2];
        }

    }
    else
    {
        for(int i(0);i<taille;i+=3)
        {
            if ((i/3)%largeur==0) {hc++;}
            outBuffer[i] = inBuffer[((largeur-((i/3)%largeur+1))+((hc-1)*largeur))*3];
            outBuffer[i+1] = inBuffer[(((largeur-((i/3)%largeur+1))+((hc-1)*largeur))*3)+1];
            outBuffer[i+2] = inBuffer[(((largeur-((i/3)%largeur+1))+((hc-1)*largeur))*3)+2];
        }
    }
    SetData(outBuffer);
}

//////////////////////////////////////////////////////////////
wxImage MyImage::rotate90(bool boolean)
{
    wxImage image;
    int largeur = GetWidth();
    int hauteur = GetHeight();
    int taille = largeur * hauteur * 3;
    image.Create(hauteur, largeur, false);
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = image.GetData();
    outBuffer = (unsigned char*) malloc (taille);
    for (int j(0);j<hauteur;j++)
    {
        for (int i(0);i<largeur;i++)
        {
            if (boolean)
            {
                outBuffer[i*j] = inBuffer[(((i+1)*hauteur) - j - 1)*3];
            }
            else
            {
                outBuffer[i*j] = inBuffer[((hauteur*(largeur-1)) + j - (i*hauteur))];
            }
        }
    }
    image.SetData(outBuffer);
    return image;
}

//////////////////////////////////////////////////////////////
void MyImage::rotateTest(bool boolean)
{
    int largeur = GetWidth();
    int hauteur = GetHeight();
    int taille = largeur * hauteur * 3;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    for (int j(0);j<hauteur;j++)
    {
        for (int i(0);i<largeur;i++)
        {
            if (boolean)
            {
                outBuffer[i*j] = inBuffer[(((i+1)*hauteur) - j - 1)*3];
            }
            else
            {
                outBuffer[i*j] = inBuffer[((hauteur*(largeur-1)) + j - (i*hauteur))];
            }
        }
    }
    SetData(outBuffer);
}

//////////////////////////////////////////////////////////////
void MyImage::posterize(/*unsigned char*/int bitCount)
{
    int taille = GetWidth() * GetHeight() * 3;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    unsigned mask = 0x00000000;
    int bit = 8;
    if (bitCount != /*'0'*/0)
    {
        for(char i(/*'0'*/0);i<bitCount;i++)
        {
            mask += (1u<<bit);
            bit--;
        }
    }
    for(int i(0);i<taille;i++)
    {
        outBuffer[i] = inBuffer[i] & mask;
    }
    SetData(outBuffer);
}

//////////////////////////////////////////////////////////////
RGBPalette* MyImage::createPalette()
{
    RGBPalette* palette;
    RGBColor* color;
    palette = new RGBPalette;
    palette->table = (RGBColor*) malloc(sizeof(RGBColor)*8);
    color = (RGBColor*) malloc (8);
    // Palette : Black / White / Red / Green / Blue / Cyan / Magenta / Yellow
    // BLACK 0;0;0 //
    color[0].R = 0;
    color[0].G = 0;
    color[0].B = 0;
    // WHITE 255;255;255 //
    color[1].R = 255;
    color[1].G = 255;
    color[1].B = 255;
    // RED 255;0;0 //
    color[2].R = 255;
    color[2].G = 0;
    color[2].B = 0;
    // GREEN 0;255;0//
    color[3].R = 0;
    color[3].G = 255;
    color[3].B = 0;
    // BLUE 0;0;255//
    color[4].R = 0;
    color[4].G = 0;
    color[4].B = 255;
    // CYAN 0;255;255//
    color[5].R = 0;
    color[5].G = 255;
    color[5].B = 255;
    // MAGENTA 255;0;255//
    color[6].R = 255;
    color[6].G = 0;
    color[6].B = 255;
    // YELLOW 255;255;0//
    color[7].R = 255;
    color[7].G = 255;
    color[7].B = 0;
    palette->sizePal = 8;
    palette->table = color;
    /*std::cout << "Create Palette sucess " << std::endl;
    for (int i(0);i<palette->sizePal;i++)
    {
        std::cout << "\tR : " << (int)palette->table[i].R << " | G : " << (int)palette->table[i].G << " | B : " << (int)palette->table[i].B << std::endl;
    }*/
    return palette;
}

//////////////////////////////////////////////////////////////
RGBColor MyImage::colorProx(RGBColor color, RGBPalette* palette)
{
    char ch;
    int distanceSquared, minDistanceSquared, bestIndex = 0;
    minDistanceSquared = 255*255+255*255+255*255+1;
    for (int i(0);i<palette->sizePal;i++)
    {

        int Rdiff = ((int)color.R) - palette->table[i].R;
        int Gdiff = ((int)color.G) - palette->table[i].G;
        int Bdiff = ((int)color.B) - palette->table[i].B;
        distanceSquared = Rdiff*Rdiff + Gdiff*Gdiff + Bdiff*Bdiff;
        if (distanceSquared < minDistanceSquared)
        {
            minDistanceSquared = distanceSquared;
            bestIndex = i;
        }

    }
    return palette->table[bestIndex];
}

//////////////////////////////////////////////////////////////
wxImage MyImage::dither()
{
    wxImage image;
    int largeur = GetWidth();
    int hauteur = GetHeight();
    int taille = largeur * hauteur * 3;
    RGBColor oldPix;
    RGBColor newPix;
    RGBColorError errorQuant;
    Color buffR, buffG, buffB;
    RGBPalette* palette = createPalette();
    image.Create(largeur, hauteur, false);
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    memcpy(outBuffer, inBuffer, taille);

    for (int j(1);j<=hauteur;j++)
    {
        for (int i(0);i<largeur*3;i+=3)
        {
            oldPix.R = outBuffer[largeur*3*(j-1)+i];
            oldPix.G = outBuffer[largeur*3*(j-1)+(i+1)];
            oldPix.B = outBuffer[largeur*3*(j-1)+(i+2)];
            newPix = colorProx(oldPix,palette);
            outBuffer[largeur*3*(j-1)+i] = newPix.R;
            outBuffer[largeur*3*(j-1)+(i+1)] = newPix.G;
            outBuffer[largeur*3*(j-1)+(i+2)] = newPix.B;

            // Error Quantum //
            errorQuant.R = (float)oldPix.R-(float)newPix.R;
            errorQuant.G = (float)oldPix.G-(float)newPix.G;
            errorQuant.B = (float)oldPix.B-(float)newPix.B;

            //////////////
            // Disperse //
            //////////////
            //std::cout << "Disperse Start : " << std::endl;
            // Right-UP //
            if (i+3 < largeur*3)
            {
                //std::cout << "Do Right-Up" << std::endl;
                buffR = Color(((float)outBuffer[largeur*3*(j-1)+(i+3)]+(7.0/16.0 * (float)errorQuant.R)));
                buffG = Color(((float)outBuffer[largeur*3*(j-1)+(i+4)]+(7.0/16.0 * (float)errorQuant.G)));
                buffB = Color(((float)outBuffer[largeur*3*(j-1)+(i+5)]+(7.0/16.0 * (float)errorQuant.B)));
                outBuffer[largeur*3*(j-1)+(i+3)] =  buffR.getColor();
                outBuffer[largeur*3*(j-1)+(i+4)] =  buffG.getColor();
                outBuffer[largeur*3*(j-1)+(i+5)] =  buffB.getColor();
            }
            // Right-Down //
            if ((j+1) <= hauteur && (i+3) < largeur*3)
            {
                //std::cout << "Do Right-Down" << std::endl;
                buffR = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+3)]+(3.0/16.0 * (float)errorQuant.R)));
                buffG = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+4)]+(3.0/16.0 * (float)errorQuant.G)));
                buffB = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+5)]+(3.0/16.0 * (float)errorQuant.B)));
                outBuffer[largeur*3*((j+1)-1)+(i+3)] = buffR.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i+4)] = buffG.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i+5)] = buffB.getColor();
            }
            // Down //
            if ((j+1) <= hauteur)
            {
                //std::cout << "Do Down" << std::endl;
                buffR = Color(((float)outBuffer[largeur*3*((j+1)-1)+i]+(5.0/16.0 * (float)errorQuant.R)));
                buffG = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+1)]+(5.0/16.0 * (float)errorQuant.G)));
                buffB = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+2)]+(5.0/16.0 * (float)errorQuant.B)));
                outBuffer[largeur*3*((j+1)-1)+i] = buffR.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i+1)] = buffG.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i+2)] = buffB.getColor();
            }
            // Left-Down //
            if ((i/3)%largeur != 0 && j<hauteur)
            {
                //std::cout << "Do Left-Down" << std::endl;
                buffR = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i-3)]+(1.0/16.0 * (float)errorQuant.R)));
                buffG = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i-2)]+(1.0/16.0 * (float)errorQuant.G)));
                buffB = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i-1)]+(1.0/16.0 * (float)errorQuant.B)));
                outBuffer[largeur*3*((j+1)-1)+(i-3)] = buffR.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i-2)] = buffG.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i-1)] = buffB.getColor();
            }
            //char ch;
            //std::cin.get(ch);
        }
    }
    image.SetData(outBuffer);
    return image;
}


//////////////////////////////////////////////////////////////
void MyImage::ditherTest()
{
    int largeur = GetWidth();
    int hauteur = GetHeight();
    int taille = largeur * hauteur * 3;
    RGBColor oldPix;
    RGBColor newPix;
    RGBColorError errorQuant;
    Color buffR, buffG, buffB;
    RGBPalette* palette = createPalette();
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    memcpy(outBuffer, inBuffer, taille);

    for (int j(1);j<=hauteur;j++)
    {
        for (int i(0);i<largeur*3;i+=3)
        {
            oldPix.R = outBuffer[largeur*3*(j-1)+i];
            oldPix.G = outBuffer[largeur*3*(j-1)+(i+1)];
            oldPix.B = outBuffer[largeur*3*(j-1)+(i+2)];
            newPix = colorProx(oldPix,palette);
            outBuffer[largeur*3*(j-1)+i] = newPix.R;
            outBuffer[largeur*3*(j-1)+(i+1)] = newPix.G;
            outBuffer[largeur*3*(j-1)+(i+2)] = newPix.B;

            // Error Quantum //
            errorQuant.R = (float)oldPix.R-(float)newPix.R;
            errorQuant.G = (float)oldPix.G-(float)newPix.G;
            errorQuant.B = (float)oldPix.B-(float)newPix.B;

            //////////////
            // Disperse //
            //////////////
            //std::cout << "Disperse Start : " << std::endl;
            // Right-UP //
            if (i+3 < largeur*3)
            {
                //std::cout << "Do Right-Up" << std::endl;
                buffR = Color(((float)outBuffer[largeur*3*(j-1)+(i+3)]+(7.0/16.0 * (float)errorQuant.R)));
                buffG = Color(((float)outBuffer[largeur*3*(j-1)+(i+4)]+(7.0/16.0 * (float)errorQuant.G)));
                buffB = Color(((float)outBuffer[largeur*3*(j-1)+(i+5)]+(7.0/16.0 * (float)errorQuant.B)));
                outBuffer[largeur*3*(j-1)+(i+3)] =  buffR.getColor();
                outBuffer[largeur*3*(j-1)+(i+4)] =  buffG.getColor();
                outBuffer[largeur*3*(j-1)+(i+5)] =  buffB.getColor();
            }
            // Right-Down //
            if ((j+1) <= hauteur && (i+3) < largeur*3)
            {
                //std::cout << "Do Right-Down" << std::endl;
                buffR = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+3)]+(3.0/16.0 * (float)errorQuant.R)));
                buffG = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+4)]+(3.0/16.0 * (float)errorQuant.G)));
                buffB = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+5)]+(3.0/16.0 * (float)errorQuant.B)));
                outBuffer[largeur*3*((j+1)-1)+(i+3)] = buffR.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i+4)] = buffG.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i+5)] = buffB.getColor();
            }
            // Down //
            if ((j+1) <= hauteur)
            {
                //std::cout << "Do Down" << std::endl;
                buffR = Color(((float)outBuffer[largeur*3*((j+1)-1)+i]+(5.0/16.0 * (float)errorQuant.R)));
                buffG = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+1)]+(5.0/16.0 * (float)errorQuant.G)));
                buffB = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i+2)]+(5.0/16.0 * (float)errorQuant.B)));
                outBuffer[largeur*3*((j+1)-1)+i] = buffR.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i+1)] = buffG.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i+2)] = buffB.getColor();
            }
            // Left-Down //
            if ((i/3)%largeur != 0 && j<hauteur)
            {
                //std::cout << "Do Left-Down" << std::endl;
                buffR = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i-3)]+(1.0/16.0 * (float)errorQuant.R)));
                buffG = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i-2)]+(1.0/16.0 * (float)errorQuant.G)));
                buffB = Color(((float)outBuffer[largeur*3*((j+1)-1)+(i-1)]+(1.0/16.0 * (float)errorQuant.B)));
                outBuffer[largeur*3*((j+1)-1)+(i-3)] = buffR.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i-2)] = buffG.getColor();
                outBuffer[largeur*3*((j+1)-1)+(i-1)] = buffB.getColor();
            }
            //char ch;
            //std::cin.get(ch);
        }
    }
    SetData(outBuffer);
}

//////////////////////////////////////////////////////////////
int MyImage::countPixelColor()
{
    char* palette;
    palette = (char*) calloc(16777216,1);
    int curPix;
    int taille = GetWidth() * GetHeight() * 3;
    unsigned char* inBuffer;
    inBuffer = GetData();


    for(int i(0);i<taille;i+=3)
    {
        curPix = inBuffer[i];
        curPix += inBuffer[i+1]<<8;
        curPix += inBuffer[i+2]<<16;
        palette[curPix] = 1;
    }
    int color = 0;
    for(int i(0);i<16777216;i++)
    {
        color += (int)palette[i];
    }
    return color;
}


void MyImage::enhenceContrast(unsigned int minValue, unsigned int maxValue)
 {
    int largeur = GetWidth();
    int hauteur = GetHeight();
    int taille = largeur * hauteur * 3;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    Color buffR, buffG, buffB;
    float d,f;
    d = (255.0 * minValue) / ((float)minValue - (float)maxValue);
    f = 255.0 / ((float)maxValue - (float)minValue);
    for (int i(0);i<taille;i+=3)
    {
        buffR = Color(f * (float)inBuffer[i] + d);
        buffG = Color(f * (float)inBuffer[i+1] + d);
        buffB = Color(f * (float)inBuffer[i+2] + d);
        outBuffer[i] = buffR.getColor();
        outBuffer[i+1] = buffG.getColor();
        outBuffer[i+2] = buffB.getColor();
    }
    SetData(outBuffer);
 }

//////////////////////////////////////////////////////////////
void MyImage::enhenceContrast(int value)
{
    int largeur = GetWidth();
    int hauteur = GetHeight();
    int taille = largeur * hauteur * 3;
    Color buffR, buffG, buffB;
    unsigned char* inBuffer;
    unsigned char* outBuffer;
    inBuffer = GetData();
    outBuffer = (unsigned char*) malloc (taille);
    for (int i(0);i<taille;i+=3)
    {
        buffR = Color((int)inBuffer[i]+value);
        buffG = Color((int)inBuffer[i+1]+value);
        buffB = Color((int)inBuffer[i+2]+value);
        outBuffer[i] = buffR.getColor();
        outBuffer[i+1] = buffG.getColor();
        outBuffer[i+2] = buffB.getColor();
    }
    SetData(outBuffer);
}

///////////////////////////
//      CLASS COLOR      //
///////////////////////////

//////////////////////////////////////////////////////////////
void Color::setColor(float newvalue)
{
    if (newvalue < 0.0)
        m_color = 0.0;
    else if (newvalue > 255.0)
        m_color = 255.0;
    else
        m_color = newvalue;
}
