#include <wx/wxprec.h>
#include <stdlib.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif // WX_PRECOMP
#define ID_ENHENCE_SLIDER 1001

DECLARE_EVENT_TYPE(wxEVT_MY_EVENT,-1)

class MyEnhenceDialog : public wxDialog
{
public:
	wxSlider* m_enhence;
	MyEnhenceDialog( wxWindow* parent, wxWindowID id = wxID_ANY,
    const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
private:
    void OnScroll(wxCommandEvent& event);
	wxButton* m_okButton;
	DECLARE_EVENT_TABLE()
};
