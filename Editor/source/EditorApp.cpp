/***************************************************************
 * Name:      EditorApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2012-08-05
 * Copyright:  ()
 * License:
 **************************************************************/

#include "EditorApp.h"

//(*AppHeaders
#include "EditorMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(EditorApp);

bool EditorApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	EditorFrame* Frame = new EditorFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
