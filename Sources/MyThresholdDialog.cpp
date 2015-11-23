#include "MyThresholdDialog.hpp"

//------------------------------//
//          EVENT DIALOG        //
//------------------------------//

BEGIN_EVENT_TABLE(MyThresholdDialog, wxDialog)
EVT_SLIDER(ID_THRESHOLD_SLIDER, MyThresholdDialog::OnScroll)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////
MyThresholdDialog::MyThresholdDialog(
	wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style )
: wxDialog( parent, id, title, pos, size, style )
{
	m_threshold = new wxSlider( this, ID_THRESHOLD_SLIDER, 128, 0, 255, wxPoint(20,10), wxSize(140,-1), wxSL_HORIZONTAL|wxSL_LABELS );
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(20,70), wxDefaultSize, 0 );
}

//////////////////////////////////////////////////////////////
void MyThresholdDialog::OnScroll(wxCommandEvent& event)
{
    wxCommandEvent outEvent(wxEVT_MY_EVENT, ID_THRESHOLD_SLIDER);
    outEvent.SetInt(m_threshold->GetValue());
    wxPostEvent(GetParent(), outEvent);
}
