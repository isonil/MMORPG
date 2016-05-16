/***************************************************************
 * Name:      LauncherApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2012-08-30
 * Copyright:  ()
 * License:
 **************************************************************/

#include "LauncherApp.h"

//(*AppHeaders
#include "LauncherMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(LauncherApp);

bool LauncherApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	LauncherFrame* Frame = new LauncherFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
