/***************************************************************
 * Name:      EditorMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2012-08-05
 * Copyright:  ()
 * License:
 **************************************************************/

#include "EditorMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(EditorFrame)
#include <wx/artprov.h>
#include <wx/bitmap.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

#include "../ScriptEditor.h"
#include "../QuestEditor.h"
#include "Editor.hpp"
#include <windows.h>

//(*IdInit(EditorFrame)
const long EditorFrame::ID_CUSTOM1 = wxNewId();
const long EditorFrame::ID_CHECKBOX4 = wxNewId();
const long EditorFrame::ID_CHECKBOX6 = wxNewId();
const long EditorFrame::ID_CHECKBOX7 = wxNewId();
const long EditorFrame::ID_CHECKBOX8 = wxNewId();
const long EditorFrame::ID_CHECKBOX9 = wxNewId();
const long EditorFrame::ID_BUTTON1 = wxNewId();
const long EditorFrame::ID_PANEL1 = wxNewId();
const long EditorFrame::ID_CHOICE1 = wxNewId();
const long EditorFrame::ID_CHOICE2 = wxNewId();
const long EditorFrame::ID_CUSTOM2 = wxNewId();
const long EditorFrame::ID_SCROLLBAR1 = wxNewId();
const long EditorFrame::ID_BITMAPBUTTON1 = wxNewId();
const long EditorFrame::ID_BITMAPBUTTON2 = wxNewId();
const long EditorFrame::ID_PANEL2 = wxNewId();
const long EditorFrame::ID_LISTBOX1 = wxNewId();
const long EditorFrame::ID_LISTBOX2 = wxNewId();
const long EditorFrame::ID_LISTBOX3 = wxNewId();
const long EditorFrame::ID_NOTEBOOK1 = wxNewId();
const long EditorFrame::ID_BITMAPBUTTON3 = wxNewId();
const long EditorFrame::ID_BITMAPBUTTON4 = wxNewId();
const long EditorFrame::ID_PANEL3 = wxNewId();
const long EditorFrame::ID_TEXTCTRL1 = wxNewId();
const long EditorFrame::ID_PANEL4 = wxNewId();
const long EditorFrame::ID_STATICTEXT1 = wxNewId();
const long EditorFrame::ID_GRID1 = wxNewId();
const long EditorFrame::ID_PANEL5 = wxNewId();
const long EditorFrame::ID_STATICTEXT2 = wxNewId();
const long EditorFrame::ID_CHECKLISTBOX1 = wxNewId();
const long EditorFrame::ID_STATICTEXT4 = wxNewId();
const long EditorFrame::ID_CHOICE3 = wxNewId();
const long EditorFrame::ID_PANEL6 = wxNewId();
const long EditorFrame::ID_AUITOOLBARITEM1 = wxNewId();
const long EditorFrame::ID_AUITOOLBARITEM4 = wxNewId();
const long EditorFrame::ID_AUITOOLBARITEM2 = wxNewId();
const long EditorFrame::ID_AUITOOLBARITEM3 = wxNewId();
const long EditorFrame::ID_AUITOOLBARITEM5 = wxNewId();
const long EditorFrame::ID_AUITOOLBARITEM6 = wxNewId();
const long EditorFrame::ID_AUITOOLBARITEM7 = wxNewId();
const long EditorFrame::ID_AUITOOLBAR1 = wxNewId();
const long EditorFrame::ID_LISTBOX4 = wxNewId();
const long EditorFrame::ID_PANEL7 = wxNewId();
const long EditorFrame::idMenuSave = wxNewId();
const long EditorFrame::idMenuQuit = wxNewId();
const long EditorFrame::idMenuAbout = wxNewId();
//*)

BEGIN_EVENT_TABLE(EditorFrame,wxFrame)
    //(*EventTable(EditorFrame)
    //*)
END_EVENT_TABLE()

EditorFrame::EditorFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(EditorFrame)
    wxFlexGridSizer* FlexGridSizer4;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxFlexGridSizer* FlexGridSizer7;
    wxFlexGridSizer* FlexGridSizer8;
    wxMenuItem* MenuItem6;
    wxFlexGridSizer* FlexGridSizer12;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("Editor"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1025,700));
    SetForegroundColour(wxColour(0,0,0));
    SetBackgroundColour(wxColour(238,238,238));
    AuiManager1 = new wxAuiManager(this, wxAUI_MGR_DEFAULT);
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(84,147), wxSize(290,247), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(300,300));
    FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer2->AddGrowableCol(0);
    FlexGridSizer2->AddGrowableRow(0);
    Custom1 = new WorldRenderCanvas(Panel1,ID_CUSTOM1,wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,_T("ID_CUSTOM1"));
    FlexGridSizer2->Add(Custom1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer9->AddGrowableCol(0);
    FlexGridSizer11 = new wxFlexGridSizer(0, 0, 0, 0);
    CheckBox4 = new wxCheckBox(Panel1, ID_CHECKBOX4, _("Grid"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX4"));
    CheckBox4->SetValue(false);
    FlexGridSizer11->Add(CheckBox4, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox6 = new wxCheckBox(Panel1, ID_CHECKBOX6, _("Minimap"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX6"));
    CheckBox6->SetValue(false);
    FlexGridSizer11->Add(CheckBox6, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox7 = new wxCheckBox(Panel1, ID_CHECKBOX7, _("Position"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX7"));
    CheckBox7->SetValue(false);
    FlexGridSizer11->Add(CheckBox7, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox8 = new wxCheckBox(Panel1, ID_CHECKBOX8, _("Scenery"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX8"));
    CheckBox8->SetValue(true);
    FlexGridSizer11->Add(CheckBox8, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CheckBox9 = new wxCheckBox(Panel1, ID_CHECKBOX9, _("Objects"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX9"));
    CheckBox9->SetValue(true);
    FlexGridSizer11->Add(CheckBox9, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9->Add(FlexGridSizer11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Import map"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer9->Add(Button1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(FlexGridSizer9, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
    Panel1->SetSizer(FlexGridSizer2);
    FlexGridSizer2->SetSizeHints(Panel1);
    AuiManager1->AddPane(Panel1, wxAuiPaneInfo().Name(_T("MAIN")).CenterPane().Caption(_("Pane caption")).BestSize(wxSize(290,247)).MinSize(wxSize(300,300)));
    Panel2 = new wxPanel(this, ID_PANEL2, wxPoint(49,96), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Panel2->SetMinSize(wxSize(180,-1));
    FlexGridSizer3 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer3->AddGrowableCol(0);
    FlexGridSizer3->AddGrowableRow(2);
    Choice1 = new wxChoice(Panel2, ID_CHOICE1, wxDefaultPosition, wxSize(188,21), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    Choice1->SetSelection( Choice1->Append(_("Tile types")) );
    Choice1->Append(_("Scenery types"));
    Choice1->Append(_("Object types"));
    Choice1->Append(_("NPC types"));
    Choice1->Append(_("Light source types"));
    Choice1->Append(_("Triggers"));
    Choice1->Append(_("Effects"));
    Choice1->Append(_("Zones"));
    FlexGridSizer3->Add(Choice1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Choice2 = new wxChoice(Panel2, ID_CHOICE2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE2"));
    FlexGridSizer3->Add(Choice2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    FlexGridSizer4 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer4->AddGrowableCol(0);
    FlexGridSizer4->AddGrowableRow(0);
    Custom2 = new EntitySelectCanvas(Panel2,ID_CUSTOM2,wxDefaultPosition,wxDefaultSize,0,wxDefaultValidator,_T("ID_CUSTOM2"));
    FlexGridSizer4->Add(Custom2, 1, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    ScrollBar1 = new wxScrollBar(Panel2, ID_SCROLLBAR1, wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_SCROLLBAR1"));
    ScrollBar1->SetScrollbar(0, 1, 10, 1);
    ScrollBar1->SetMinSize(wxSize(15,100));
    ScrollBar1->SetMaxSize(wxSize(15,-1));
    FlexGridSizer4->Add(ScrollBar1, 1, wxTOP|wxBOTTOM|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    FlexGridSizer3->Add(FlexGridSizer4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer5 = new wxFlexGridSizer(0, 2, 0, 0);
    BitmapButton1 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    BitmapButton1->SetDefault();
    FlexGridSizer5->Add(BitmapButton1, 0, wxALIGN_LEFT|wxALIGN_TOP, 0);
    BitmapButton2 = new wxBitmapButton(Panel2, ID_BITMAPBUTTON2, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_DELETE")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON2"));
    FlexGridSizer5->Add(BitmapButton2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer3->Add(FlexGridSizer5, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(FlexGridSizer3);
    FlexGridSizer3->Fit(Panel2);
    FlexGridSizer3->SetSizeHints(Panel2);
    AuiManager1->AddPane(Panel2, wxAuiPaneInfo().Name(_T("ENTITY_TYPE")).Caption(_("Entity type")).CaptionVisible().PinButton().Left().MinSize(wxSize(180,-1)));
    Panel3 = new wxPanel(this, ID_PANEL3, wxPoint(103,18), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    Panel3->SetMinSize(wxSize(150,0));
    FlexGridSizer7 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer7->AddGrowableCol(0);
    FlexGridSizer7->AddGrowableRow(0);
    Notebook1 = new wxNotebook(Panel3, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Notebook1->SetMinSize(wxSize(150,-1));
    ListBox1 = new wxListBox(Notebook1, ID_LISTBOX1, wxPoint(24,12), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    ListBox2 = new wxListBox(Notebook1, ID_LISTBOX2, wxPoint(36,121), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX2"));
    ListBox3 = new wxListBox(Notebook1, ID_LISTBOX3, wxPoint(95,8), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX3"));
    Notebook1->AddPage(ListBox1, _("Scripts"), false);
    Notebook1->AddPage(ListBox2, _("Quests"), false);
    Notebook1->AddPage(ListBox3, _("Texts"), false);
    FlexGridSizer7->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer8 = new wxFlexGridSizer(0, 3, 0, 0);
    BitmapButton3 = new wxBitmapButton(Panel3, ID_BITMAPBUTTON3, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_NEW")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON3"));
    FlexGridSizer8->Add(BitmapButton3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BitmapButton4 = new wxBitmapButton(Panel3, ID_BITMAPBUTTON4, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_DELETE")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON4"));
    FlexGridSizer8->Add(BitmapButton4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer7->Add(FlexGridSizer8, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(FlexGridSizer7);
    FlexGridSizer7->Fit(Panel3);
    FlexGridSizer7->SetSizeHints(Panel3);
    AuiManager1->AddPane(Panel3, wxAuiPaneInfo().Name(_T("NOTEBOOK")).Caption(_("Resources")).CaptionVisible().Right().MinSize(wxSize(150,0)));
    Panel4 = new wxPanel(this, ID_PANEL4, wxPoint(1,478), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL4"));
    Panel4->SetMinSize(wxSize(-1,70));
    FlexGridSizer10 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer10->AddGrowableCol(0);
    FlexGridSizer10->AddGrowableRow(0);
    TextCtrl1 = new wxTextCtrl(Panel4, ID_TEXTCTRL1, _("No errors"), wxDefaultPosition, wxSize(100,40), wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetForegroundColour(wxColour(159,11,15));
    FlexGridSizer10->Add(TextCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel4->SetSizer(FlexGridSizer10);
    FlexGridSizer10->Fit(Panel4);
    FlexGridSizer10->SetSizeHints(Panel4);
    AuiManager1->AddPane(Panel4, wxAuiPaneInfo().Name(_T("ERROR_LOG")).Caption(_("Error log")).CaptionVisible().Bottom().MinSize(wxSize(-1,70)));
    Panel5 = new wxPanel(this, ID_PANEL5, wxPoint(186,28), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    StaticText1 = new wxStaticText(Panel5, ID_STATICTEXT1, _("None"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    FlexGridSizer1->Add(StaticText1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Grid1 = new wxGrid(Panel5, ID_GRID1, wxDefaultPosition, wxSize(178,215), wxSUNKEN_BORDER, _T("ID_GRID1"));
    Grid1->CreateGrid(0,2);
    Grid1->SetMinSize(wxSize(-1,180));
    Grid1->EnableEditing(true);
    Grid1->EnableGridLines(true);
    Grid1->SetColLabelSize(1);
    Grid1->SetRowLabelSize(15);
    Grid1->SetColLabelValue(0, wxEmptyString);
    Grid1->SetColLabelValue(1, wxEmptyString);
    Grid1->SetDefaultCellFont( Grid1->GetFont() );
    Grid1->SetDefaultCellTextColour( Grid1->GetForegroundColour() );
    FlexGridSizer1->Add(Grid1, 1, wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    Panel5->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel5);
    FlexGridSizer1->SetSizeHints(Panel5);
    AuiManager1->AddPane(Panel5, wxAuiPaneInfo().Name(_T("ENTITY_PREFERENCES")).Caption(_("Entity preferences")).CaptionVisible().PinButton().Left());
    Panel6 = new wxPanel(this, ID_PANEL6, wxPoint(184,464), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL6"));
    FlexGridSizer6 = new wxFlexGridSizer(0, 1, 0, 0);
    FlexGridSizer6->AddGrowableCol(0);
    FlexGridSizer6->AddGrowableRow(1);
    StaticText2 = new wxStaticText(Panel6, ID_STATICTEXT2, _("Show"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    FlexGridSizer6->Add(StaticText2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CheckListBox1 = new wxCheckListBox(Panel6, ID_CHECKLISTBOX1, wxDefaultPosition, wxSize(140,170), 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
    CheckListBox1->Append(_("Grid"));
    CheckListBox1->Check(CheckListBox1->Append(_("Minimap")));
    CheckListBox1->Check(CheckListBox1->Append(_("Position")));
    CheckListBox1->Check(CheckListBox1->Append(_("Scenery")));
    CheckListBox1->Check(CheckListBox1->Append(_("Objects")));
    CheckListBox1->Check(CheckListBox1->Append(_("NPCs")));
    CheckListBox1->Check(CheckListBox1->Append(_("Players")));
    CheckListBox1->Check(CheckListBox1->Append(_("Lighting")));
    CheckListBox1->Check(CheckListBox1->Append(_("Triggers")));
    CheckListBox1->Check(CheckListBox1->Append(_("Effects")));
    CheckListBox1->Check(CheckListBox1->Append(_("Zones")));
    FlexGridSizer6->Add(CheckListBox1, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText4 = new wxStaticText(Panel6, ID_STATICTEXT4, _("Render type"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    FlexGridSizer6->Add(StaticText4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Choice3 = new wxChoice(Panel6, ID_CHOICE3, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE3"));
    Choice3->SetSelection( Choice3->Append(_("Editor")) );
    Choice3->Append(_("Color Map"));
    Choice3->Append(_("Normal Map"));
    Choice3->Append(_("Height Map"));
    FlexGridSizer6->Add(Choice3, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel6->SetSizer(FlexGridSizer6);
    FlexGridSizer6->Fit(Panel6);
    FlexGridSizer6->SetSizeHints(Panel6);
    AuiManager1->AddPane(Panel6, wxAuiPaneInfo().Name(_T("OPTIONS")).Caption(_("Options")).CaptionVisible().Right().Resizable(false));
    AuiToolBar1 = new wxAuiToolBar(this, ID_AUITOOLBAR1, wxPoint(183,22), wxDefaultSize, wxAUI_TB_DEFAULT_STYLE);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM1, _("Save"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FILE_SAVE")),wxART_BUTTON), wxNullBitmap, wxITEM_NORMAL, _("Save project"), wxEmptyString, NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM4, _("Help"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_QUESTION")),wxART_BUTTON), wxNullBitmap, wxITEM_NORMAL, _("Help"), wxEmptyString, NULL);
    AuiToolBar1->AddSeparator();
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM2, _("Undo"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_UNDO")),wxART_BUTTON), wxNullBitmap, wxITEM_NORMAL, _("Undo"), wxEmptyString, NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM3, _("Redo"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_REDO")),wxART_BUTTON), wxNullBitmap, wxITEM_NORMAL, _("Redo"), wxEmptyString, NULL);
    AuiToolBar1->AddSeparator();
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM5, _("Cut"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_CUT")),wxART_BUTTON), wxNullBitmap, wxITEM_NORMAL, _("Cut"), wxEmptyString, NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM6, _("Copy"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_COPY")),wxART_BUTTON), wxNullBitmap, wxITEM_NORMAL, _("Copy"), wxEmptyString, NULL);
    AuiToolBar1->AddTool(ID_AUITOOLBARITEM7, _("Paste"), wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_PASTE")),wxART_BUTTON), wxNullBitmap, wxITEM_NORMAL, _("Paste"), wxEmptyString, NULL);
    AuiToolBar1->Realize();
    AuiManager1->AddPane(AuiToolBar1, wxAuiPaneInfo().Name(_T("TOOLBAR")).ToolbarPane().Caption(_("Toolbar")).Layer(10).Row(1).Top().Gripper());
    Panel7 = new wxPanel(this, ID_PANEL7, wxPoint(184,37), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL7"));
    Panel7->SetMinSize(wxSize(100,100));
    FlexGridSizer12 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer12->AddGrowableCol(0);
    FlexGridSizer12->AddGrowableCol(1);
    FlexGridSizer12->AddGrowableRow(0);
    ListBox4 = new wxListBox(Panel7, ID_LISTBOX4, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX4"));
    ListBox4->Append(_("Placed scenery (Wall)"));
    ListBox4->Append(_("Placed scenery (Wall)"));
    ListBox4->Append(_("Placed tile (Grass)"));
    ListBox4->Append(_("Deleted tile (Grass)"));
    FlexGridSizer12->Add(ListBox4, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel7->SetSizer(FlexGridSizer12);
    FlexGridSizer12->Fit(Panel7);
    FlexGridSizer12->SetSizeHints(Panel7);
    AuiManager1->AddPane(Panel7, wxAuiPaneInfo().Name(_T("HISTORY")).Caption(_("History")).CaptionVisible().Float().Top().MinSize(wxSize(100,100)));
    AuiManager1->Update();
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem6 = new wxMenuItem(Menu1, idMenuSave, _("Save\tCTRL+S"), _("Save current project"), wxITEM_NORMAL);
    Menu1->Append(MenuItem6);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt+F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);

    Custom1->Connect(wxEVT_KEY_UP,(wxObjectEventFunction)&EditorFrame::OnCustom1KeyUp,0,this);
    Custom1->Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorFrame::OnCustom1SetFocus,0,this);
    Custom1->Connect(wxEVT_KILL_FOCUS,(wxObjectEventFunction)&EditorFrame::OnCustom1KillFocus,0,this);
    Custom1->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&EditorFrame::OnCustom1LeftDown,0,this);
    Custom1->Connect(wxEVT_RIGHT_DOWN,(wxObjectEventFunction)&EditorFrame::OnCustom1RightDown,0,this);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditorFrame::OnButton1Click1);
    Custom2->Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorFrame::OnCustom2SetFocus,0,this);
    Custom2->Connect(wxEVT_KILL_FOCUS,(wxObjectEventFunction)&EditorFrame::OnCustom2KillFocus,0,this);
    Custom2->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&EditorFrame::OnCustom2LeftDown,0,this);
    Custom2->Connect(wxEVT_LEFT_DCLICK,(wxObjectEventFunction)&EditorFrame::OnCustom2LeftDClick,0,this);
    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditorFrame::OnBitmapButton1Click);
    Connect(ID_BITMAPBUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditorFrame::OnBitmapButton2Click);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&EditorFrame::OnListBox1Select);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&EditorFrame::OnListBox1DClick);
    Connect(ID_LISTBOX2,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&EditorFrame::OnListBox2Select);
    Connect(ID_LISTBOX2,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&EditorFrame::OnListBox2DClick);
    Connect(ID_LISTBOX3,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&EditorFrame::OnListBox3Select);
    Connect(ID_NOTEBOOK1,wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED,(wxObjectEventFunction)&EditorFrame::OnNotebook1PageChanged2);
    Connect(ID_BITMAPBUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditorFrame::OnBitmapButton3Click);
    Connect(ID_BITMAPBUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&EditorFrame::OnBitmapButton4Click);
    Connect(ID_GRID1,wxEVT_GRID_CELL_CHANGE,(wxObjectEventFunction)&EditorFrame::OnGrid1CellChange);
    Connect(ID_GRID1,wxEVT_GRID_EDITOR_SHOWN,(wxObjectEventFunction)&EditorFrame::OnGrid1EditorShown);
    Connect(idMenuSave,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorFrame::OnSave);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&EditorFrame::OnAbout);
    Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&EditorFrame::OnSetFocus);
    //*)

    //new WorldRenderCanvas(this,wxID_ANY,wxPoint(0, 0), wxSize(500, 500),0,wxDefaultValidator,_T("ID_CUSTOM1"));

    Grid1->DisableDragRowSize();
    //Grid1->SetReadOnly(0, 0);
    //Grid1->SetCellRenderer(0, 0, new wxGridCellBoolRenderer);
    //Grid1->SetCellEditor(0, 0, new wxGridCellBoolEditor);

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOW);

    wxMainWindow = this;
    wxEntitySelection1 = Choice1;
    wxEntitySelection2 = Choice2;
    wxEntityText = StaticText1;
    wxEntityGrid = Grid1;
    wxScriptsListBox = ListBox1;
    wxQuestsListBox = ListBox2;
    wxTextsListBox = ListBox3;
    wxGridCheckBox = CheckBox4;
    wxMinimapCheckBox = CheckBox6;
    wxDisplaySelection = Choice3;
    wxErrorLogEditBox = TextCtrl1;

    Editor::getInstance().init();
    info("Editor running.");

    /*m_pImageList = new wxImageList(16,16);
    wxIcon icon;
    icon.LoadFile(wxT("res/user_offline.ico"), wxBITMAP_TYPE_ICO);
    m_pImageList->Add(icon);
    SetImageList(m_pImageList, wxIMAGE_LIST_SMALL);
    SetItemImage(item, 0);*/
}

EditorFrame::~EditorFrame()
{
    //(*Destroy(EditorFrame)
    //*)
}

void EditorFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void EditorFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox(_("Editor"), _("About"));
}

void EditorFrame::OnButton1Click(wxCommandEvent& event)
{
}

void EditorFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void EditorFrame::OnGLCanvas1Paint(wxPaintEvent& event)
{
}

void EditorFrame::OnCheckBox1Click(wxCommandEvent& event)
{
}

void EditorFrame::OnListBox1Select(wxCommandEvent& event)
{
    if(ListBox1->GetSelection() < 0) return;

    StaticText1->SetLabel("Script (double click to edit script)");
    if(Grid1->GetNumberRows()) {
        Grid1->DeleteRows(0, Grid1->GetNumberRows());
    }
    Grid1->InsertRows(0, 1);
    for(int i=0; i<1; ++i) {
        Grid1->SetReadOnly(i, 0);
    }
    Grid1->SetCellValue(0, 0, _("IDName"));

    selectionEntityType = ENTITY_TYPE_SCRIPT;
    int index = -1;
    for(size_t i=0, j=0; i<Editor::getInstance().Script.size(); ++i) {
        if(Editor::getInstance().Script[i].isLoaded) ++j;
        if(j == ListBox1->GetSelection()+1) {
            index = (int)i;
            break;
        }
    }
    _assert(index >= 0, "Could not find corresponding entity index.");

    Grid1->SetCellValue(0, 1, Editor::getInstance().Script[index].IDName);

    selectionEntityIndex = index;
    selectionListBoxSelectionIndex = ListBox1->GetSelection();
}

void EditorFrame::OnListBox2Select(wxCommandEvent& event)
{
    if(ListBox2->GetSelection() < 0) return;

    StaticText1->SetLabel("Quest (double click to edit texts)");
    if(Grid1->GetNumberRows()) {
        Grid1->DeleteRows(0, Grid1->GetNumberRows());
    }
    Grid1->InsertRows(0, 3);
    for(int i=0; i<3; ++i) {
        Grid1->SetReadOnly(i, 0);
    }
    Grid1->SetCellValue(0, 0, _("IDName"));
    Grid1->SetCellValue(1, 0, _("name"));
    Grid1->SetCellValue(2, 0, _("questType"));

    selectionEntityType = ENTITY_TYPE_QUEST;
    int index = -1;
    for(size_t i=0, j=0; i<Editor::getInstance().Quest.size(); ++i) {
        if(Editor::getInstance().Quest[i].isLoaded) ++j;
        if(j == ListBox2->GetSelection()+1) {
            index = (int)i;
            break;
        }
    }
    _assert(index >= 0, "Could not find corresponding entity index.");

    Grid1->SetCellValue(0, 1, Editor::getInstance().Quest[index].IDName);
    Grid1->SetCellValue(1, 1, Editor::getInstance().Quest[index].name);
    Grid1->SetCellValue(2, 1, Editor::getInstance().intToString(Editor::getInstance().Quest[index].questType));

    selectionEntityIndex = index;
    selectionListBoxSelectionIndex = ListBox2->GetSelection();
}

void EditorFrame::OnListBox3Select(wxCommandEvent& event)
{
    if(ListBox3->GetSelection() < 0) return;

    StaticText1->SetLabel("Text preferences");
    if(Grid1->GetNumberRows()) {
        Grid1->DeleteRows(0, Grid1->GetNumberRows());
    }
    Grid1->InsertRows(0, 1);
    for(int i=0; i<1; ++i) {
        Grid1->SetReadOnly(i, 0);
    }
    Grid1->SetCellValue(0, 0, _("text"));

    selectionEntityType = ENTITY_TYPE_TEXT;
    int index = -1;
    for(size_t i=0, j=0; i<Editor::getInstance().Text.size(); ++i) {
        if(Editor::getInstance().Text[i].isLoaded) ++j;
        if(j == ListBox3->GetSelection()+1) {
            index = (int)i;
            break;
        }
    }
    _assert(index >= 0, "Could not find corresponding entity index.");

    selectionEntityIndex = index;
    selectionListBoxSelectionIndex = ListBox3->GetSelection();
}

void EditorFrame::OnNotebook1PageChanged2(wxNotebookEvent& event)
{
    if(event.GetSelection() == 0) {
        ListBox1->SetSelection(-1);
    }
    else if(event.GetSelection() == 1) {
        ListBox2->SetSelection(-1);
    }
    else if(event.GetSelection() == 2) {
        ListBox3->SetSelection(-1);
    }
}

void EditorFrame::OnSave(wxCommandEvent& event)
{
    Editor::getInstance().save();
    // We have to update globalTime because saving takes long time.
    // If we didn't do this, delta time between two frames would be huge.
    globalTime = globalClock.getElapsedTime().asMilliseconds();
    saved_timer = globalTime+4000.0;
}

void EditorFrame::OnGrid1CellChange(wxGridEvent& event)
{
    Editor::getInstance().changeEntityValue(event);
}

void EditorFrame::OnGrid1EditorShown(wxGridEvent& event)
{
    const char *str = ((wxGrid*)event.GetEventObject())->GetCellValue(event.GetRow(),
                                                                      event.GetCol()).c_str();
}

void EditorFrame::OnListBox1DClick(wxCommandEvent& event)
{
    if(selectionEntityType == ENTITY_TYPE_SCRIPT) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().Script.size(),
                "Script index out of bounds in OnListBox1DClick.");
        editingScriptIndex = selectionEntityIndex;
        ScriptEditor dialog(this);
        dialog.ShowModal();
        Editor::getInstance().updateErrorLog();
    }
}

void EditorFrame::OnCustom1SetFocus(wxFocusEvent& event)
{
    Custom1->isFocused = true;
}

void EditorFrame::OnCustom1KillFocus(wxFocusEvent& event)
{
    Custom1->isFocused = false;
}

void EditorFrame::OnCustom2SetFocus(wxFocusEvent& event)
{
    Custom2->isFocused = true;
}

void EditorFrame::OnCustom2KillFocus(wxFocusEvent& event)
{
    Custom2->isFocused = false;
}

void EditorFrame::OnCustom1LeftDown(wxMouseEvent& event)
{
    Custom1->SetFocus();
    Editor::getInstance().onClick(event.GetPosition().x, event.GetPosition().y);
}

void EditorFrame::OnCustom2LeftDown(wxMouseEvent& event)
{
    Custom2->SetFocus();
    Editor::getInstance().onEntitySelectClick(event.GetPosition().x, event.GetPosition().y, false);
}

void EditorFrame::OnCustom1RightDown(wxMouseEvent& event)
{
    Custom1->SetFocus();
    Editor::getInstance().onRClick(event.GetPosition().x, event.GetPosition().y);
}

void EditorFrame::OnBitmapButton1Click(wxCommandEvent& event)
{
    if(Choice1->GetSelection() == 0) {
        Editor::getInstance().TileType.push_back(TileTypeClass());
        Editor::getInstance().TileType.back().isLoaded = true;
    }
    else if(Choice1->GetSelection() == 1) {
        Editor::getInstance().SceneryType.push_back(SceneryTypeClass());
        Editor::getInstance().SceneryType.back().isLoaded = true;
    }
    else if(Choice1->GetSelection() == 2) {
        Editor::getInstance().ObjectType.push_back(ObjectTypeClass());
        Editor::getInstance().ObjectType.back().isLoaded = true;
    }
    else if(Choice1->GetSelection() == 3) {
        Editor::getInstance().NPCType.push_back(NPCTypeClass());
        Editor::getInstance().NPCType.back().isLoaded = true;
    }
}

void EditorFrame::OnBitmapButton2Click(wxCommandEvent& event)
{
    if(selectionEntityType == ENTITY_TYPE_TILE_TYPE) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().TileType.size(),
                "Tile type index out of bounds in OnBitmapButton2Click.");
        Editor::getInstance().removeTileType(selectionEntityIndex);
        selectionEntityType = ENTITY_TYPE_NONE;
        Editor::getInstance().resetEntityPreferencesGrid();
    }
    else if(selectionEntityType == ENTITY_TYPE_SCENERY_TYPE) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().SceneryType.size(),
                "Scenery type index out of bounds in OnBitmapButton2Click.");
        Editor::getInstance().removeSceneryType(selectionEntityIndex);
        selectionEntityType = ENTITY_TYPE_NONE;
        Editor::getInstance().resetEntityPreferencesGrid();
    }
    else if(selectionEntityType == ENTITY_TYPE_OBJECT_TYPE) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().ObjectType.size(),
                "Object type index out of bounds in OnBitmapButton2Click.");
        Editor::getInstance().removeObjectType(selectionEntityIndex);
        selectionEntityType = ENTITY_TYPE_NONE;
        Editor::getInstance().resetEntityPreferencesGrid();
    }
    else if(selectionEntityType == ENTITY_TYPE_NPC_TYPE) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().NPCType.size(),
                "NPC type index out of bounds in OnBitmapButton2Click.");
        Editor::getInstance().removeNPCType(selectionEntityIndex);
        selectionEntityType = ENTITY_TYPE_NONE;
        Editor::getInstance().resetEntityPreferencesGrid();
    }
}

void EditorFrame::OnCustom1KeyUp(wxKeyEvent& event)
{
    if(event.GetKeyCode() == WXK_DELETE) {
        if(selectionEntityType == ENTITY_TYPE_SCENERY) {
            _assert(!Editor::getInstance().isOutOfMap(selectionEntityX, selectionEntityY),
                    "Entity position out of map in OnCustom1KeyUp.");
            Editor::getInstance().Tile[selectionEntityX][selectionEntityY].sceneryType = -1;
            selectionEntityType = ENTITY_TYPE_NONE;
            Editor::getInstance().resetEntityPreferencesGrid();
        }
        else if(selectionEntityType == ENTITY_TYPE_OBJECT) {
            _assert(!Editor::getInstance().isOutOfMap(selectionEntityX, selectionEntityY),
                    "Entity position out of map in OnCustom1KeyUp.");
            Editor::getInstance().Tile[selectionEntityX][selectionEntityY].object.pop_back();
            selectionEntityType = ENTITY_TYPE_NONE;
            Editor::getInstance().resetEntityPreferencesGrid();
        }
        else if(selectionEntityType == ENTITY_TYPE_NPC) {
            _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().NPC.size(),
                    "NPC index out of bounds in OnCustom1KeyUp.");
            Editor::getInstance().NPC.erase(Editor::getInstance().NPC.begin()+selectionEntityIndex);
            selectionEntityType = ENTITY_TYPE_NONE;
            Editor::getInstance().resetEntityPreferencesGrid();
        }
    }

    if(selectionEntityType == ENTITY_TYPE_NPC) {
        int key = event.GetKeyCode()-'0';
        if(key >= 1 && key <= 9) {
            Editor::getInstance().changeNPCMovementCheckpoint(selectionEntityIndex, key-1);
        }
    }
}

void EditorFrame::OnSetFocus(wxFocusEvent& event)
{
    wxErrorLogEditBox->SetFocus();
}

void EditorFrame::OnCustom2LeftDClick(wxMouseEvent& event)
{
    Custom2->SetFocus();
    Editor::getInstance().onEntitySelectClick(event.GetPosition().x, event.GetPosition().y, true);
}

void EditorFrame::OnListBox2DClick(wxCommandEvent& event)
{
    if(selectionEntityType == ENTITY_TYPE_QUEST) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().Quest.size(),
                "Quest index out of bounds in OnListBox2DClick.");
        editingQuestIndex = selectionEntityIndex;
        QuestEditor dialog(this);
        dialog.ShowModal();
    }
}

void EditorFrame::OnBitmapButton4Click(wxCommandEvent& event)
{
    if(selectionEntityType == ENTITY_TYPE_SCRIPT) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().Script.size(),
                "Script index out of bounds in OnBitmapButton4Click.");

        for(size_t i=0; i<Editor::getInstance().NPCType.size(); ++i) {
            for(size_t j=0; j<Editor::getInstance().NPCType[i].dialogueBlock.size(); ++j) {
                if(Editor::getInstance().NPCType[i].dialogueBlock[j].scriptIndex == selectionEntityIndex) {
                    Editor::getInstance().NPCType[i].dialogueBlock[j].scriptIndex = -1;
                }
            }
        }

        Editor::getInstance().Script[selectionEntityIndex].isLoaded = false;
        if(wxScriptsListBox->GetSelection() >= 0) {
            wxScriptsListBox->Delete(wxScriptsListBox->GetSelection());
        }

        Editor::getInstance().updateErrorLog();
        Editor::getInstance().resetEntityPreferencesGrid();
    }
    else if(selectionEntityType == ENTITY_TYPE_QUEST) {
        _assert(selectionEntityIndex >= 0 && selectionEntityIndex < (int)Editor::getInstance().Quest.size(),
                "Quest index out of bounds in OnBitmapButton4Click.");

        for(size_t i=0; i<Editor::getInstance().NPCType.size(); ++i) {
            for(size_t j=0; j<Editor::getInstance().NPCType[i].dialogueBlock.size(); ++j) {
                for(size_t k=0; k<Editor::getInstance().NPCType[i].dialogueBlock[j].option.size(); ++k) {
                    if(Editor::getInstance().NPCType[i].dialogueBlock[j].option[k].requiredQuestProgressIndex == selectionEntityIndex) {
                        Editor::getInstance().NPCType[i].dialogueBlock[j].option[k].requiredQuestProgressIndex = -1;
                        Editor::getInstance().NPCType[i].dialogueBlock[j].option[k].requiredQuestProgressFrom = 0;
                        Editor::getInstance().NPCType[i].dialogueBlock[j].option[k].requiredQuestProgressTo = 0;
                    }
                }
            }
        }

        Editor::getInstance().Quest[selectionEntityIndex].isLoaded = false;
        if(wxQuestsListBox->GetSelection() >= 0) {
            wxQuestsListBox->Delete(wxQuestsListBox->GetSelection());
        }

        Editor::getInstance().updateErrorLog();
        Editor::getInstance().resetEntityPreferencesGrid();
    }
}

void EditorFrame::OnBitmapButton3Click(wxCommandEvent& event)
{
    if(Notebook1->GetSelection() == 0) {
        Editor::getInstance().Script.push_back(ScriptClass());
        Editor::getInstance().Script.back().isLoaded = true;

        std::string IDName = "NEW_1";
        int count = 1;

        while(Editor::getInstance().getScriptIDByIDName(IDName) >= 0) {
            ++count;
            IDName = "NEW_"+Editor::getInstance().intToString(count);
        }
        Editor::getInstance().Script.back().IDName = IDName;
        wxScriptsListBox->Append(IDName);
    }
    else if(Notebook1->GetSelection() == 1) {
        Editor::getInstance().Quest.push_back(QuestClass());
        Editor::getInstance().Quest.back().isLoaded = true;

        std::string IDName = "NEW_1";
        int count = 1;

        while(Editor::getInstance().getQuestIDByIDName(IDName) >= 0) {
            ++count;
            IDName = "NEW_"+Editor::getInstance().intToString(count);
        }
        Editor::getInstance().Quest.back().IDName = IDName;
        wxQuestsListBox->Append(IDName);
    }
}

void EditorFrame::OnButton1Click1(wxCommandEvent& event)
{
    sf::Image img;
    loadImage(img, "map.png");
    Editor::getInstance().Tile.clear();
    Editor::getInstance().Tile.resize(img.getSize().x, std::vector <TileClass> (img.getSize().y));
    srand(1000);
    for(unsigned int i=0; i<img.getSize().x; ++i) {
        for(unsigned int j=0; j<img.getSize().y; ++j) {
            if(img.getPixel(i, j).r > 128) {
                Editor::getInstance().Tile[i][j].tileType = rand()%1;
                if(rand()%10 == 0 && i && j &&
                   Editor::getInstance().Tile[i-1][j].tileType >= 0 &&
                   Editor::getInstance().Tile[i][j-1].tileType >= 0 &&
                   Editor::getInstance().Tile[i-1][j-1].tileType >= 0) {
                    int scenery = rand()%5;
                    if(scenery >= 3) scenery += 4;
                    Editor::getInstance().Tile[i][j].sceneryType = scenery;
                }
            }
        }
    }
}
