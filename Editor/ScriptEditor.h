#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

//(*Headers(ScriptEditor)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/html/htmlwin.h>
//*)

#include <wx/stc/stc.h>

class ScriptEditor: public wxDialog
{
	public:

		ScriptEditor(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~ScriptEditor();

		//(*Declarations(ScriptEditor)
		wxNotebook* Notebook1;
		wxStyledTextCtrl* styledTextCtrl;
		wxButton* Button1;
		wxPanel* Panel1;
		wxStaticText* StaticText1;
		wxButton* Button2;
		wxHtmlWindow* HtmlWindow1;
		wxTextCtrl* TextCtrl2;
		wxPanel* Panel2;
		//*)

	protected:

		//(*Identifiers(ScriptEditor)
		static const long ID_CUSTOM1;
		static const long ID_TEXTCTRL2;
		static const long ID_PANEL1;
		static const long ID_HTMLWINDOW1;
		static const long ID_PANEL2;
		static const long ID_NOTEBOOK1;
		static const long ID_BUTTON1;
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(ScriptEditor)
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		//*)
		void OnStyledTextCtrlKeyPressed(wxStyledTextEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif
