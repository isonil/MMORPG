/***************************************************************
 * Name:      LauncherMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2012-08-30
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef LAUNCHERMAIN_H
#define LAUNCHERMAIN_H

//(*Headers(LauncherFrame)
#include <wx/stattext.h>
#include "HtmlWindow.hpp"
#include <wx/frame.h>
#include <wx/gauge.h>
//*)

class LauncherFrame: public wxFrame
{
    public:

        LauncherFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~LauncherFrame();

    private:

        //(*Handlers(LauncherFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        //*)

        //(*Identifiers(LauncherFrame)
        static const long ID_GAUGE1;
        static const long ID_STATICTEXT1;
        static const long ID_CUSTOM1;
        //*)

        //(*Declarations(LauncherFrame)
        wxGauge* Gauge1;
        wxStaticText* StaticText1;
        HtmlWindow* Custom1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // LAUNCHERMAIN_H
