#include "ThresholdDialog.h"

//(*InternalHeaders(ThresholdDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(ThresholdDialog)
const long ThresholdDialog::ID_SLIDER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ThresholdDialog,wxDialog)
	//(*EventTable(ThresholdDialog)
	//*)
END_EVENT_TABLE()

ThresholdDialog::ThresholdDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(ThresholdDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(276,148));
	Slider1 = new wxSlider(this, ID_SLIDER1, 0, 0, 100, wxPoint(112,32), wxDefaultSize, wxSL_HORIZONTAL|wxSL_LABELS, wxDefaultValidator, _T("ID_SLIDER1"));
	ButtonOK = new wxButton(this, wxID_OK, _("OK"), wxPoint(24,96), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(152,96), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

	//*)
}

ThresholdDialog::~ThresholdDialog()
{
	//(*Destroy(ThresholdDialog)
	//*)
}

