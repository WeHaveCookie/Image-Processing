#include "MyRotateDialog.h"

//(*InternalHeaders(MyRotateDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(MyRotateDialog)
const long MyRotateDialog::ID_RADIOBUTTON1 = wxNewId();
const long MyRotateDialog::ID_RADIOBUTTON2 = wxNewId();
const long MyRotateDialog::ID_RADIOBUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(MyRotateDialog,wxDialog)
	//(*EventTable(MyRotateDialog)
	//*)
END_EVENT_TABLE()

MyRotateDialog::MyRotateDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(MyRotateDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(263,302));
	Rot90 = new wxRadioButton(this, ID_RADIOBUTTON1, _("90°"), wxPoint(72,72), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON1"));
	Rot180 = new wxRadioButton(this, ID_RADIOBUTTON2, _("180°"), wxPoint(72,120), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON2"));
	RadioButton1 = new wxRadioButton(this, ID_RADIOBUTTON3, _("-90°"), wxPoint(72,168), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTON3"));
	ButtonOk = new wxButton(this, wxID_OK, _("OK"), wxPoint(48,240), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(168,240), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

	//*)
}

MyRotateDialog::~MyRotateDialog()
{
	//(*Destroy(MyRotateDialog)
	//*)
}


