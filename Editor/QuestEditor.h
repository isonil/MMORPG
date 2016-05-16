#ifndef QUESTEDITOR_H
#define QUESTEDITOR_H

//(*Headers(QuestEditor)
#include <wx/listctrl.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)
#include "source/Editor.hpp"
#include "source/Classes.hpp"

class QuestEditor: public wxDialog
{
	public:

		QuestEditor(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~QuestEditor();

		//(*Declarations(QuestEditor)
		wxSpinCtrl* wxQuestProgressTo;
		wxButton* Button1;
		wxTextCtrl* wxText;
		wxBitmapButton* BitmapButton2;
		wxBitmapButton* BitmapButton1;
		wxButton* Button2;
		wxStaticLine* StaticLine2;
		wxStaticLine* StaticLine1;
		wxListCtrl* wxQuestProgressText;
		wxPanel* Panel2;
		wxSpinCtrl* wxQuestProgressFrom;
		//*)
		QuestClass editingQuest;

	protected:

		//(*Identifiers(QuestEditor)
		static const long ID_BITMAPBUTTON1;
		static const long ID_QUEST_PROGRESS_FROM;
		static const long ID_QUEST_PROGRESS_TO;
		static const long ID_BITMAPBUTTON2;
		static const long ID_QUEST_PROGESS_TEXT;
		static const long ID_TEXT;
		static const long ID_STATICLINE2;
		static const long ID_PANEL2;
		static const long ID_STATICLINE1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)

	private:

		//(*Handlers(QuestEditor)
		void OnButton1Click(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnBitmapButton1Click(wxCommandEvent& event);
		void OnBitmapButton2Click(wxCommandEvent& event);
		void OnwxTextText(wxCommandEvent& event);
		void OnwxQuestProgressTextItemSelect(wxListEvent& event);
		void OnwxQuestProgressTextItemDeselect(wxListEvent& event);
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
