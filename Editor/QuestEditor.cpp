#include "QuestEditor.h"

//(*InternalHeaders(QuestEditor)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//(*IdInit(QuestEditor)
const long QuestEditor::ID_BITMAPBUTTON1 = wxNewId();
const long QuestEditor::ID_QUEST_PROGRESS_FROM = wxNewId();
const long QuestEditor::ID_QUEST_PROGRESS_TO = wxNewId();
const long QuestEditor::ID_BITMAPBUTTON2 = wxNewId();
const long QuestEditor::ID_QUEST_PROGESS_TEXT = wxNewId();
const long QuestEditor::ID_TEXT = wxNewId();
const long QuestEditor::ID_STATICLINE2 = wxNewId();
const long QuestEditor::ID_PANEL2 = wxNewId();
const long QuestEditor::ID_STATICLINE1 = wxNewId();
const long QuestEditor::ID_BUTTON1 = wxNewId();
const long QuestEditor::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(QuestEditor,wxDialog)
	//(*EventTable(QuestEditor)
	//*)
END_EVENT_TABLE()

QuestEditor::QuestEditor(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(QuestEditor)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("Quest Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(289,258));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	Panel2 = new wxPanel(this, ID_PANEL2, wxDefaultPosition, wxSize(392,337), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	BitmapButton1 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_DELETE")),wxART_BUTTON), wxPoint(16,304), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	wxQuestProgressFrom = new wxSpinCtrl(Panel2, ID_QUEST_PROGRESS_FROM, _T("0"), wxPoint(216,304), wxSize(64,21), 0, 0, 100, 0, _T("ID_QUEST_PROGRESS_FROM"));
	wxQuestProgressFrom->SetValue(_T("0"));
	wxQuestProgressTo = new wxSpinCtrl(Panel2, ID_QUEST_PROGRESS_TO, _T("0"), wxPoint(288,304), wxSize(56,21), 0, 0, 100, 0, _T("ID_QUEST_PROGRESS_TO"));
	wxQuestProgressTo->SetValue(_T("0"));
	BitmapButton2 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON2, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_BUTTON), wxPoint(352,304), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	wxQuestProgressText = new wxListCtrl(Panel2, ID_QUEST_PROGESS_TEXT, wxPoint(16,16), wxSize(360,208), wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_QUEST_PROGESS_TEXT"));
	wxText = new wxTextCtrl(Panel2, ID_TEXT, wxEmptyString, wxPoint(16,232), wxSize(360,48), 0, wxDefaultValidator, _T("ID_TEXT"));
	wxText->Disable();
	StaticLine2 = new wxStaticLine(Panel2, ID_STATICLINE2, wxPoint(0,296), wxSize(392,2), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
	FlexGridSizer1->Add(Panel2, 1, wxALL|wxFIXED_MINSIZE|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
	FlexGridSizer2->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	Button1 = new wxButton(this, ID_BUTTON1, _("Discard"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer3->Add(Button1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer3->Add(Button2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&QuestEditor::OnBitmapButton1Click);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&QuestEditor::OnBitmapButton2Click);
	Connect(ID_QUEST_PROGESS_TEXT,wxEVT_COMMAND_LIST_ITEM_SELECTED,(wxObjectEventFunction)&QuestEditor::OnwxQuestProgressTextItemSelect);
	Connect(ID_QUEST_PROGESS_TEXT,wxEVT_COMMAND_LIST_ITEM_DESELECTED,(wxObjectEventFunction)&QuestEditor::OnwxQuestProgressTextItemDeselect);
	Connect(ID_TEXT,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&QuestEditor::OnwxTextText);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&QuestEditor::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&QuestEditor::OnButton2Click);
	//*)

	_assert(editingQuestIndex >= 0 && editingQuestIndex < (int)Editor::getInstance().Quest.size(),
            "Quest index out of bounds in QuestEditor constructor.");

	editingQuest = Editor::getInstance().Quest[editingQuestIndex];

    wxListItem col0;
    col0.SetId(0);
    col0.SetText(_("from"));
    wxQuestProgressText->InsertColumn(0, col0);

    wxListItem col1;
    col1.SetId(1);
    col1.SetText(_("to"));
    wxQuestProgressText->InsertColumn(1, col1);

    wxListItem col2;
    col2.SetId(2);
    col2.SetText(_("text"));
    wxQuestProgressText->InsertColumn(2, col2);

    for(size_t i=0; i<editingQuest.questProgressText.size(); ++i) {
        wxListItem item;
        item.SetId(i);
        item.SetText(editingQuest.questProgressText[i].text);
        wxQuestProgressText->InsertItem(item);

        wxQuestProgressText->SetItem(i, 0, Editor::getInstance().intToString(editingQuest.questProgressText[i].progressFrom));
        wxQuestProgressText->SetItem(i, 1, Editor::getInstance().intToString(editingQuest.questProgressText[i].progressTo));
        wxQuestProgressText->SetItem(i, 2, editingQuest.questProgressText[i].text);
    }
}

QuestEditor::~QuestEditor()
{
	//(*Destroy(QuestEditor)
	//*)
}


void QuestEditor::OnButton1Click(wxCommandEvent& event)
{
    Close();
}

void QuestEditor::OnButton2Click(wxCommandEvent& event)
{
    editingQuest.questProgressText.clear();
    long item = wxQuestProgressText->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE);
    while(item >= 0) {
        wxListItem info[3];
        for(int i=0; i<3; ++i) {
            info[i].m_itemId = item;
            info[i].m_col = i;
            info[i].m_mask = wxLIST_MASK_TEXT;
            wxQuestProgressText->GetItem(info[i]);
        }

        int progressFrom = 0;
        int progressTo = 0;

        sscanf(info[0].m_text.c_str(), "%d", &progressFrom);
        sscanf(info[1].m_text.c_str(), "%d", &progressTo);

        editingQuest.questProgressText.push_back(QuestClass::QuestProgressTextClass(progressFrom, progressTo, info[2].m_text.c_str()));
        item = wxQuestProgressText->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE);
    }

	_assert(editingQuestIndex >= 0 && editingQuestIndex < (int)Editor::getInstance().Quest.size(),
            "Quest index out of bounds in OnButton2Click.");

    Editor::getInstance().Quest[editingQuestIndex] = editingQuest;

    Close();
}

void QuestEditor::OnBitmapButton1Click(wxCommandEvent& event)
{
    long item = wxQuestProgressText->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item >= 0) {
        wxQuestProgressText->DeleteItem(item);
    }
    wxText->Enable(false);
    wxText->SetValue("");
}

void QuestEditor::OnBitmapButton2Click(wxCommandEvent& event)
{
    int count = wxQuestProgressText->GetItemCount();

    wxListItem item;
    item.SetId(count);
    wxQuestProgressText->InsertItem(item);

    wxQuestProgressText->SetItem(count, 0, Editor::getInstance().intToString(wxQuestProgressFrom->GetValue()));
    wxQuestProgressText->SetItem(count, 1, Editor::getInstance().intToString(wxQuestProgressTo->GetValue()));
    wxQuestProgressText->SetItem(count, 2, "");
}

void QuestEditor::OnwxTextText(wxCommandEvent& event)
{
    long item = wxQuestProgressText->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item >= 0) {
        wxQuestProgressText->SetItem(item, 2, event.GetString());
    }
}

void QuestEditor::OnwxQuestProgressTextItemSelect(wxListEvent& event)
{
    if(event.GetIndex() >= 0) {
        wxListItem rowInfo;
        rowInfo.m_itemId = event.GetIndex();
        rowInfo.m_col = 2;
        rowInfo.m_mask = wxLIST_MASK_TEXT;
        if(wxQuestProgressText->GetItem(rowInfo)) {
            wxText->Enable(true);
            wxText->SetValue(rowInfo.m_text);
        }
        else {
            wxText->Enable(false);
            wxText->SetValue("");
        }
    }
    else {
        wxText->Enable(false);
        wxText->SetValue("");
    }
}

void QuestEditor::OnwxQuestProgressTextItemDeselect(wxListEvent& event)
{
    wxText->Enable(false);
    wxText->SetValue("");
}
