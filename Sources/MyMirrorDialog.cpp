#include "MyMirrorDialog.h"

//(*InternalHeaders(MyMirrorDialog)
#include <wx/string.h>
#include <wx/intl.h>
//*)

//(*IdInit(MyMirrorDialog)
const long MyMirrorDialog::ID_RADIOBUTTONHOR = wxNewId();
const long MyMirrorDialog::ID_RADIOBUTTONVER = wxNewId();
//*)

BEGIN_EVENT_TABLE(MyMirrorDialog,wxDialog)
	//(*EventTable(MyMirrorDialog)
	//*)
END_EVENT_TABLE()

MyMirrorDialog::MyMirrorDialog(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(MyMirrorDialog)
	Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(336,158));
	RadioButtonHor = new wxRadioButton(this, ID_RADIOBUTTONHOR, _("Horizontal"), wxPoint(56,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTONHOR"));
	RadioButtonVer = new wxRadioButton(this, ID_RADIOBUTTONVER, _("Vertical"), wxPoint(200,48), wxDefaultSize, 0, wxDefaultValidator, _T("ID_RADIOBUTTONVER"));
	ButtonOk = new wxButton(this, wxID_OK, _("OK"), wxPoint(48,104), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
	ButtonCancel = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(200,104), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

	Connect(ID_RADIOBUTTONHOR,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&MyMirrorDialog::OnRadioButton1Select);
	//*)
}

MyMirrorDialog::~MyMirrorDialog()
{
	//(*Destroy(MyMirrorDialog)
	//*)
}


void MyMirrorDialog::OnRadioButton1Select(wxCommandEvent& event)
{
}
