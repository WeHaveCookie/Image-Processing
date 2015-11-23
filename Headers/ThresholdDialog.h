#ifndef THRESHOLDDIALOG_H
#define THRESHOLDDIALOG_H

//(*Headers(ThresholdDialog)
#include <wx/dialog.h>
#include <wx/button.h>
#include <wx/slider.h>
//*)

class ThresholdDialog: public wxDialog
{
	public:

		ThresholdDialog(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~ThresholdDialog();

		//(*Declarations(ThresholdDialog)
		wxButton* ButtonOK;
		wxButton* ButtonCancel;
		wxSlider* Slider1;
		//*)

	protected:

		//(*Identifiers(ThresholdDialog)
		static const long ID_SLIDER1;
		//*)

	private:

		//(*Handlers(ThresholdDialog)
		void OnButton1Click(wxCommandEvent& event);
		void OnButtonOKClick(wxCommandEvent& event);
		void OnButtonCancelClick(wxCommandEvent& event);
		void OnSlider1CmdScroll(wxScrollEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
