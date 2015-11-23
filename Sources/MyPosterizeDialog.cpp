#include "MyPosterizeDialog.hpp"

//------------------------------//
//          EVENT DIALOG        //
//------------------------------//

BEGIN_EVENT_TABLE(MyPosterizeDialog, wxDialog)
EVT_SLIDER(ID_POSTERIZE_SLIDER, MyPosterizeDialog::OnScroll)
END_EVENT_TABLE()

//////////////////////////////////////////////////////////////
MyPosterizeDialog::MyPosterizeDialog(
	wxWindow* parent, wxWindowID id, const wxString& title,
	const wxPoint& pos, const wxSize& size, long style )
: wxDialog( parent, id, title, pos, size, style )
{
	m_posterize = new wxSlider( this, ID_POSTERIZE_SLIDER, 8, 0, 8, wxPoint(20,10), wxSize(140,-1), wxSL_HORIZONTAL|wxSL_LABELS );
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(20,70), wxDefaultSize, 0 );
}

//////////////////////////////////////////////////////////////
void MyPosterizeDialog::OnScroll(wxCommandEvent& event)
{
    wxCommandEvent outEvent(wxEVT_MY_EVENT, ID_POSTERIZE_SLIDER);
    outEvent.SetInt(m_posterize->GetValue());
    wxPostEvent(GetParent(), outEvent);
}
