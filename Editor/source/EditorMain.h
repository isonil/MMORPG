/***************************************************************
 * Name:      EditorMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2012-08-05
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef EDITORMAIN_H
#define EDITORMAIN_H

//(*Headers(EditorFrame)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checklst.h>
#include <wx/checkbox.h>
#include <wx/listbox.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/grid.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/scrolbar.h>
#include <wx/frame.h>
//*)

#include <SFML/Graphics.hpp>
#include "wxSFMLCanvas.hpp"

class EditorFrame: public wxFrame
{
    public:
        EditorFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~EditorFrame();

    private:

        //(*Handlers(EditorFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnGLCanvas1Paint(wxPaintEvent& event);
        void OnNotebook1PageChanged(wxNotebookEvent& event);
        void OnCheckBox1Click(wxCommandEvent& event);
        void OnNotebook1PageChanged1(wxNotebookEvent& event);
        void OnListBox1Select(wxCommandEvent& event);
        void OnListBox2Select(wxCommandEvent& event);
        void OnListBox3Select(wxCommandEvent& event);
        void OnNotebook1PageChanged2(wxNotebookEvent& event);
        void OnSave(wxCommandEvent& event);
        void OnGrid1CellChange(wxGridEvent& event);
        void OnGrid1EditorShown(wxGridEvent& event);
        void OnListBox1DClick(wxCommandEvent& event);
        void OnCustom1SetFocus(wxFocusEvent& event);
        void OnCustom1KillFocus(wxFocusEvent& event);
        void OnCustom2SetFocus(wxFocusEvent& event);
        void OnCustom2KillFocus(wxFocusEvent& event);
        void OnCustom1LeftDown(wxMouseEvent& event);
        void OnCustom2LeftDown(wxMouseEvent& event);
        void OnCustom1RightDown(wxMouseEvent& event);
        void OnBitmapButton1Click(wxCommandEvent& event);
        void OnBitmapButton2Click(wxCommandEvent& event);
        void OnCustom1KeyUp(wxKeyEvent& event);
        void OnSetFocus(wxFocusEvent& event);
        void OnCustom2LeftDClick(wxMouseEvent& event);
        void OnListBox2DClick(wxCommandEvent& event);
        void OnBitmapButton4Click(wxCommandEvent& event);
        void OnBitmapButton3Click(wxCommandEvent& event);
        void OnButton1Click1(wxCommandEvent& event);
        //*)

        //(*Identifiers(EditorFrame)
        static const long ID_CUSTOM1;
        static const long ID_CHECKBOX4;
        static const long ID_CHECKBOX6;
        static const long ID_CHECKBOX7;
        static const long ID_CHECKBOX8;
        static const long ID_CHECKBOX9;
        static const long ID_BUTTON1;
        static const long ID_PANEL1;
        static const long ID_CHOICE1;
        static const long ID_CHOICE2;
        static const long ID_CUSTOM2;
        static const long ID_SCROLLBAR1;
        static const long ID_BITMAPBUTTON1;
        static const long ID_BITMAPBUTTON2;
        static const long ID_PANEL2;
        static const long ID_LISTBOX1;
        static const long ID_LISTBOX2;
        static const long ID_LISTBOX3;
        static const long ID_NOTEBOOK1;
        static const long ID_BITMAPBUTTON3;
        static const long ID_BITMAPBUTTON4;
        static const long ID_PANEL3;
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL4;
        static const long ID_STATICTEXT1;
        static const long ID_GRID1;
        static const long ID_PANEL5;
        static const long ID_STATICTEXT2;
        static const long ID_CHECKLISTBOX1;
        static const long ID_STATICTEXT4;
        static const long ID_CHOICE3;
        static const long ID_PANEL6;
        static const long ID_AUITOOLBARITEM1;
        static const long ID_AUITOOLBARITEM4;
        static const long ID_AUITOOLBARITEM2;
        static const long ID_AUITOOLBARITEM3;
        static const long ID_AUITOOLBARITEM5;
        static const long ID_AUITOOLBARITEM6;
        static const long ID_AUITOOLBARITEM7;
        static const long ID_AUITOOLBAR1;
        static const long ID_LISTBOX4;
        static const long ID_PANEL7;
        static const long idMenuSave;
        static const long idMenuQuit;
        static const long idMenuAbout;
        //*)

        //(*Declarations(EditorFrame)
        wxAuiManager* AuiManager1;
        wxAuiToolBar* AuiToolBar1;
        wxPanel* Panel5;
        wxCheckBox* CheckBox9;
        wxNotebook* Notebook1;
        wxStaticText* StaticText2;
        wxPanel* Panel4;
        wxListBox* ListBox4;
        wxChoice* Choice3;
        wxButton* Button1;
        wxScrollBar* ScrollBar1;
        WorldRenderCanvas* Custom1;
        wxCheckListBox* CheckListBox1;
        wxCheckBox* CheckBox6;
        wxBitmapButton* BitmapButton2;
        wxPanel* Panel1;
        wxStaticText* StaticText1;
        wxGrid* Grid1;
        wxBitmapButton* BitmapButton1;
        wxPanel* Panel6;
        wxPanel* Panel3;
        wxListBox* ListBox3;
        wxPanel* Panel7;
        wxCheckBox* CheckBox4;
        wxBitmapButton* BitmapButton4;
        wxCheckBox* CheckBox8;
        wxListBox* ListBox2;
        wxTextCtrl* TextCtrl1;
        wxCheckBox* CheckBox7;
        wxBitmapButton* BitmapButton3;
        EntitySelectCanvas* Custom2;
        wxPanel* Panel2;
        wxStaticText* StaticText4;
        wxChoice* Choice1;
        wxChoice* Choice2;
        wxListBox* ListBox1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // EDITORMAIN_H
