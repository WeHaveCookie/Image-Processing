#include <wx/wxprec.h>
#include <stdlib.h>
#include <stdio.h>
#include "MyImage.hpp"
#include "MyThresholdDialog.hpp"
#include "MyRotateDialog.h"
#include "MyHistorogram.h"
#include "MyEnhenceDialog.hpp"
#include "MyMirrorDialog.h"
#include "MyPosterizeDialog.hpp"
#include "opencv_bridge.h"
#include <time.h>
#include <opencv/highgui.h>
//#include <cv.hpp>
#include <wx/thread.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif // WX_PRECOMP

DEFINE_EVENT_TYPE(wxEVT_MY_EVENT)

class MyFrame;
class MyApp;
class MyThread;

//------------------------------//
//          CLASS APP           //
//------------------------------//

class MyApp: public wxApp
{
public:
    virtual bool OnInit();
protected:
private:
};


//------------------------------//
//          CLASS PANEL         //
//------------------------------//

class MyPanel: public wxPanel
{
public:
    MyPanel(wxWindow *parent/*, const wxPoint &pos, const wxSize &size*/);
    ~MyPanel();
    void openImage(wxString fileName);
    void mirrorImage(bool boolean);
    void blurImage();
    void rotateImage(int rot);
    void negativeImage();
    void desaturateImage();
    void thresholdingImage();
    void mirrorMyImage(bool boolean);
    void rotate90MyImage(bool boolean);
    void rotateMyImage();
    void posterizeImage(unsigned char bitCount);
    void ditherImage();
    void countPixelColorImage();
    void enhenceContrastImage();
    void thresholdImage();
    void enhenceContrastDialog();
    void saveImage(wxString fileName);
    void initWebcam(IplImage* wframe);
    void treatmentWebcam();

    // SETTER //
    inline void setProcess(int i) {m_process = i;}
    void setBuffer(IplImage* wframe);
    void setValue(int i) {m_value = i;}

private:
    DECLARE_EVENT_TABLE()
    void OnThresholdImage(wxCommandEvent& event);
    void OnEnhenceImage(wxCommandEvent& event);
    void OnPaint(wxPaintEvent& event);
    MyImage *m_saveImage;
    MyImage *m_image;
    MyHistorogram *m_histogram;
    wxBitmap m_bitmap;
    int m_width;
    int m_height;
    int m_process;
    int m_value;
    unsigned char* m_buffer;

};


//------------------------------//
//         CLASS THREAD         //
//------------------------------//

class MyThread: public wxThread
{
public:
    MyThread(MyFrame *frame, MyPanel *panel);
    //~MyThread();
    void stopProcess();
    void negative();
protected:
    virtual wxThread::ExitCode Entry();
    MyFrame *m_frame;
    MyPanel *m_panel;
    CvCapture *m_capture;
    IplImage *m_wframe;
    bool m_process;
};

//------------------------------//
//          CLASS FRAME         //
//------------------------------//

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~MyFrame();
    void setCounter(long int i);
    void onWebcam(unsigned char* buffer, wxSize* size);
protected:
private:
    void OnHello(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnEnCours(wxCommandEvent& event);
    void OnLarge(wxCommandEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnOpenImage(wxCommandEvent& event);
    void OnStartCam(wxCommandEvent& event);
    void OnStopCam(wxCommandEvent& event);
    void OnProcessImage(wxCommandEvent& event);
    void OnProcessWebcam(wxCommandEvent& event);
    void OnSaveImage(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    DECLARE_EVENT_TABLE()
    MyPanel *m_panel;
    MyThread *m_thread;
};



//------------------------------//
//             ENUM             //
//------------------------------//

enum
{
    ID_Hello = 1,
    ID_About,
    ID_EnCours,
    ID_plusLarge,
    ID_moinsLarge, // 5
    ID_openImage,
    ID_mirrorImageHo,
    ID_mirrorImageVe,
    ID_blurImage,
    ID_rotateImageP90, // 10
    ID_rotateImageM90,
    ID_rotateImage180,
    ID_saveImage,
    ID_negativeImage,
    ID_desaturateImage, // 15
    ID_thresholdingImage,
    ID_mirrorMyImageHo,
    ID_mirrorMyImageVe,
    ID_rotateP90MyImage,
    ID_rotateM90MyImage, // 20
    ID_posterizeImage,
    ID_ditherImage,
    ID_rotateMyImage,
    ID_countPixelColor,
    ID_enhenceContrastImage, //25
    ID_enhenceContrastDialog,
    ID_startWebcam,
    ID_stopWebcam,
    ID_none,
    ID_mirror,
    ID_negativeWebcam,
    ID_rotate,
    ID_rotateWebp90,
    ID_rotateWebm90,
    ID_rotateWeb180,
    ID_desaturateWebcam,
    ID_thresholdingWebcam,
    ID_ditherWebcam,
    ID_posterizeWebcam
};


//------------------------------//
//          EVENT FRAME         //
//------------------------------//

BEGIN_EVENT_TABLE(MyFrame, wxFrame)

//  FILE    //
EVT_MENU(ID_Hello, MyFrame::OnHello)
EVT_MENU(ID_About, MyFrame::OnAbout)
EVT_MENU(ID_plusLarge, MyFrame::OnLarge)
EVT_MENU(ID_moinsLarge, MyFrame::OnLarge)
EVT_MENU(ID_openImage, MyFrame::OnOpenImage)
EVT_MENU(ID_saveImage, MyFrame::OnSaveImage)
EVT_MENU(ID_startWebcam, MyFrame::OnStartCam)
EVT_MENU(ID_stopWebcam, MyFrame::OnStopCam)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)

//  HELP    //
EVT_MENU(ID_EnCours, MyFrame::OnEnCours)

//  PROCESS //
EVT_MENU(ID_mirrorImageHo, MyFrame::OnProcessImage)
EVT_MENU(ID_mirrorImageVe, MyFrame::OnProcessImage)
EVT_MENU(ID_blurImage, MyFrame::OnProcessImage)
EVT_MENU(ID_rotateImageP90, MyFrame::OnProcessImage)
EVT_MENU(ID_rotateImageM90, MyFrame::OnProcessImage)
EVT_MENU(ID_rotateImage180, MyFrame::OnProcessImage)
EVT_MENU(ID_negativeImage, MyFrame::OnProcessImage)
EVT_MENU(ID_desaturateImage, MyFrame::OnProcessImage)
EVT_MENU(ID_thresholdingImage, MyFrame::OnProcessImage)
EVT_MENU(ID_mirrorMyImageHo, MyFrame::OnProcessImage)
EVT_MENU(ID_mirrorMyImageVe, MyFrame::OnProcessImage)
EVT_MENU(ID_rotateP90MyImage, MyFrame::OnProcessImage)
EVT_MENU(ID_rotateM90MyImage, MyFrame::OnProcessImage)
EVT_MENU(ID_posterizeImage, MyFrame::OnProcessImage)
EVT_MENU(ID_ditherImage, MyFrame::OnProcessImage)
EVT_MENU(ID_rotateMyImage, MyFrame::OnProcessImage)
EVT_MENU(ID_countPixelColor, MyFrame::OnProcessImage)
EVT_MENU(ID_enhenceContrastImage, MyFrame::OnProcessImage)
EVT_MENU(ID_enhenceContrastDialog, MyFrame::OnProcessImage)

//  WEBCAM  //
EVT_MENU(ID_none, MyFrame::OnProcessWebcam)
EVT_MENU(ID_mirror, MyFrame::OnProcessWebcam)
EVT_MENU(ID_negativeWebcam, MyFrame::OnProcessWebcam)
EVT_MENU(ID_rotate, MyFrame::OnProcessWebcam)
EVT_MENU(ID_desaturateWebcam, MyFrame::OnProcessWebcam)
EVT_MENU(ID_thresholdingWebcam, MyFrame::OnProcessWebcam)
EVT_MENU(ID_ditherWebcam, MyFrame::OnProcessWebcam)
EVT_MENU(ID_posterizeWebcam, MyFrame::OnProcessWebcam)


//  MOTION  //
EVT_MOTION(MyFrame::OnMouseMove)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

//------------------------------//
//          EVENT PANEL         //
//------------------------------//

BEGIN_EVENT_TABLE(MyPanel, wxPanel)
EVT_PAINT(MyPanel::OnPaint)
EVT_COMMAND(ID_THRESHOLD_SLIDER, wxEVT_MY_EVENT, MyPanel::OnThresholdImage)
EVT_COMMAND(ID_ENHENCE_SLIDER, wxEVT_MY_EVENT, MyPanel::OnEnhenceImage)
END_EVENT_TABLE()


//------------------------------//
//          MY PANEL            //
//------------------------------//

MyPanel::MyPanel(wxWindow *parent)
:wxPanel(parent), m_image()
{
    m_image = NULL;
    m_process = ID_none;
}

//////////////////////////////////////////////////////////////
MyPanel::~MyPanel()
{
    delete m_image;
}

//////////////////////////////////////////////////////////////
void MyPanel::OnPaint(wxPaintEvent& event)
{
    if (m_image != NULL)
    {
        wxPaintDC dc(this);
        m_bitmap = wxBitmap(*m_image);
        dc.DrawBitmap(m_bitmap,wxPoint(0,0));
    }
}

//////////////////////////////////////////////////////////////
void MyPanel::openImage(wxString fileName)
{
    if (m_image != NULL)
        delete m_image;
    m_image = new MyImage(fileName);
    m_histogram = new MyHistorogram(m_image);
    m_width = m_image->GetWidth();
    m_height = m_image->GetHeight()+50;
    GetParent()->SetSize(wxSize(m_width,m_height));
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::mirrorImage(bool boolean)
{
    if (m_image != NULL)
    {
        wxImage mumu = m_image->Mirror(boolean);
        delete m_image;
        m_image = new MyImage(mumu);
    }
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::blurImage()
{
    if (m_image != NULL)
    {
        wxImage mumu = m_image->Blur(1);
        delete m_image;
        m_image = new MyImage(mumu);
    }
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::rotateImage(int rot)
{
    if (m_image != NULL)
    {
        if (rot ==90 )
        {
            wxImage mumu = m_image->Rotate90(true);
            delete m_image;
            m_image = new MyImage(mumu);
        }
        else if (rot == -90)
        {
            wxImage mumu = m_image->Rotate90(false);
            delete m_image;
            m_image = new MyImage(mumu);
        }
        else
        {
            wxImage mumu = m_image->Rotate90(true).Rotate90(true);
            delete m_image;
            m_image = new MyImage(mumu);
        }
    }
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::negativeImage()
{
    if (m_image != NULL)
    {
        m_image->negative();
        Refresh();
    }
}

//////////////////////////////////////////////////////////////
void MyPanel::desaturateImage()
{
    if (m_image != NULL)
    {
        m_image->desaturate();
        Refresh();
    }
}

//////////////////////////////////////////////////////////////
void MyPanel::thresholdingImage()
{
    if (m_image != NULL)
    {
        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
        if (dlg->ShowModal() != wxID_CANCEL)
        {
            m_image->threshold(dlg->m_threshold->GetValue());
        }
        Refresh();
    }
}

//////////////////////////////////////////////////////////////
void MyPanel::mirrorMyImage(bool boolean)
{
    if (m_image != NULL)
    {
        m_image->mirror(boolean);
        Refresh();
    }
}


//////////////////////////////////////////////////////////////
void MyPanel::rotateMyImage()
{
    if (m_image != NULL)
    {
        MyRotateDialog *dlg = new MyRotateDialog(this,-2);
        if  (dlg->ShowModal() != wxID_CANCEL )
        {
            if (dlg->Rot90->GetValue())
            {
                wxImage mumu = m_image->Rotate90(true);
                delete m_image;
                m_image = new MyImage(mumu);
                m_width = m_image->GetWidth();
                m_height = m_image->GetHeight()+50;
                GetParent()->SetSize(wxSize(m_width,m_height));
            }
            else if (dlg->Rot180->GetValue())
            {
                wxImage mumu = m_image->Rotate90(true).Rotate90(true);
                delete m_image;
                m_image = new MyImage(mumu);
            }
            else
            {
                wxImage mumu = m_image->Rotate90(false);
                delete m_image;
                m_image = new MyImage(mumu);
                m_width = m_image->GetWidth();
                m_height = m_image->GetHeight()+50;
                GetParent()->SetSize(wxSize(m_width,m_height));
            }
        }
    }
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::rotate90MyImage(bool boolean)
{
    if (m_image != NULL)
    {
        wxImage mumu = m_image->Rotate90(boolean);
        delete m_image;
        m_image = new MyImage(mumu);
        m_width = m_image->GetWidth();
        m_height = m_image->GetHeight()+50;
        GetParent()->SetSize(wxSize(m_width,m_height));
    }
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::posterizeImage(unsigned char bitCount)
{
    if (m_image != NULL)
    {
        m_image->posterize(bitCount);
        Refresh();
    }
}

//////////////////////////////////////////////////////////////
void MyPanel::ditherImage()
{
    if (m_image != NULL)
    {
        wxImage mumu = m_image->dither();
        delete m_image;
        m_image = new MyImage(mumu);
    }
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::countPixelColorImage()
{
    if (m_image != NULL)
    {
        int color;
        color = m_image->countPixelColor();
        std::cout << "Color : " << color << std::endl;
        wxString  foo;
        foo.sprintf(wxT("Number of color : %d "),color);
        wxLogMessage(foo);
    }
}

//////////////////////////////////////////////////////////////
void MyPanel::enhenceContrastImage()
{
    if (m_image != NULL)
    {
        unsigned int * minValue;
        unsigned int * maxValue;
        minValue = (unsigned int*) malloc(sizeof(unsigned int));
        maxValue = (unsigned int*) malloc(sizeof(unsigned int));
        m_histogram->getBorderValues(minValue,maxValue);
        m_image->enhenceContrast(*minValue,*maxValue);
        m_histogram->reloadHistogram(m_image);
    }
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::thresholdImage()
{
    if (m_image != NULL)
    {
        m_saveImage = new MyImage(*m_image);
        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140)) ;
        if (dlg->ShowModal() != wxID_CANCEL)
        {
            m_image->threshold(dlg->m_threshold->GetValue());
        }
        else
        {
            *m_image = *m_saveImage;
        }
        Refresh();
        delete m_saveImage;
    }

}

//////////////////////////////////////////////////////////////
void MyPanel::enhenceContrastDialog()
{
    if (m_image != NULL)
    {
        m_saveImage = new MyImage(*m_image);
        MyEnhenceDialog *dlg = new MyEnhenceDialog(this, -1, wxT("Enhence"), wxDefaultPosition, wxSize(250,140));
        if (dlg->ShowModal() != wxID_CANCEL)
        {
            m_image->enhenceContrast(dlg->m_enhence->GetValue());
        }
        else
        {
            *m_image = *m_saveImage;
        }
        Refresh();
        delete m_saveImage;
    }
}

//////////////////////////////////////////////////////////////
void MyPanel::saveImage(wxString fileName)
{
    if (m_image != NULL)
        m_image->SaveFile(fileName,wxBITMAP_TYPE_BMP);
}

void MyPanel::initWebcam(IplImage* wframe)
{
    m_buffer = (unsigned char*) malloc(wframe->height*wframe->width*3);
    IplImageToBuffer(wframe,m_buffer);
    m_image = new MyImage(m_buffer,wframe->height,wframe->width);
    m_width = wframe->width;
    m_height = wframe->height+50;
    GetParent()->SetSize(wxSize(m_width,m_height));
}

//////////////////////////////////////////////////////////////
void MyPanel::setBuffer(IplImage* wframe)
{
    m_buffer = (unsigned char*) malloc(wframe->height*wframe->width*3);
    IplImageToBuffer(wframe,m_buffer);
}

//////////////////////////////////////////////////////////////
void MyPanel::treatmentWebcam()
{
    m_image->SetData(m_buffer);
    switch(m_process)
    {
    case ID_none:
        break;
    case ID_mirrorMyImageHo:
        m_image->mirror(true);
        break;
    case ID_mirrorMyImageVe:
        m_image->mirror(false);
        break;
    case ID_negativeWebcam:
        m_image->negative();
        break;
    case ID_rotateWebp90:
        m_image->rotateTest(true);
        break;
    case ID_rotateWeb180:
        m_image->rotate90(true);
        m_image->rotate90(true);
        break;
    case ID_rotateWebm90:
        m_image->rotateTest(false);
        break;
    case ID_desaturateWebcam:
        m_image->desaturate();
        break;
    case ID_thresholdingWebcam:
        m_image->threshold(m_value);
        break;
    case ID_ditherWebcam:
        m_image->ditherTest();
        break;
    case ID_posterizeWebcam:
        m_image->posterize(m_value);
        break;
    }
    Refresh();
}

//------------------------------//
//       MY PANEL EVENT         //
//------------------------------//

//////////////////////////////////////////////////////////////
void MyPanel::OnThresholdImage(wxCommandEvent& event)
{
    *m_image = *m_saveImage;
    m_image->threshold(event.GetInt());
    Refresh();
}

//////////////////////////////////////////////////////////////
void MyPanel::OnEnhenceImage(wxCommandEvent& event)
{
    *m_image = *m_saveImage;
    m_image->enhenceContrast(event.GetInt());
    Refresh();
}

//------------------------------//
//          MY APP              //
//------------------------------//

bool MyApp::OnInit()
{
    wxInitAllImageHandlers();
    MyFrame *frame = new MyFrame(wxT("Hey Bro !"), wxPoint(50,50), wxSize(450,340));
    frame->Show(true);
    return true;
}


//------------------------------//
//          MY FRAME            //
//------------------------------//

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
:wxFrame(NULL, wxID_ANY, title, pos, size)
{
    m_panel = new MyPanel(this/*,pos,size*/);
    this->CenterOnScreen();
    this->CreateStatusBar();
    this->SetStatusText(wxT("Work"));
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, wxT("Hey!...\tCtrl-H"), wxT("Heeeeeeeelp !"));
    menuFile->Append(ID_plusLarge,wxT("+ Large...\t"));
    menuFile->Append(ID_moinsLarge,wxT("- Large...\t"));
    menuFile->Append(ID_openImage,wxT("Open Image...\tCtrl-O"));
    menuFile->Append(ID_saveImage,wxT("Save Image...\tCtrl-S"));
    menuFile->Append(ID_startWebcam,wxT("Start Webcam...\tCtrl-W"));
    menuFile->Append(ID_stopWebcam,wxT("Stop Webcam...\t"));
    menuFile->AppendSeparator();
    menuFile->Append(ID_About,wxT("About...\t"));
    menuFile->Append((wxID_EXIT));


    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(ID_EnCours, wxT("En Cours...\t"));

    wxMenu *menuProcess = new wxMenu;
    menuProcess->Append(ID_mirrorImageHo, wxT("Mirror image Ho...\t"));
    menuProcess->Append(ID_mirrorImageVe, wxT("Mirror image Ve...\t"));
    menuProcess->Append(ID_blurImage, wxT("Blur image...\tCtrl-B"));
    menuProcess->Append(ID_rotateImageP90, wxT("Rotate image +90...\t"));
    menuProcess->Append(ID_rotateImageM90, wxT("Rotate image -90...\t"));
    menuProcess->Append(ID_rotateImage180, wxT("Rotate image 180...\t"));
    menuProcess->Append(ID_negativeImage, wxT("Negative image...\t"));
    menuProcess->Append(ID_desaturateImage, wxT("Desaturate image...\t"));
    menuProcess->Append(ID_thresholdingImage, wxT("Thresholding image...\t"));
    menuProcess->Append(ID_mirrorMyImageHo, wxT("My Mirror image Ho...\t"));
    menuProcess->Append(ID_mirrorMyImageVe, wxT("My Mirror image Ve...\t"));
    menuProcess->Append(ID_rotateP90MyImage, wxT("My Rotate image +90...\t"));
    menuProcess->Append(ID_rotateM90MyImage, wxT("My Rotate image -90...\t"));
    menuProcess->Append(ID_posterizeImage, wxT("Posterize image...\t"));
    menuProcess->Append(ID_ditherImage, wxT("Dither x8 Image...\t"));
    menuProcess->Append(ID_rotateMyImage, wxT("Rotate my image...\t"));
    menuProcess->Append(ID_countPixelColor, wxT("Count Pixel Color Image...\t"));
    menuProcess->Append(ID_enhenceContrastImage, wxT("Enhence Contrast Image...\t"));
    menuProcess->Append(ID_enhenceContrastDialog, wxT("Enhence Contrast Dialog...\t"));

    wxMenu *menuWebcam = new wxMenu;
    menuWebcam->Append(ID_none, wxT("Stop Process...\tCtrl-P"));
    menuWebcam->AppendSeparator();
    menuWebcam->Append(ID_mirror, wxT("Mirror...\t"));
    menuWebcam->Append(ID_negativeWebcam, wxT("Negative...\t"));
    menuWebcam->Append(ID_rotate, wxT("Rotate...\t"));
    menuWebcam->Append(ID_desaturateWebcam, wxT("Desaturate...\t"));
    menuWebcam->Append(ID_thresholdingWebcam, wxT("Thresholding...\t"));
    menuWebcam->Append(ID_ditherWebcam, wxT("Dither...\t"));
    menuWebcam->Append(ID_posterizeWebcam, wxT("Posterize...\t"));

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, wxT("File"));
    menuBar->Append(menuHelp,wxT("Help"));
    menuBar->Append(menuProcess,wxT("Process"));
    menuBar->Append(menuWebcam,wxT("Webcam"));
    SetMenuBar(menuBar);


    ////////////
    // THREAD //
    ////////////

    m_thread = NULL;
}

//////////////////////////////////////////////////////////////
MyFrame::~MyFrame()
{
}

//////////////////////////////////////////////////////////////
void MyFrame::setCounter(long int i)
{
    wxString str;
    str.sprintf(wxT("%ld"),i);
    this->SetStatusText(str);
}

//////////////////////////////////////////////////////////////
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage(wxT("Hey bro' !"));
}

//////////////////////////////////////////////////////////////
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxLogMessage(wxT("Author : Cookie Man - 2014"));
}

//////////////////////////////////////////////////////////////
void MyFrame::OnEnCours(wxCommandEvent& event)
{
    wxLogMessage(wxT("Work in progress"));
}

//////////////////////////////////////////////////////////////
void MyFrame::OnLarge(wxCommandEvent& event)
{
    int* width = new int;
    int* height = new int;
    GetSize(width,height);
    if (event.GetId() == 4)
    {
        if (*width+100 < 1600 )
        {
            SetSize(*width+100,*height+100);
        }
    }
    else
    {
       if (*width-100 > 200 )
        {
            SetSize(*width-100,*height-100);
        }
    }

}

//////////////////////////////////////////////////////////////
void MyFrame::OnMouseMove(wxMouseEvent& event)
{
    wxString  foo;
    foo.sprintf(wxT("X : %d Y : %d"),event.m_x,event.m_y);
    this->SetStatusText(foo);
}

//////////////////////////////////////////////////////////////
void MyFrame::OnOpenImage(wxCommandEvent& event)
{
    wxString fileName = wxFileSelector(wxT("Choose a image to open"));
    if (!fileName.empty())
    {
        m_panel->openImage(fileName);
    }
}

//////////////////////////////////////////////////////////////
void MyFrame::OnStartCam(wxCommandEvent& event)
{
    ////////////
    // THREAD //
    ////////////

    m_thread = new MyThread(this,m_panel);
    m_thread->Create();
    m_thread->SetPriority(50);
    if (m_thread->Run() != wxTHREAD_NO_ERROR )
    {
        wxLogError(wxT("Can't create the thread!"));
        delete m_thread;
        m_thread = NULL;
    }

    //m_thread->Create();
    //m_thread->SetPriority(50);
    //if (m_thread->Run() != wxTHREAD_NO_ERROR)
    //{
     //wxLogError(wxT("Can't create the thread dude!"));
     //delete m_thread;
     //m_thread = NULL;
    //}
}

void MyFrame::OnStopCam(wxCommandEvent& event)
{
    if (m_thread->IsRunning())
    {
        m_thread->Pause();
        wxMessageOutputDebug().Printf(wxT("MYFRAME: deleting thread"));
        /*if (m_thread->Delete() != wxTHREAD_NO_ERROR)
        {
            std::cout << "can't delete the thread!" << std::endl;
        }*/
    }
}

//////////////////////////////////////////////////////////////
void MyFrame::OnProcessImage(wxCommandEvent& event)
{
    clock_t t;
    t = clock();
    switch(event.GetId())
    {
    case 7: // Mirror Hor
        m_panel->mirrorImage(true);
        break;
    case 8: // Mirror Ver
        m_panel->mirrorImage(false);
        break;
    case 9: // Blur
        m_panel->blurImage();
        break;
    case 10: // Rotate +90
        m_panel->rotateImage(90);
        break;
    case 11: // Rotate -90
        m_panel->rotateImage(-90);
        break;
    case 12: // Rotate +180
        m_panel->rotateImage(180);
        break;
    case 14: // Negative
        m_panel->negativeImage();
        break;
    case 15: // Desaturate
        m_panel->desaturateImage();
        break;
    case 16: // Thresholding
        m_panel->thresholdImage();
        break;
    case 17: // My Mirror Hor
        m_panel->mirrorMyImage(true);
        break;
    case 18: // My Mirror Ver
        m_panel->mirrorMyImage(false);
        break;
    case 19: // My Rotate +90
        m_panel->rotate90MyImage(true);
        break;
    case 20: // My Rotate -90
        m_panel->rotate90MyImage(false);
        break;
    case 21: // Posterize
        m_panel->posterizeImage('2');
        break;
    case 22: // Dither x8
        m_panel->ditherImage();
        break;
    case 23: // Rotate My Image
        m_panel->rotateMyImage();
        break;
    case 24: // Count Pixel Color Image
        m_panel->countPixelColorImage();
        break;
    case 25: // Enhence Contrast Image
        m_panel->enhenceContrastImage();
        break;
    case 26: // Enhence Contrast Dialog
        m_panel->enhenceContrastDialog();
        break;
    }
    t = clock()-t;
    wxString foo;
    foo.sprintf(wxT("Temps écoulé : %f"),((float)t)/CLOCKS_PER_SEC);
    SetStatusText(foo);
}

//////////////////////////////////////////////////////////////
void MyFrame::OnProcessWebcam(wxCommandEvent& event)
{
    MyMirrorDialog *dlgMirror = new MyMirrorDialog(this,-3);
    MyRotateDialog *dlgRotate = new MyRotateDialog(this,-2);
    MyThresholdDialog *dlgThre = new MyThresholdDialog(this,-4);
    MyPosterizeDialog *dlgPost = new MyPosterizeDialog(this,-5);
    switch(event.GetId())
    {
    case ID_none: // Stop any process on Webcam
        m_panel->setProcess(ID_none);
        break;
    case ID_mirror:
        if  (dlgMirror->ShowModal() != wxID_CANCEL )
        {
            if (dlgMirror->RadioButtonHor->GetValue()) {m_panel->setProcess(ID_mirrorMyImageHo);} else {m_panel->setProcess(ID_mirrorMyImageVe);}
        }
        //delete dlg;
        break;
    case ID_negativeWebcam: // Negative Webcam
        m_panel->setProcess(ID_negativeWebcam);
        break;
    case ID_rotate:
        if (dlgRotate->ShowModal() != wxID_CANCEL)
        {
            if (dlgRotate->Rot90->GetValue())
            {
                m_panel->setProcess(ID_rotateWebp90);
            }
            else if (dlgRotate->Rot180->GetValue())
            {
                m_panel->setProcess(ID_rotateWeb180);
            }
            else
            {
                m_panel->setProcess(ID_rotateWebm90);
            }
        }
        break;
    case ID_desaturateWebcam:
        m_panel->setProcess(ID_desaturateWebcam);
        break;
    case ID_thresholdingWebcam:
        if (dlgThre->ShowModal() != wxID_CANCEL)
        {
            m_panel->setValue(dlgThre->m_threshold->GetValue());
            m_panel->setProcess(ID_thresholdingWebcam);
        }
        break;
    case ID_ditherWebcam:
        m_panel->setProcess(ID_ditherWebcam);
        break;
    case ID_posterizeWebcam:
        if (dlgPost->ShowModal() != wxID_CANCEL)
        {
            m_panel->setValue(dlgPost->m_posterize->GetValue());
            m_panel->setProcess(ID_posterizeWebcam);
        }
        break;
    }
}

//////////////////////////////////////////////////////////////
void MyFrame::OnSaveImage(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, wxT("Save XYZ file"), wxT(""), wxT(""),wxT("XYZ files (*.BMP)"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    m_panel->saveImage(saveFileDialog.GetPath());
}

//////////////////////////////////////////////////////////////
void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


//------------------------------//
//          MY THREAD           //
//------------------------------//

//////////////////////////////////////////////////////////////
MyThread::MyThread(MyFrame *frame, MyPanel *panel)
//: wxThread(wxTHREAD_DETACHED)
{
    m_frame = frame;
    m_panel = panel;
}

//////////////////////////////////////////////////////////////
/*MyThread::~MyThread()
{
    m_frame = NULL;
}*/


//////////////////////////////////////////////////////////////
wxThread::ExitCode MyThread::Entry()
{
    m_capture = cvCaptureFromCAM(0);
    std::cout << "Create" << std::endl;
    if (!m_capture)
    {
        fprintf(stderr, "Cannot initialize webcam!\n");
    }
    else
    {
        m_wframe = cvQueryFrame(m_capture);
        m_panel->initWebcam(m_wframe);
        while(!TestDestroy())
        {
            m_wframe = cvQueryFrame(m_capture);
            while (m_wframe)
            {
                wxMutexGuiEnter();
                m_panel->setBuffer(m_wframe);
                m_panel->treatmentWebcam();
                wxMutexGuiLeave();
                m_wframe = cvQueryFrame(m_capture);
            }
            if (!m_wframe)
            {
                fprintf(stderr, "Cannot acquire frame!\n");
            }
        }
    }
    cvReleaseCapture(&m_capture);
    std::cout << "dead" << std::endl;
    return (wxThread::ExitCode)0;
}



//------------------------------------------------------------------------
void IplImageToBuffer(IplImage* iImage, unsigned char* buffer)
//------------------------------------------------------------------------
// Parameters: an existing IplImage and an already allocated buffer
// This function fills the buffer with the pixels of the IplImage
// IPL image are BGR coded instead of RGB
{
	int h, w ;
	unsigned char* source = (unsigned char*)iImage->imageData ;
	unsigned char* saveSource ;
	unsigned char* dest = buffer ;

	if (iImage->nChannels == 1)
	{
		for (h=0; h<iImage->height; h++)
		{
			memcpy(dest, source, iImage->width) ;
			source += iImage->widthStep ;
			dest += iImage->width ;
		}
	}
	else if (iImage->nChannels == 3)
	{
		for (h=0; h<iImage->height; h++)
		{
			saveSource = source ;

			for (w=0; w<iImage->width; w++)
			{
				*(dest++) = *(source+2) ; // copy and change the BGR order
				*(dest++) = *(source+1) ;
				*(dest++) = *source ;
				source+=3 ;
			}
			source = saveSource + iImage->widthStep ;
		}
	}
}

//------------------------------------------------------------------------
void BufferToIplImage(unsigned char* buffer, IplImage* iImage)
//------------------------------------------------------------------------
// Parameters: a buffer storing an image and an already allocated IplImage
// This function fills the IplImage with the pixels of the buffer
{
	int h, w ;
	unsigned char* source = buffer  ;
	char* dest = iImage->imageData ;
	char* saveDest ;

	if (iImage->nChannels == 1)
	{
		for (h=0; h<iImage->height; h++)
		{
			memcpy(dest, source, iImage->width) ;
			source += iImage->width ;
			dest += iImage->widthStep ;
		}
	}
	else if (iImage->nChannels == 3)
	{
		for (h=0; h<iImage->height; h++)
		{
			saveDest = dest ;
			for (w=0; w<iImage->width; w++)
			{
				*(dest++) = *(source+2) ; // copy and change the RGB order
				*(dest++) = *(source+1) ;
				*(dest++) = *source ;
				source+=3 ;
			}
			dest = saveDest + iImage->widthStep ;
		}
	}
}
