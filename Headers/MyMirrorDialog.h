#ifndef MYMIRRORDIALOG_H
#define MYMIRRORDIALOG_H

//(*Headers(MyMirrorDialog)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/radiobut.h>
//*)

class MyMirrorDialog: public wxDialog
{
	public:

		MyMirrorDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~MyMirrorDialog();

		//(*Declarations(MyMirrorDialog)
		wxRadioButton* RadioButtonVer;
		wxRadioButton* RadioButtonHor;
		wxButton* ButtonCancel;
		wxButton* ButtonOk;
		//*)

	protected:

		//(*Identifiers(MyMirrorDialog)
		static const long ID_RADIOBUTTONHOR;
		static const long ID_RADIOBUTTONVER;
		//*)

	private:

		//(*Handlers(MyMirrorDialog)
		void OnRadioButton1Select(wxCommandEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
