#include "MyEnhenceDialog.hpp"

//------------------------------//
//          EVENT DIALOG        //
//------------------------------//

BEGIN_EVENT_TABLE(MyEnhenceDialog, wxDialog)
EVT_SLIDER(ID_ENHENCE_SLIDER, MyEnhenceDialog::OnScroll)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////
MyEnhenceDialog::MyEnhenceDialog(
	wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style )
: wxDialog( parent, id, title, pos, size, style )
{
	m_enhence = new wxSlider( this, ID_ENHENCE_SLIDER, 0, -127, 127, wxPoint(20,10), wxSize(140,-1), wxSL_HORIZONTAL|wxSL_LABELS );
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(20,70), wxDefaultSize, 0 );
}

//////////////////////////////////////////////////////////////
void MyEnhenceDialog::OnScroll(wxCommandEvent& event)
{
    wxCommandEvent outEvent(wxEVT_MY_EVENT, ID_ENHENCE_SLIDER);
    outEvent.SetInt(m_enhence->GetValue());
    wxPostEvent(GetParent(), outEvent);
}
