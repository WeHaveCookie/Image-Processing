#ifndef MYROTATEDIALOG_H
#define MYROTATEDIALOG_H

//(*Headers(MyRotateDialog)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/radiobut.h>
//*)

class MyRotateDialog: public wxDialog
{
	public:

		MyRotateDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~MyRotateDialog();

		//(*Declarations(MyRotateDialog)
		wxRadioButton* Rot90;
		wxRadioButton* RadioButton1;
		wxButton* ButtonCancel;
		wxButton* ButtonOk;
		wxRadioButton* Rot180;
		//*)

	protected:

		//(*Identifiers(MyRotateDialog)
		static const long ID_RADIOBUTTON1;
		static const long ID_RADIOBUTTON2;
		static const long ID_RADIOBUTTON3;
		//*)

	private:

		//(*Handlers(MyRotateDialog)
		void OnRadioButton1Select(wxCommandEvent& event);
		void OnRadioButton1Select1(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		void OnRadioButton2Select(wxCommandEvent& event);
		void OnRadioButton3Select(wxCommandEvent& event);
		void OnInit(wxInitDialogEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
