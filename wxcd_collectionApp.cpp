/***************************************************************
 * Name:      wxcd_collectionApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Anders J. Andersen (andersj.andersen@gmail.com)
 * Created:   2019-05-12
 * Copyright: Anders J. Andersen ()
 * License:
 **************************************************************/

#include "wxcd_collectionApp.h"

//(*AppHeaders
#include "wxcd_collectionMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(wxcd_collectionApp);

bool wxcd_collectionApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    wxcd_collectionFrame* Frame = new wxcd_collectionFrame(0);
    Frame->Show();
    SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
