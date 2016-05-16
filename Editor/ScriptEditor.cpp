#include "ScriptEditor.h"

//(*InternalHeaders(ScriptEditor)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include "wx/stc/stc.h"
#include "source/Classes.hpp"
#include "source/Editor.hpp"

//(*IdInit(ScriptEditor)
const long ScriptEditor::ID_CUSTOM1 = wxNewId();
const long ScriptEditor::ID_TEXTCTRL2 = wxNewId();
const long ScriptEditor::ID_PANEL1 = wxNewId();
const long ScriptEditor::ID_HTMLWINDOW1 = wxNewId();
const long ScriptEditor::ID_PANEL2 = wxNewId();
const long ScriptEditor::ID_NOTEBOOK1 = wxNewId();
const long ScriptEditor::ID_BUTTON1 = wxNewId();
const long ScriptEditor::ID_STATICTEXT1 = wxNewId();
const long ScriptEditor::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ScriptEditor,wxDialog)
	//(*EventTable(ScriptEditor)
	//*)
END_EVENT_TABLE()

ScriptEditor::ScriptEditor(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(ScriptEditor)
	wxFlexGridSizer* FlexGridSizer3;
	wxFlexGridSizer* FlexGridSizer2;
	wxFlexGridSizer* FlexGridSizer1;
	
	Create(parent, wxID_ANY, _("Script Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(447,312));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(423,343), 0, _T("ID_NOTEBOOK1"));
	Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxPoint(37,37), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
	styledTextCtrl = new wxStyledTextCtrl(Panel1,ID_CUSTOM1,wxDefaultPosition,wxSize(399,249),0,_T("ID_CUSTOM1"));
	FlexGridSizer3->Add(styledTextCtrl, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl2 = new wxTextCtrl(Panel1, ID_TEXTCTRL2, _("No errors"), wxDefaultPosition, wxSize(405,45), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	TextCtrl2->SetForegroundColour(wxColour(159,11,15));
	FlexGridSizer3->Add(TextCtrl2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Panel1->SetSizer(FlexGridSizer3);
	FlexGridSizer3->Fit(Panel1);
	FlexGridSizer3->SetSizeHints(Panel1);
	Panel2 = new wxPanel(Notebook1, ID_PANEL2, wxPoint(53,12), wxSize(151,68), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
	HtmlWindow1 = new wxHtmlWindow(Panel2, ID_HTMLWINDOW1, wxPoint(8,8), wxSize(400,304), wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW1"));
	HtmlWindow1->SetPage(_("<strong>Functions:</strong>\n<ul>\n  <li>\n    <strong><font color=\'#009600\'>SetQuestProgress</font></strong>\n    <font color=\'#960000\'>quest progress</font><br>\n    Sets player\'s quest progress.\n  </li>\n  <li>\n    <strong><font color=\'#009600\'>AddMoney</font></strong>\n    <font color=\'#960000\'>amount</font><br>\n    Gives money to player.\n  </li>\n  <li>\n    <strong><font color=\'#009600\'>AddExp</font></strong>\n    <font color=\'#960000\'>amount</font><br>\n    Gives exp to player.\n  </li>\n  <li>\n    <strong><font color=\'#009600\'>EndDialogue</font></strong><br>\n    Ends current dialogue (if active).\n  </li>\n</ul>\n\n<br><br>\n<strong>Condition functions:</strong>\n<ul>\n  <li>\n    <strong><font color=\'#000096\'>QuestProgress</font></strong>\n    <font color=\'#960000\'>quest from to</font><br>\n    Checks if player\'s quest progress is between from and to.\n  </li>\n</ul>"));
	Notebook1->AddPage(Panel1, _("Editor"), false);
	Notebook1->AddPage(Panel2, _("Documentation"), false);
	FlexGridSizer1->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer2 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer2->AddGrowableCol(1);
	Button1 = new wxButton(this, ID_BUTTON1, _("Discard"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer2->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Script ID name"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Button2 = new wxButton(this, ID_BUTTON2, _("Save"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer2->Add(Button2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScriptEditor::OnButton1Click);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScriptEditor::OnButton2Click);
	//*)

    #define MARGIN_LINE_NUMBERS (0)
    #define MARGIN_FOLD (1)

    //styledTextCtrl->SetMarginType(1, 1);
    //styledTextCtrl->SetMarginWidth(1, 30);
    //styledTextCtrl->SetLexer(wxSTC_LEX_CPP);
    //styledTextCtrl->SetKeyWords(0, "if endif");

    wxStyledTextCtrl *text = styledTextCtrl;
    text->SetMarginWidth (MARGIN_LINE_NUMBERS, 50);
    text->StyleSetForeground (wxSTC_STYLE_LINENUMBER, wxColour (75, 75, 75) );
    text->StyleSetBackground (wxSTC_STYLE_LINENUMBER, wxColour (220, 220, 220));
    text->SetMarginType (MARGIN_LINE_NUMBERS, wxSTC_MARGIN_NUMBER);


    // ---- Enable code folding
    text->SetMarginType (MARGIN_FOLD, wxSTC_MARGIN_SYMBOL);
    text->SetMarginWidth(MARGIN_FOLD, 15);
    text->SetMarginMask (MARGIN_FOLD, wxSTC_MASK_FOLDERS);
    text->StyleSetBackground(MARGIN_FOLD, wxColor(200, 200, 200) );
    text->SetMarginSensitive(MARGIN_FOLD, true);

    // Properties found from http://www.scintilla.org/SciTEDoc.html
    text->SetProperty (wxT("fold"),         wxT("1") );
    text->SetProperty (wxT("fold.comment"), wxT("1") );
    text->SetProperty (wxT("fold.compact"), wxT("1") );

    wxColor grey( 100, 100, 100 );
    text->MarkerDefine (wxSTC_MARKNUM_FOLDER, wxSTC_MARK_ARROW );
    text->MarkerSetForeground (wxSTC_MARKNUM_FOLDER, grey);
    text->MarkerSetBackground (wxSTC_MARKNUM_FOLDER, grey);

    text->MarkerDefine (wxSTC_MARKNUM_FOLDEROPEN,    wxSTC_MARK_ARROWDOWN);
    text->MarkerSetForeground (wxSTC_MARKNUM_FOLDEROPEN, grey);
    text->MarkerSetBackground (wxSTC_MARKNUM_FOLDEROPEN, grey);

    text->MarkerDefine (wxSTC_MARKNUM_FOLDERSUB,     wxSTC_MARK_EMPTY);
    text->MarkerSetForeground (wxSTC_MARKNUM_FOLDERSUB, grey);
    text->MarkerSetBackground (wxSTC_MARKNUM_FOLDERSUB, grey);

    text->MarkerDefine (wxSTC_MARKNUM_FOLDEREND,     wxSTC_MARK_ARROW);
    text->MarkerSetForeground (wxSTC_MARKNUM_FOLDEREND, grey);
    text->MarkerSetBackground (wxSTC_MARKNUM_FOLDEREND, _T("WHITE"));

    text->MarkerDefine (wxSTC_MARKNUM_FOLDEROPENMID, wxSTC_MARK_ARROWDOWN);
    text->MarkerSetForeground (wxSTC_MARKNUM_FOLDEROPENMID, grey);
    text->MarkerSetBackground (wxSTC_MARKNUM_FOLDEROPENMID, _T("WHITE"));

    text->MarkerDefine (wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_EMPTY);
    text->MarkerSetForeground (wxSTC_MARKNUM_FOLDERMIDTAIL, grey);
    text->MarkerSetBackground (wxSTC_MARKNUM_FOLDERMIDTAIL, grey);

    text->MarkerDefine (wxSTC_MARKNUM_FOLDERTAIL,    wxSTC_MARK_EMPTY);
    text->MarkerSetForeground (wxSTC_MARKNUM_FOLDERTAIL, grey);
    text->MarkerSetBackground (wxSTC_MARKNUM_FOLDERTAIL, grey);
    // ---- End of code folding part

    text->SetWrapMode (wxSTC_WRAP_WORD); // other choice is wxSCI_WRAP_NONE

    text->StyleClearAll();
    text->SetLexer(wxSTC_LEX_CPP);
    text->StyleSetForeground (wxSTC_C_STRING,            wxColour(150,0,0));
    text->StyleSetForeground (wxSTC_C_PREPROCESSOR,      wxColour(165,105,0));
    text->StyleSetForeground (wxSTC_C_IDENTIFIER,        wxColour(40,0,60));
    text->StyleSetForeground (wxSTC_C_NUMBER,            wxColour(150,50,187));
    text->StyleSetForeground (wxSTC_C_CHARACTER,         wxColour(150,0,0));
    text->StyleSetForeground (wxSTC_C_WORD,              wxColour(0,0,150));
    text->StyleSetForeground (wxSTC_C_WORD2,             wxColour(0,150,0));
    text->StyleSetForeground (wxSTC_C_COMMENT,           wxColour(150,150,150));
    text->StyleSetForeground (wxSTC_C_COMMENTLINE,       wxColour(150,150,150));
    text->StyleSetForeground (wxSTC_C_COMMENTDOC,        wxColour(150,150,150));
    text->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORD, wxColour(0,0,200));
    text->StyleSetForeground (wxSTC_C_COMMENTDOCKEYWORDERROR, wxColour(0,0,200));
    text->StyleSetBold(wxSTC_C_WORD, true);
    text->StyleSetBold(wxSTC_C_WORD2, true);
    text->StyleSetBold(wxSTC_C_COMMENTDOCKEYWORD, true);

    text->SetKeyWords(0, wxT("if endif QuestProgress"));
    text->SetKeyWords(1, wxT("AddExp AddMoney SetQuestProgress EndDialogue"));

	Connect(ID_CUSTOM1,wxEVT_STC_CHANGE,(wxObjectEventFunction)&ScriptEditor::OnStyledTextCtrlKeyPressed);

    _assert(editingScriptIndex >= 0 && editingScriptIndex < (int)Editor::getInstance().Script.size(),
            "Script index out of bounds in ScriptEditor constructor.");
    styledTextCtrl->SetText(Editor::getInstance().Script[editingScriptIndex].script.c_str());
    StaticText1->SetLabel(Editor::getInstance().Script[editingScriptIndex].IDName.c_str());
}

ScriptEditor::~ScriptEditor()
{
	//(*Destroy(ScriptEditor)
	//*)
}

void ScriptEditor::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void ScriptEditor::OnStyledTextCtrlKeyPressed(wxStyledTextEvent& event)
{
    _assert(editingScriptIndex >= 0 && editingScriptIndex < (int)Editor::getInstance().Script.size(),
            "Script index out of bounds in OnStyledTextCtrlKeyPressed.");
    ScriptClass script = Editor::getInstance().Script[editingScriptIndex];
    script.script = styledTextCtrl->GetText();
    std::string err;
    if(!Editor::getInstance().compileScript(script, err)) {
        TextCtrl2->SetLabel(err.c_str());
    }
    else TextCtrl2->SetLabel("No errors");
}

void ScriptEditor::OnButton2Click(wxCommandEvent& event)
{
    _assert(editingScriptIndex >= 0 && editingScriptIndex < (int)Editor::getInstance().Script.size(),
            "Script index out of bounds in OnButton2Click.");
    Editor::getInstance().Script[editingScriptIndex].script = styledTextCtrl->GetText();
    Close();
}

void ScriptEditor::OnButton1Click(wxCommandEvent& event)
{
    Close();
}
