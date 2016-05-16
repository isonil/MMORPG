#include "NPCTypeEditor.h"

//(*InternalHeaders(NPCTypeEditor)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include "source/Editor.hpp"

//(*IdInit(NPCTypeEditor)
const long NPCTypeEditor::ID_STATICTEXT2 = wxNewId();
const long NPCTypeEditor::ID_NAME = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT4 = wxNewId();
const long NPCTypeEditor::ID_MAX_HEALTH = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT3 = wxNewId();
const long NPCTypeEditor::ID_TEAM = wxNewId();
const long NPCTypeEditor::ID_PANEL1 = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT7 = wxNewId();
const long NPCTypeEditor::ID_WEAPON = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT8 = wxNewId();
const long NPCTypeEditor::ID_HELMET = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT9 = wxNewId();
const long NPCTypeEditor::ID_VEST = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT10 = wxNewId();
const long NPCTypeEditor::ID_BOOTS = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT11 = wxNewId();
const long NPCTypeEditor::ID_GLOVES = wxNewId();
const long NPCTypeEditor::ID_PANEL2 = wxNewId();
const long NPCTypeEditor::ID_PANEL3 = wxNewId();
const long NPCTypeEditor::ID_BITMAPBUTTON1 = wxNewId();
const long NPCTypeEditor::ID_BITMAPBUTTON2 = wxNewId();
const long NPCTypeEditor::ID_LOOT_ADD_OBJECT_TYPE = wxNewId();
const long NPCTypeEditor::ID_LOOT_ADD_OBJECT_QUANTITY_FROM = wxNewId();
const long NPCTypeEditor::ID_LOOT_ADD_OBJECT_CHANCE = wxNewId();
const long NPCTypeEditor::ID_LOOT_ADD_OBJECT_QUANTITY_TO = wxNewId();
const long NPCTypeEditor::ID_LOOT = wxNewId();
const long NPCTypeEditor::ID_PANEL4 = wxNewId();
const long NPCTypeEditor::ID_TRADE = wxNewId();
const long NPCTypeEditor::ID_BITMAPBUTTON3 = wxNewId();
const long NPCTypeEditor::ID_BITMAPBUTTON4 = wxNewId();
const long NPCTypeEditor::ID_TRADE_ADD_OBJECT_TYPE = wxNewId();
const long NPCTypeEditor::ID_PANEL5 = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_TEXT = wxNewId();
const long NPCTypeEditor::ID_BUTTON2 = wxNewId();
const long NPCTypeEditor::ID_BUTTON3 = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT12 = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT13 = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_START_TRADE = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_GO_TO_BLOCK = wxNewId();
const long NPCTypeEditor::ID_STATICBOX1 = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT15 = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_BLOCK_NUMBER = wxNewId();
const long NPCTypeEditor::ID_STATICBOX2 = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_GO_TO_BLOCK_NUMBER = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT16 = wxNewId();
const long NPCTypeEditor::ID_STATICTEXT17 = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_QUEST_PROGRESS_FROM = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_QUEST_PROGRESS_TO = wxNewId();
const long NPCTypeEditor::ID_BUTTON4 = wxNewId();
const long NPCTypeEditor::ID_BUTTON5 = wxNewId();
const long NPCTypeEditor::ID_BUTTON6 = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_QUEST = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE_SCRIPT = wxNewId();
const long NPCTypeEditor::ID_DIALOGUE = wxNewId();
const long NPCTypeEditor::ID_PANEL6 = wxNewId();
const long NPCTypeEditor::ID_NOTEBOOK1 = wxNewId();
const long NPCTypeEditor::ID_BUTTON7 = wxNewId();
const long NPCTypeEditor::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(NPCTypeEditor,wxDialog)
	//(*EventTable(NPCTypeEditor)
	//*)
END_EVENT_TABLE()

NPCTypeEditor::NPCTypeEditor(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(NPCTypeEditor)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer5;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("NPC Type Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(451,415));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(430,430), 0, _T("ID_NOTEBOOK1"));
	Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxPoint(115,206), wxSize(386,246), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer3->AddGrowableCol(1);
	StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer3->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxName = new wxTextCtrl(Panel1, ID_NAME, wxEmptyString, wxDefaultPosition, wxSize(116,21), 0, wxDefaultValidator, _T("ID_NAME"));
	FlexGridSizer3->Add(wxName, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(79,20,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(Panel1, ID_STATICTEXT4, _("maxHealth"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
	FlexGridSizer3->Add(StaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxMaxHealth = new wxSpinCtrl(Panel1, ID_MAX_HEALTH, _T("100"), wxDefaultPosition, wxDefaultSize, 0, 0, 10000, 100, _T("ID_MAX_HEALTH"));
	wxMaxHealth->SetValue(_T("100"));
	FlexGridSizer3->Add(wxMaxHealth, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("team"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
	FlexGridSizer3->Add(StaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxTeam = new wxSpinCtrl(Panel1, ID_TEAM, _T("0"), wxDefaultPosition, wxDefaultSize, 0, 0, 100, 0, _T("ID_TEAM"));
	wxTeam->SetValue(_T("0"));
	FlexGridSizer3->Add(wxTeam, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer3);
	FlexGridSizer3->SetSizeHints(Panel1);
	Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxPoint(54,14), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer5->AddGrowableCol(1);
	StaticText7 = new wxStaticText(Panel2, ID_STATICTEXT7, _("Weapon"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	FlexGridSizer5->Add(StaticText7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxWeapon = new wxChoice(Panel2, ID_WEAPON, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_WEAPON"));
	FlexGridSizer5->Add(wxWeapon, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(90,20,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText8 = new wxStaticText(Panel2, ID_STATICTEXT8, _("Helmet"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT8"));
	FlexGridSizer5->Add(StaticText8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxHelmet = new wxChoice(Panel2, ID_HELMET, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_HELMET"));
	FlexGridSizer5->Add(wxHelmet, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText9 = new wxStaticText(Panel2, ID_STATICTEXT9, _("Vest"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT9"));
	FlexGridSizer5->Add(StaticText9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxVest = new wxChoice(Panel2, ID_VEST, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_VEST"));
	FlexGridSizer5->Add(wxVest, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText10 = new wxStaticText(Panel2, ID_STATICTEXT10, _("Boots"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT10"));
	FlexGridSizer5->Add(StaticText10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxBoots = new wxChoice(Panel2, ID_BOOTS, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_BOOTS"));
	FlexGridSizer5->Add(wxBoots, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText11 = new wxStaticText(Panel2, ID_STATICTEXT11, _("Gloves"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT11"));
	FlexGridSizer5->Add(StaticText11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	wxGloves = new wxChoice(Panel2, ID_GLOVES, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_GLOVES"));
	FlexGridSizer5->Add(wxGloves, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer5->Add(-1,-1,1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel2->SetSizer(FlexGridSizer5);
	FlexGridSizer5->Fit(Panel2);
	FlexGridSizer5->SetSizeHints(Panel2);
	Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxPoint(165,13), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
	FlexGridSizer6 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer6->AddGrowableCol(1);
	Panel3->SetSizer(FlexGridSizer6);
	FlexGridSizer6->Fit(Panel3);
	FlexGridSizer6->SetSizeHints(Panel3);
	Panel4 = new wxPanel(Notebook1, ID_PANEL4, wxPoint(286,8), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
	BitmapButton1 = new wxBitmapButton(Panel4, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_DELETE")),wxART_BUTTON), wxPoint(16,328), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
	BitmapButton1->SetDefault();
	BitmapButton2 = new wxBitmapButton(Panel4, ID_BITMAPBUTTON2, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_BUTTON), wxPoint(384,328), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
	wxLootAddObjectType = new wxChoice(Panel4, ID_LOOT_ADD_OBJECT_TYPE, wxPoint(240,328), wxSize(138,21), 0, 0, 0, wxDefaultValidator, _T("ID_LOOT_ADD_OBJECT_TYPE"));
	wxLootAddObjectQuantityFrom = new wxSpinCtrl(Panel4, ID_LOOT_ADD_OBJECT_QUANTITY_FROM, _T("1"), wxPoint(240,352), wxSize(64,21), 0, 0, 100, 1, _T("ID_LOOT_ADD_OBJECT_QUANTITY_FROM"));
	wxLootAddObjectQuantityFrom->SetValue(_T("1"));
	wxLootAddObjectChance = new wxSpinCtrl(Panel4, ID_LOOT_ADD_OBJECT_CHANCE, _T("100"), wxPoint(240,376), wxSize(136,21), 0, 0, 100, 100, _T("ID_LOOT_ADD_OBJECT_CHANCE"));
	wxLootAddObjectChance->SetValue(_T("100"));
	wxLootAddObjectQuantityTo = new wxSpinCtrl(Panel4, ID_LOOT_ADD_OBJECT_QUANTITY_TO, _T("1"), wxPoint(312,352), wxSize(64,21), 0, 0, 100, 1, _T("ID_LOOT_ADD_OBJECT_QUANTITY_TO"));
	wxLootAddObjectQuantityTo->SetValue(_T("1"));
	wxLoot = new wxListCtrl(Panel4, ID_LOOT, wxPoint(16,16), wxSize(392,304), wxLC_REPORT|wxLC_SINGLE_SEL, wxDefaultValidator, _T("ID_LOOT"));
	Panel5 = new wxPanel(Notebook1, ID_PANEL5, wxPoint(294,18), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
	wxTrade = new wxListBox(Panel5, ID_TRADE, wxPoint(16,16), wxSize(392,352), 0, 0, 0, wxDefaultValidator, _T("ID_TRADE"));
	BitmapButton3 = new wxBitmapButton(Panel5, ID_BITMAPBUTTON3, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_DELETE")),wxART_BUTTON), wxPoint(16,376), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
	BitmapButton3->SetDefault();
	BitmapButton4 = new wxBitmapButton(Panel5, ID_BITMAPBUTTON4, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_BUTTON), wxPoint(384,376), wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
	wxTradeAddObjectType = new wxChoice(Panel5, ID_TRADE_ADD_OBJECT_TYPE, wxPoint(248,376), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_TRADE_ADD_OBJECT_TYPE"));
	Panel6 = new wxPanel(Notebook1, ID_PANEL6, wxPoint(284,15), wxSize(423,336), wxTAB_TRAVERSAL, _T("ID_PANEL6"));
	wxDialogueText = new wxTextCtrl(Panel6, ID_DIALOGUE_TEXT, wxEmptyString, wxPoint(16,336), wxSize(280,56), wxTE_MULTILINE, wxDefaultValidator, _T("ID_DIALOGUE_TEXT"));
	wxDialogueText->Disable();
	Button2 = new wxButton(Panel6, ID_BUTTON2, _("New block"), wxPoint(304,328), wxSize(80,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
	Button3 = new wxButton(Panel6, ID_BUTTON3, _("New option"), wxPoint(304,352), wxSize(80,23), 0, wxDefaultValidator, _T("ID_BUTTON3"));
	StaticText12 = new wxStaticText(Panel6, ID_STATICTEXT12, _("Number:"), wxPoint(24,240), wxDefaultSize, 0, _T("ID_STATICTEXT12"));
	StaticText13 = new wxStaticText(Panel6, ID_STATICTEXT13, _("Effect:"), wxPoint(184,240), wxDefaultSize, 0, _T("ID_STATICTEXT13"));
	wxDialogueStartTrade = new wxRadioButton(Panel6, ID_DIALOGUE_START_TRADE, _("Start trade"), wxPoint(184,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_DIALOGUE_START_TRADE"));
	wxDialogueStartTrade->Disable();
	wxDialogueGoToBlock = new wxRadioButton(Panel6, ID_DIALOGUE_GO_TO_BLOCK, _("Go to block:"), wxPoint(184,272), wxDefaultSize, 0, wxDefaultValidator, _T("ID_DIALOGUE_GO_TO_BLOCK"));
	wxDialogueGoToBlock->SetValue(true);
	wxDialogueGoToBlock->Disable();
	StaticBox1 = new wxStaticBox(Panel6, ID_STATICBOX1, _("Block options"), wxPoint(16,224), wxSize(152,104), 0, _T("ID_STATICBOX1"));
	StaticText15 = new wxStaticText(Panel6, ID_STATICTEXT15, _("Run script:"), wxPoint(24,280), wxDefaultSize, 0, _T("ID_STATICTEXT15"));
	wxDialogueBlockNumber = new wxSpinCtrl(Panel6, ID_DIALOGUE_BLOCK_NUMBER, _T("0"), wxPoint(24,256), wxSize(136,21), 0, 0, 100, 0, _T("ID_DIALOGUE_BLOCK_NUMBER"));
	wxDialogueBlockNumber->SetValue(_T("0"));
	wxDialogueBlockNumber->Disable();
	StaticBox2 = new wxStaticBox(Panel6, ID_STATICBOX2, _("Option options:"), wxPoint(176,224), wxSize(232,104), 0, _T("ID_STATICBOX2"));
	wxDialogueGoToBlockNumber = new wxSpinCtrl(Panel6, ID_DIALOGUE_GO_TO_BLOCK_NUMBER, _T("-1"), wxPoint(184,296), wxSize(72,21), 0, -1, 100, -1, _T("ID_DIALOGUE_GO_TO_BLOCK_NUMBER"));
	wxDialogueGoToBlockNumber->SetValue(_T("-1"));
	wxDialogueGoToBlockNumber->Disable();
	StaticText16 = new wxStaticText(Panel6, ID_STATICTEXT16, _("Quest ID name"), wxPoint(280,240), wxDefaultSize, 0, _T("ID_STATICTEXT16"));
	StaticText17 = new wxStaticText(Panel6, ID_STATICTEXT17, _("Progress (from, to)"), wxPoint(280,280), wxDefaultSize, 0, _T("ID_STATICTEXT17"));
	wxDialogueQuestProgressFrom = new wxSpinCtrl(Panel6, ID_DIALOGUE_QUEST_PROGRESS_FROM, _T("0"), wxPoint(280,296), wxSize(56,21), 0, 0, 100, 0, _T("ID_DIALOGUE_QUEST_PROGRESS_FROM"));
	wxDialogueQuestProgressFrom->SetValue(_T("0"));
	wxDialogueQuestProgressFrom->Disable();
	wxDialogueQuestProgressTo = new wxSpinCtrl(Panel6, ID_DIALOGUE_QUEST_PROGRESS_TO, _T("0"), wxPoint(344,296), wxSize(56,21), 0, 0, 100, 0, _T("ID_DIALOGUE_QUEST_PROGRESS_TO"));
	wxDialogueQuestProgressTo->SetValue(_T("0"));
	wxDialogueQuestProgressTo->Disable();
	Button4 = new wxButton(Panel6, ID_BUTTON4, _("Delete"), wxPoint(304,376), wxSize(80,23), 0, wxDefaultValidator, _T("ID_BUTTON4"));
	Button5 = new wxButton(Panel6, ID_BUTTON5, _("/\\"), wxPoint(392,336), wxSize(24,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
	Button6 = new wxButton(Panel6, ID_BUTTON6, _("\\/"), wxPoint(392,368), wxSize(24,23), 0, wxDefaultValidator, _T("ID_BUTTON6"));
	wxDialogueQuest = new wxChoice(Panel6, ID_DIALOGUE_QUEST, wxPoint(280,256), wxSize(120,21), 0, 0, 0, wxDefaultValidator, _T("ID_DIALOGUE_QUEST"));
	wxDialogueQuest->Disable();
	wxDialogueScript = new wxChoice(Panel6, ID_DIALOGUE_SCRIPT, wxPoint(24,296), wxSize(136,21), 0, 0, 0, wxDefaultValidator, _T("ID_DIALOGUE_SCRIPT"));
	wxDialogueScript->Disable();
	wxDialogue = new wxTreeCtrl(Panel6, ID_DIALOGUE, wxPoint(16,16), wxSize(392,200), wxTR_HIDE_ROOT|wxTR_DEFAULT_STYLE, wxDefaultValidator, _T("ID_DIALOGUE"));
	Notebook1->AddPage(Panel1, _("Params"), false);
	Notebook1->AddPage(Panel2, _("Slots"), false);
	Notebook1->AddPage(Panel3, _("AI"), false);
	Notebook1->AddPage(Panel4, _("Loot"), false);
	Notebook1->AddPage(Panel5, _("Trade"), false);
	Notebook1->AddPage(Panel6, _("Dialogue"), false);
	FlexGridSizer1->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer2->AddGrowableCol(0);
	Button7 = new wxButton(this, ID_BUTTON7, _("Discard"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
	FlexGridSizer2->Add(Button7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	Button1 = new wxButton(this, ID_BUTTON1, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(Button1, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);

	Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnBitmapButton1Click);
	Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnBitmapButton2Click);
	Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnBitmapButton3Click);
	Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnBitmapButton4Click);
	Connect(ID_DIALOGUE_TEXT,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueTextText);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnButton2Click);
	Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnButton3Click);
	Connect(ID_DIALOGUE_START_TRADE,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueStartTradeSelect);
	Connect(ID_DIALOGUE_GO_TO_BLOCK,wxEVT_COMMAND_RADIOBUTTON_SELECTED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueGoToBlockSelect);
	Connect(ID_DIALOGUE_BLOCK_NUMBER,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueBlockNumberChange);
	Connect(ID_DIALOGUE_GO_TO_BLOCK_NUMBER,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueGoToBlockNumberChange);
	Connect(ID_DIALOGUE_QUEST_PROGRESS_FROM,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueQuestProgressFromChange);
	Connect(ID_DIALOGUE_QUEST_PROGRESS_TO,wxEVT_COMMAND_SPINCTRL_UPDATED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueQuestProgressToChange);
	Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnButton4Click);
	Connect(ID_DIALOGUE_QUEST,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueQuestSelect);
	Connect(ID_DIALOGUE_SCRIPT,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueScriptSelect);
	Connect(ID_DIALOGUE,wxEVT_COMMAND_TREE_SEL_CHANGED,(wxObjectEventFunction)&NPCTypeEditor::OnwxDialogueSelectionChanged);
	Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnButton7Click);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&NPCTypeEditor::OnButton1Click);
	//*)

	_assert(editingNPCTypeIndex >= 0 && editingNPCTypeIndex < (int)Editor::getInstance().NPCType.size(),
            "NPC type index out of bounds in NPCTypeEditor constructor.");

    NPCTypeClass &NPCType = Editor::getInstance().NPCType[editingNPCTypeIndex];
    wxName->SetValue(NPCType.name);
    wxMaxHealth->SetValue(NPCType.maxHealth);
    wxTeam->SetValue(NPCType.team);

    if(Editor::getInstance().ObjectType.size()) {
        size_t maxSize = Editor::getInstance().ObjectType.size();
        maxSize = std::max(maxSize, Editor::getInstance().Script.size());
        maxSize = std::max(maxSize, Editor::getInstance().Quest.size());
        indexes = new int[maxSize];
    }
    else indexes = NULL;
    negativeIndex = -1;

    int index = -1;
    wxWeapon->Append("-none-", (void*)&negativeIndex);
    for(size_t i=0; i<Editor::getInstance().ObjectType.size(); ++i) {
        indexes[i] = i;
        if(!Editor::getInstance().ObjectType[i].isLoaded) continue;
        if(Editor::getInstance().ObjectType[i].baseType != OBJECT_BASE_TYPE_WEAPON) continue;
        wxWeapon->Append(Editor::getInstance().ObjectType[i].name.c_str(),
                         (void*)&indexes[i]);
        if(NPCType.objectTypeOnSlot[0] == i) index = wxWeapon->GetCount()-1;
    }
    wxWeapon->SetSelection(index);
    index = -1;
    wxHelmet->Append("-none-", (void*)&negativeIndex);
    for(size_t i=0; i<Editor::getInstance().ObjectType.size(); ++i) {
        if(!Editor::getInstance().ObjectType[i].isLoaded) continue;
        if(Editor::getInstance().ObjectType[i].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;
        if(Editor::getInstance().ObjectType[i].equipmentType != EQUIPMENT_TYPE_HELMET) continue;
        wxHelmet->Append(Editor::getInstance().ObjectType[i].name.c_str(),
                         (void*)&indexes[i]);
        if(NPCType.objectTypeOnSlot[4] == i) index = wxHelmet->GetCount()-1;
    }
    wxHelmet->SetSelection(index);
    index = -1;
    wxVest->Append("-none-", (void*)&negativeIndex);
    for(size_t i=0; i<Editor::getInstance().ObjectType.size(); ++i) {
        if(!Editor::getInstance().ObjectType[i].isLoaded) continue;
        if(Editor::getInstance().ObjectType[i].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;
        if(Editor::getInstance().ObjectType[i].equipmentType != EQUIPMENT_TYPE_VEST) continue;
        wxVest->Append(Editor::getInstance().ObjectType[i].name.c_str(),
                       (void*)&indexes[i]);
        if(NPCType.objectTypeOnSlot[2] == i) index = wxVest->GetCount()-1;
    }
    wxVest->SetSelection(index);
    index = -1;
    wxBoots->Append("-none-", (void*)&negativeIndex);
    for(size_t i=0; i<Editor::getInstance().ObjectType.size(); ++i) {
        if(!Editor::getInstance().ObjectType[i].isLoaded) continue;
        if(Editor::getInstance().ObjectType[i].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;
        if(Editor::getInstance().ObjectType[i].equipmentType != EQUIPMENT_TYPE_BOOTS) continue;
        wxBoots->Append(Editor::getInstance().ObjectType[i].name.c_str(),
                        (void*)&indexes[i]);
        if(NPCType.objectTypeOnSlot[1] == i) index = wxBoots->GetCount()-1;
    }
    wxBoots->SetSelection(index);
    index = -1;
    wxGloves->Append("-none-", (void*)&negativeIndex);
    for(size_t i=0; i<Editor::getInstance().ObjectType.size(); ++i) {
        if(!Editor::getInstance().ObjectType[i].isLoaded) continue;
        if(Editor::getInstance().ObjectType[i].baseType != OBJECT_BASE_TYPE_EQUIPMENT) continue;
        if(Editor::getInstance().ObjectType[i].equipmentType != EQUIPMENT_TYPE_GLOVES) continue;
        wxGloves->Append(Editor::getInstance().ObjectType[i].name.c_str(),
                         (void*)&indexes[i]);
        if(NPCType.objectTypeOnSlot[3] == i) index = wxGloves->GetCount()-1;
    }
    wxGloves->SetSelection(index);

    wxListItem col0;
    col0.SetId(0);
    col0.SetText(_("name"));
    wxLoot->InsertColumn(0, col0);

    wxListItem col1;
    col1.SetId(1);
    col1.SetText(_("quantity from"));
    wxLoot->InsertColumn(1, col1);

    wxListItem col2;
    col2.SetId(2);
    col2.SetText(_("quantity to"));
    wxLoot->InsertColumn(2, col2);

    wxListItem col3;
    col3.SetId(3);
    col3.SetText(_("chance"));
    wxLoot->InsertColumn(3, col3);

    wxListItem col4;
    col4.SetId(4);
    col4.SetText(_("id"));
    col4.SetWidth(30);
    wxLoot->InsertColumn(4, col4);

    for(size_t i=0; i<NPCType.lootObject.size(); ++i) {
        wxListItem item;
        item.SetId(i);
        item.SetText(Editor::getInstance().ObjectType[NPCType.lootObject[i].objectType].name.c_str());
        wxLoot->InsertItem(item);

        wxLoot->SetItem(i, 0, Editor::getInstance().ObjectType[NPCType.lootObject[i].objectType].name.c_str());
        wxLoot->SetItem(i, 1, Editor::getInstance().intToString(NPCType.lootObject[i].quantityFrom).c_str());
        wxLoot->SetItem(i, 2, Editor::getInstance().intToString(NPCType.lootObject[i].quantityTo).c_str());
        wxLoot->SetItem(i, 3, Editor::getInstance().intToString(NPCType.lootObject[i].chance).c_str());
        wxLoot->SetItem(i, 4, Editor::getInstance().intToString(NPCType.lootObject[i].objectType).c_str());
    }

    for(size_t i=0; i<Editor::getInstance().ObjectType.size(); ++i) {
        if(!Editor::getInstance().ObjectType[i].isLoaded) continue;
        wxLootAddObjectType->Append(Editor::getInstance().ObjectType[i].name.c_str(),
                                    (void*)&indexes[i]);
    }

    for(size_t i=0; i<NPCType.tradeObject.size(); ++i) {
        _assert(NPCType.tradeObject[i].objectType >= 0 && NPCType.tradeObject[i].objectType < (int)Editor::getInstance().ObjectType.size(),
                "NPC type trade object type index out of bounds in NPCTypeEditor constructor.");
        wxTrade->Append(Editor::getInstance().ObjectType[NPCType.tradeObject[i].objectType].name.c_str(), (void*)&indexes[NPCType.tradeObject[i].objectType]);
    }

    for(size_t i=0; i<Editor::getInstance().ObjectType.size(); ++i) {
        if(!Editor::getInstance().ObjectType[i].isLoaded) continue;
        wxTradeAddObjectType->Append(Editor::getInstance().ObjectType[i].name.c_str(),
                                     (void*)&indexes[i]);
    }

    editingDialogueBlock = NPCType.dialogueBlock;
    updateDialogueTree();

    wxDialogueScript->Append("-none-", (void*)&negativeIndex);
    for(size_t i=0; i<Editor::getInstance().Script.size(); ++i) {
        if(!Editor::getInstance().Script[i].isLoaded) continue;
        wxDialogueScript->Append(Editor::getInstance().Script[i].IDName.c_str(),
                                 (void*)&indexes[i]);
    }

    wxDialogueQuest->Append("-none-", (void*)&negativeIndex);
    for(size_t i=0; i<Editor::getInstance().Quest.size(); ++i) {
        if(!Editor::getInstance().Quest[i].isLoaded) continue;
        wxDialogueQuest->Append(Editor::getInstance().Quest[i].IDName.c_str(),
                                (void*)&indexes[i]);
    }
}

NPCTypeEditor::~NPCTypeEditor()
{
	//(*Destroy(NPCTypeEditor)
	//*)
	delete []indexes;
}


void NPCTypeEditor::OnBitmapButton1Click(wxCommandEvent& event)
{
    long item = wxLoot->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if(item >= 0) {
        wxLoot->DeleteItem(item);
    }
}

void NPCTypeEditor::OnBitmapButton2Click(wxCommandEvent& event)
{
    if(wxLootAddObjectType->GetSelection() >= 0) {
        int objectTypeIndex = *(int*)wxLootAddObjectType->GetClientData(wxLootAddObjectType->GetSelection());
        _assert(objectTypeIndex >= 0 && objectTypeIndex < (int)Editor::getInstance().ObjectType.size(),
                "Object type index out of bounds in OnBitmapButton2Click.");

        int count = wxLoot->GetItemCount();

        wxListItem item;
        item.SetId(count);
        item.SetText(Editor::getInstance().ObjectType[objectTypeIndex].name.c_str());
        wxLoot->InsertItem(item);

        wxLoot->SetItem(count, 0, Editor::getInstance().ObjectType[objectTypeIndex].name.c_str());
        wxLoot->SetItem(count, 1, Editor::getInstance().intToString(wxLootAddObjectQuantityFrom->GetValue()).c_str());
        wxLoot->SetItem(count, 2, Editor::getInstance().intToString(wxLootAddObjectQuantityTo->GetValue()).c_str());
        wxLoot->SetItem(count, 3, Editor::getInstance().intToString(wxLootAddObjectChance->GetValue()).c_str());
        wxLoot->SetItem(count, 4, Editor::getInstance().intToString(objectTypeIndex).c_str());
    }
}

void NPCTypeEditor::OnBitmapButton4Click(wxCommandEvent& event)
{
    if(wxTradeAddObjectType->GetSelection() >= 0) {
        int objectTypeIndex = *(int*)wxTradeAddObjectType->GetClientData(wxTradeAddObjectType->GetSelection());
            _assert(objectTypeIndex >= 0 && objectTypeIndex < (int)Editor::getInstance().ObjectType.size(),
                    "Object type index out of bounds in OnBitmapButton4Click.");

        wxTrade->Append(Editor::getInstance().ObjectType[objectTypeIndex].name.c_str(),
                        (void*)&indexes[objectTypeIndex]);
    }
}

void NPCTypeEditor::OnBitmapButton3Click(wxCommandEvent& event)
{
    if(wxTrade->GetSelection() >= 0) {
        wxTrade->Delete(wxTrade->GetSelection());
    }
}

void NPCTypeEditor::OnwxDialogueSelectionChanged(wxTreeEvent& event)
{
    wxDialogue->SetFocus();

    currentBlockIndex = -1;
    currentOptionIndex = -1;

    for(size_t i=0; i<editingDialogueBlock.size(); ++i) {
        if(event.GetItem() == editingDialogueBlock[i].treeItemId) {
            currentBlockIndex = i;
            currentOptionIndex = -1;
            break;
        }
        for(size_t j=0; j<editingDialogueBlock[i].option.size(); ++j) {
            if(event.GetItem() == editingDialogueBlock[i].option[j].treeItemId) {
                currentBlockIndex = i;
                currentOptionIndex = j;
                break;
            }
        }
    }

    wxDialogueText->Enable(false);
    wxDialogueScript->Enable(false);
    wxDialogueQuest->Enable(false);
    wxDialogueBlockNumber->Enable(false);
    wxDialogueGoToBlock->Enable(false);
    wxDialogueStartTrade->Enable(false);
    wxDialogueGoToBlockNumber->Enable(false);
    wxDialogueQuestProgressFrom->Enable(false);
    wxDialogueQuestProgressTo->Enable(false);

    if(currentBlockIndex >= 0) {
        if(currentOptionIndex >= 0) {
            wxDialogueText->SetValue(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].text.c_str());
            for(size_t i=0; i<wxDialogueQuest->GetCount(); ++i) {
                if(*(int*)wxDialogueQuest->GetClientData(i) == editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].requiredQuestProgressIndex) {
                    wxDialogueQuest->SetSelection(i);
                    break;
                }
            }
            if(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].startTrade) {
                wxDialogueStartTrade->SetValue(true);
            }
            else wxDialogueGoToBlock->SetValue(true);
            wxDialogueGoToBlockNumber->SetValue(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].leadToBlock);
            wxDialogueQuestProgressFrom->SetValue(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].requiredQuestProgressFrom);
            wxDialogueQuestProgressTo->SetValue(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].requiredQuestProgressTo);

            wxDialogueQuest->Enable(true);
            wxDialogueStartTrade->Enable(true);
            wxDialogueGoToBlock->Enable(true);
            wxDialogueGoToBlockNumber->Enable(true);
            wxDialogueQuestProgressFrom->Enable(true);
            wxDialogueQuestProgressTo->Enable(true);
        }
        else {
            wxDialogueText->SetValue(editingDialogueBlock[currentBlockIndex].NPCText.c_str());
            wxDialogueQuest->SetSelection(-1);
            wxDialogueGoToBlock->SetValue(true);
            wxDialogueGoToBlockNumber->SetValue(-1);
            wxDialogueQuestProgressFrom->SetValue(0);
            wxDialogueQuestProgressTo->SetValue(0);
        }

        for(size_t i=0; i<wxDialogueScript->GetCount(); ++i) {
            if(*(int*)wxDialogueScript->GetClientData(i) == editingDialogueBlock[currentBlockIndex].scriptIndex) {
                wxDialogueScript->SetSelection(i);
                break;
            }
        }
        wxDialogueBlockNumber->SetValue(currentBlockIndex);

        wxDialogueText->Enable(true);
        wxDialogueScript->Enable(true);
        wxDialogueBlockNumber->Enable(true);
    }
    else {
        wxDialogueText->SetValue("");
        wxDialogueScript->SetSelection(-1);
        wxDialogueQuest->SetSelection(-1);
        wxDialogueBlockNumber->SetValue(0);
        wxDialogueGoToBlock->SetValue(true);
        wxDialogueGoToBlockNumber->SetValue(-1);
        wxDialogueQuestProgressFrom->SetValue(0);
        wxDialogueQuestProgressTo->SetValue(0);
    }
}

void NPCTypeEditor::OnwxDialogueTextText(wxCommandEvent& event)
{
    if(currentBlockIndex >= 0) {
        if(currentOptionIndex >= 0) {
            editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].text = event.GetString();
            std::string target;
            if(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].leadToBlock < 0) target = "exit";
            else target = Editor::getInstance().intToString(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].leadToBlock);
            wxDialogue->SetItemText(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].treeItemId,
                                    ("(->"+target+") "+event.GetString()).c_str());
        }
        else {
            editingDialogueBlock[currentBlockIndex].NPCText = event.GetString();
            wxDialogue->SetItemText(editingDialogueBlock[currentBlockIndex].treeItemId,
                                    ('('+Editor::getInstance().intToString(currentBlockIndex)+") "+event.GetString()).c_str());
        }
    }
}

void NPCTypeEditor::OnButton2Click(wxCommandEvent& event)
{
    editingDialogueBlock.resize(editingDialogueBlock.size()+1);
    wxTreeItemId itemId = wxDialogue->AppendItem(treeRootId, ('('+Editor::getInstance().intToString(editingDialogueBlock.size()-1)+") "+editingDialogueBlock.back().NPCText).c_str());
    wxDialogue->SetItemBold(itemId);
    editingDialogueBlock.back().treeItemId = itemId;
}

void NPCTypeEditor::OnButton4Click(wxCommandEvent& event)
{
    if(currentBlockIndex >= 0) {
        if(currentOptionIndex >= 0) {
            // We need to do 'backup' because Delete calls SelectionChanged callback.
            int blockIndex = currentBlockIndex;
            int optionIndex = currentOptionIndex;
            wxDialogue->Delete(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].treeItemId);
            editingDialogueBlock[blockIndex].option.erase(editingDialogueBlock[blockIndex].option.begin()+optionIndex);
        }
        else {
            int blockIndex = currentBlockIndex;
            wxDialogue->Delete(editingDialogueBlock[currentBlockIndex].treeItemId);
            editingDialogueBlock.erase(editingDialogueBlock.begin()+blockIndex);
            for(size_t i=0; i<editingDialogueBlock.size(); ++i) {
                for(size_t j=0; j<editingDialogueBlock[i].option.size(); ++j) {
                    if(editingDialogueBlock[i].option[j].leadToBlock >= (int)editingDialogueBlock.size()) {
                        editingDialogueBlock[i].option[j].leadToBlock = -1;
                    }
                }
            }
        }
    }
    currentBlockIndex = -1;
    currentOptionIndex = -1;
    updateDialogueTree();
}

void NPCTypeEditor::OnButton3Click(wxCommandEvent& event)
{
    if(currentBlockIndex >= 0) {
        editingDialogueBlock[currentBlockIndex].option.resize(editingDialogueBlock[currentBlockIndex].option.size()+1);
        wxTreeItemId itemId = wxDialogue->AppendItem(editingDialogueBlock[currentBlockIndex].treeItemId,
                                                     ("(->exit) "+editingDialogueBlock[currentBlockIndex].option.back().text).c_str());
        editingDialogueBlock[currentBlockIndex].option.back().treeItemId = itemId;
    }
}

void NPCTypeEditor::OnwxDialogueQuestSelect(wxCommandEvent& event)
{
    if(currentBlockIndex >= 0 && currentOptionIndex >= 0) {
        editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].requiredQuestProgressIndex = *(int*)wxDialogueQuest->GetClientData(event.GetSelection());
        updateDialogueColors();
    }
}

void NPCTypeEditor::updateDialogueTree()
{
    if(!wxDialogue->IsEmpty()) {
        wxDialogue->UnselectAll();
        wxDialogue->DeleteAllItems();
    }
    currentBlockIndex = -1;
    currentOptionIndex = -1;
    treeRootId = wxDialogue->AddRoot("Dialogue");
    for(size_t i=0; i<editingDialogueBlock.size(); ++i) {
        wxTreeItemId itemId = wxDialogue->AppendItem(treeRootId, ('('+Editor::getInstance().intToString(i)+") "+editingDialogueBlock[i].NPCText).c_str());
        editingDialogueBlock[i].treeItemId = itemId;
        wxDialogue->SetItemBold(itemId);

        for(size_t j=0; j<editingDialogueBlock[i].option.size(); ++j) {
            std::string target;
            if(editingDialogueBlock[i].option[j].leadToBlock < 0) target = "exit";
            else target = Editor::getInstance().intToString(editingDialogueBlock[i].option[j].leadToBlock);
            wxTreeItemId optionId = wxDialogue->AppendItem(itemId,
                                                           ("(->"+target+") "+editingDialogueBlock[i].option[j].text).c_str());
            editingDialogueBlock[i].option[j].treeItemId = optionId;
        }
    }
    updateDialogueColors();
    wxDialogue->ExpandAll();
}

void NPCTypeEditor::updateDialogueColors()
{
    for(size_t i=0; i<editingDialogueBlock.size(); ++i) {
        // Looking for a quest related to this block.
        bool shouldBreak = false;
        int questIndex = -1;
        for(size_t j=0; j<editingDialogueBlock.size(); ++j) {
            for(size_t k=0; k<editingDialogueBlock[j].option.size(); ++k) {
                if(editingDialogueBlock[j].option[k].leadToBlock == i) {
                    if(questIndex < 0) questIndex = editingDialogueBlock[j].option[k].requiredQuestProgressIndex;
                    else {
                        if(questIndex != editingDialogueBlock[j].option[k].requiredQuestProgressIndex) {
                            questIndex = -1;
                            shouldBreak = true;
                            break;
                        }
                    }
                }
            }
            if(shouldBreak) break;
        }
        if(questIndex >= 0) wxDialogue->SetItemBackgroundColour(editingDialogueBlock[i].treeItemId, getColorById(questIndex));
        else wxDialogue->SetItemBackgroundColour(editingDialogueBlock[i].treeItemId, wxColor(255, 255, 255));

        for(size_t j=0; j<editingDialogueBlock[i].option.size(); ++j) {
            int questIndex = editingDialogueBlock[i].option[j].requiredQuestProgressIndex;
            if(questIndex >= 0) wxDialogue->SetItemBackgroundColour(editingDialogueBlock[i].option[j].treeItemId, getColorById(questIndex));
            else wxDialogue->SetItemBackgroundColour(editingDialogueBlock[i].option[j].treeItemId, wxColor(255, 255, 255));
        }
    }
}

void NPCTypeEditor::OnwxDialogueBlockNumberChange(wxSpinEvent& event)
{
    event.Veto();
}

void NPCTypeEditor::OnwxDialogueScriptSelect(wxCommandEvent& event)
{
    if(currentBlockIndex >= 0) {
        editingDialogueBlock[currentBlockIndex].scriptIndex = *(int*)wxDialogueScript->GetClientData(event.GetSelection());
    }
}

void NPCTypeEditor::OnwxDialogueStartTradeSelect(wxCommandEvent& event)
{
    if(event.GetSelection() && currentBlockIndex >= 0 && currentOptionIndex >= 0) {
        editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].startTrade = true;
        editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].leadToBlock = -1;
        wxDialogueGoToBlockNumber->SetValue(-1);
        updateDialogueColors();
    }
}

void NPCTypeEditor::OnwxDialogueGoToBlockSelect(wxCommandEvent& event)
{
    if(event.GetSelection() && currentBlockIndex >= 0 && currentOptionIndex >= 0) {
        editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].startTrade = false;
        editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].leadToBlock = wxDialogueGoToBlockNumber->GetValue();
        updateDialogueColors();
    }
}

void NPCTypeEditor::OnwxDialogueGoToBlockNumberChange(wxSpinEvent& event)
{
    if(currentBlockIndex >= 0 && currentOptionIndex >= 0) {
        if(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].startTrade == false) {
            if(event.GetInt() >= (int)editingDialogueBlock.size()) {
                wxDialogueGoToBlockNumber->SetValue(editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].leadToBlock);
            }
            else {
                editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].leadToBlock = event.GetInt();
                updateDialogueColors();
            }
        }
        else wxDialogueGoToBlockNumber->SetValue(-1);
    }
    else wxDialogueGoToBlockNumber->SetValue(-1);
}

void NPCTypeEditor::OnwxDialogueQuestProgressFromChange(wxSpinEvent& event)
{
    if(currentBlockIndex >= 0 && currentOptionIndex >= 0) {
        editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].requiredQuestProgressFrom = event.GetInt();
    }
}

void NPCTypeEditor::OnwxDialogueQuestProgressToChange(wxSpinEvent& event)
{
    if(currentBlockIndex >= 0 && currentOptionIndex >= 0) {
        editingDialogueBlock[currentBlockIndex].option[currentOptionIndex].requiredQuestProgressTo = event.GetInt();
    }
}

void NPCTypeEditor::OnButton7Click(wxCommandEvent& event)
{
    Close();
}

void NPCTypeEditor::OnButton1Click(wxCommandEvent& event)
{
    NPCTypeClass &NPCType = Editor::getInstance().NPCType[editingNPCTypeIndex];

    NPCType.name = wxName->GetValue();
    if(NPCType.name.empty()) NPCType.name = "undefined";
    NPCType.maxHealth = wxMaxHealth->GetValue();
    NPCType.team = wxTeam->GetValue();

    if(wxWeapon->GetSelection() >= 0) NPCType.objectTypeOnSlot[0] = *(int*)wxWeapon->GetClientData(wxWeapon->GetSelection());
    else NPCType.objectTypeOnSlot[0] = -1;
    if(wxHelmet->GetSelection() >= 0) NPCType.objectTypeOnSlot[4] = *(int*)wxHelmet->GetClientData(wxHelmet->GetSelection());
    else NPCType.objectTypeOnSlot[4] = -1;
    if(wxVest->GetSelection() >= 0) NPCType.objectTypeOnSlot[2] = *(int*)wxVest->GetClientData(wxVest->GetSelection());
    else NPCType.objectTypeOnSlot[2] = -1;
    if(wxBoots->GetSelection() >= 0) NPCType.objectTypeOnSlot[1] = *(int*)wxBoots->GetClientData(wxBoots->GetSelection());
    else NPCType.objectTypeOnSlot[1] = -1;
    if(wxGloves->GetSelection() >= 0) NPCType.objectTypeOnSlot[3] = *(int*)wxGloves->GetClientData(wxGloves->GetSelection());
    else NPCType.objectTypeOnSlot[3] = -1;

    NPCType.lootObject.clear();
    long item = wxLoot->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE);
    while(item >= 0) {
        wxListItem info[4];
        for(int i=0; i<4; ++i) {
            info[i].m_itemId = item;
            info[i].m_col = i+1;
            info[i].m_mask = wxLIST_MASK_TEXT;
            wxLoot->GetItem(info[i]);
        }

        int index = -1;
        int quantityFrom = 0;
        int quantityTo = 0;
        int chance = 0;

        sscanf(info[0].m_text.c_str(), "%d", &quantityFrom);
        sscanf(info[1].m_text.c_str(), "%d", &quantityTo);
        sscanf(info[2].m_text.c_str(), "%d", &chance);
        sscanf(info[3].m_text.c_str(), "%d", &index);

        NPCType.lootObject.push_back(NPCTypeClass::LootObjectClass(index, quantityFrom, quantityTo, chance));
        item = wxLoot->GetNextItem(item, wxLIST_NEXT_ALL, wxLIST_STATE_DONTCARE);
    }

    NPCType.tradeObject.clear();
    for(size_t i=0; i<wxTrade->GetCount(); ++i) {
        NPCType.tradeObject.push_back(NPCTypeClass::TradeObjectClass(*(int*)wxTrade->GetClientData(i)));
    }

    NPCType.dialogueBlock = editingDialogueBlock;
    Close();
}
