#ifndef NPCTYPEEDITOR_H
#define NPCTYPEEDITOR_H

//(*Headers(NPCTypeEditor)
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/listbox.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/radiobut.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/dialog.h>
//*)

#include <vector>
#include "source/Classes.hpp"

class NPCTypeEditor: public wxDialog
{
	public:

		NPCTypeEditor(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~NPCTypeEditor();

		//(*Declarations(NPCTypeEditor)
		wxStaticText* StaticText10;
		wxStaticText* StaticText9;
		wxSpinCtrl* wxDialogueQuestProgressTo;
		wxSpinCtrl* wxDialogueGoToBlockNumber;
		wxListBox* wxTrade;
		wxChoice* wxLootAddObjectType;
		wxTreeCtrl* wxDialogue;
		wxPanel* Panel5;
		wxSpinCtrl* wxLootAddObjectQuantityFrom;
		wxButton* Button4;
		wxChoice* wxVest;
		wxNotebook* Notebook1;
		wxSpinCtrl* wxLootAddObjectQuantityTo;
		wxChoice* wxHelmet;
		wxStaticText* StaticText13;
		wxStaticText* StaticText2;
		wxPanel* Panel4;
		wxChoice* wxDialogueQuest;
		wxButton* Button1;
		wxSpinCtrl* wxDialogueBlockNumber;
		wxListCtrl* wxLoot;
		wxSpinCtrl* wxDialogueQuestProgressFrom;
		wxStaticText* StaticText8;
		wxStaticText* StaticText11;
		wxChoice* wxWeapon;
		wxRadioButton* wxDialogueStartTrade;
		wxSpinCtrl* wxMaxHealth;
		wxBitmapButton* BitmapButton2;
		wxPanel* Panel1;
		wxStaticText* StaticText3;
		wxStaticBox* StaticBox1;
		wxBitmapButton* BitmapButton1;
		wxSpinCtrl* wxTeam;
		wxButton* Button2;
		wxPanel* Panel6;
		wxPanel* Panel3;
		wxButton* Button6;
		wxChoice* wxGloves;
		wxStaticBox* StaticBox2;
		wxButton* Button5;
		wxRadioButton* wxDialogueGoToBlock;
		wxButton* Button3;
		wxButton* Button7;
		wxStaticText* StaticText7;
		wxSpinCtrl* wxLootAddObjectChance;
		wxChoice* wxDialogueScript;
		wxTextCtrl* wxDialogueText;
		wxBitmapButton* BitmapButton4;
		wxStaticText* StaticText15;
		wxStaticText* StaticText12;
		wxBitmapButton* BitmapButton3;
		wxPanel* Panel2;
		wxTextCtrl* wxName;
		wxChoice* wxTradeAddObjectType;
		wxStaticText* StaticText17;
		wxStaticText* StaticText4;
		wxChoice* wxBoots;
		wxStaticText* StaticText16;
		//*)
		int *indexes;
		int negativeIndex;
		std::vector <NPCTypeClass::DialogueBlockClass> editingDialogueBlock;
		int currentBlockIndex;
		int currentOptionIndex;
		wxTreeItemId treeRootId;

	protected:

		//(*Identifiers(NPCTypeEditor)
		static const long ID_STATICTEXT2;
		static const long ID_NAME;
		static const long ID_STATICTEXT4;
		static const long ID_MAX_HEALTH;
		static const long ID_STATICTEXT3;
		static const long ID_TEAM;
		static const long ID_PANEL1;
		static const long ID_STATICTEXT7;
		static const long ID_WEAPON;
		static const long ID_STATICTEXT8;
		static const long ID_HELMET;
		static const long ID_STATICTEXT9;
		static const long ID_VEST;
		static const long ID_STATICTEXT10;
		static const long ID_BOOTS;
		static const long ID_STATICTEXT11;
		static const long ID_GLOVES;
		static const long ID_PANEL2;
		static const long ID_PANEL3;
		static const long ID_BITMAPBUTTON1;
		static const long ID_BITMAPBUTTON2;
		static const long ID_LOOT_ADD_OBJECT_TYPE;
		static const long ID_LOOT_ADD_OBJECT_QUANTITY_FROM;
		static const long ID_LOOT_ADD_OBJECT_CHANCE;
		static const long ID_LOOT_ADD_OBJECT_QUANTITY_TO;
		static const long ID_LOOT;
		static const long ID_PANEL4;
		static const long ID_TRADE;
		static const long ID_BITMAPBUTTON3;
		static const long ID_BITMAPBUTTON4;
		static const long ID_TRADE_ADD_OBJECT_TYPE;
		static const long ID_PANEL5;
		static const long ID_DIALOGUE_TEXT;
		static const long ID_BUTTON2;
		static const long ID_BUTTON3;
		static const long ID_STATICTEXT12;
		static const long ID_STATICTEXT13;
		static const long ID_DIALOGUE_START_TRADE;
		static const long ID_DIALOGUE_GO_TO_BLOCK;
		static const long ID_STATICBOX1;
		static const long ID_STATICTEXT15;
		static const long ID_DIALOGUE_BLOCK_NUMBER;
		static const long ID_STATICBOX2;
		static const long ID_DIALOGUE_GO_TO_BLOCK_NUMBER;
		static const long ID_STATICTEXT16;
		static const long ID_STATICTEXT17;
		static const long ID_DIALOGUE_QUEST_PROGRESS_FROM;
		static const long ID_DIALOGUE_QUEST_PROGRESS_TO;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		static const long ID_BUTTON6;
		static const long ID_DIALOGUE_QUEST;
		static const long ID_DIALOGUE_SCRIPT;
		static const long ID_DIALOGUE;
		static const long ID_PANEL6;
		static const long ID_NOTEBOOK1;
		static const long ID_BUTTON7;
		static const long ID_BUTTON1;
		//*)

	private:

		//(*Handlers(NPCTypeEditor)
		void OnBitmapButton1Click(wxCommandEvent& event);
		void OnBitmapButton2Click(wxCommandEvent& event);
		void OnBitmapButton4Click(wxCommandEvent& event);
		void OnBitmapButton3Click(wxCommandEvent& event);
		void OnwxDialogueSelectionChanged(wxTreeEvent& event);
		void OnwxDialogueTextText(wxCommandEvent& event);
		void OnButton2Click(wxCommandEvent& event);
		void OnButton4Click(wxCommandEvent& event);
		void OnButton3Click(wxCommandEvent& event);
		void OnwxDialogueQuestSelect(wxCommandEvent& event);
		void OnwxDialogueBlockNumberChange(wxSpinEvent& event);
		void OnwxDialogueScriptSelect(wxCommandEvent& event);
		void OnwxDialogueStartTradeSelect(wxCommandEvent& event);
		void OnwxDialogueGoToBlockSelect(wxCommandEvent& event);
		void OnwxDialogueGoToBlockNumberChange(wxSpinEvent& event);
		void OnwxDialogueQuestProgressFromChange(wxSpinEvent& event);
		void OnwxDialogueQuestProgressToChange(wxSpinEvent& event);
		void OnButton7Click(wxCommandEvent& event);
		void OnButton1Click(wxCommandEvent& event);
		//*)

        void updateDialogueTree();
		void updateDialogueColors();

		DECLARE_EVENT_TABLE()
};

#endif
