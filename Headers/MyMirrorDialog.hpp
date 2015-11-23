#include <wx/wxprec.h>
#include <stdlib.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif // WX_PRECOMP


class MyMirrordDialog : public wxDialog
{
public:
	MyThresholdDialog( wxWindow* parent, wxWindowID id = wxID_ANY,
    const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
private:
    void OnScroll(wxCommandEvent& event);
	wxButton* m_okButton;
	DECLARE_EVENT_TABLE()
};
