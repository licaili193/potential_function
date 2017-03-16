#ifndef GRAPHTEST_H
#define GRAPHTEST_H

// -*- C++ -*- generated by wxGlade 0.6.3 on Fri Nov 20 21:30:11 2009

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/timer.h>

#include "visualizer.h"
#include "sphere.h"
#include "sphereWorld.h"
#include "square.h"
#include "starWorld.h"
#include "purgedWorld.h"

#include "worldManager.h"
#include "roslistener.h"

// begin wxGlade: ::extracode
// end wxGlade

class MainFrame: public wxFrame {
    void OnExit(wxCommandEvent& event);

    wxTimer* m_pTimer;
public:
    // begin wxGlade: MainFrame::ids
    // end wxGlade

    MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_FRAME_STYLE);

	virtual void OnPaint(wxPaintEvent &event);
    // begin wxGlade: MainFrame::methods
    void set_properties();
    void do_layout();
    // end wxGlade

    //THE PLOT THINGS
	Visualizer thePlot;
    WorldManager theWorlds;

    // begin wxGlade: MainFrame::attributes
    wxStaticBox* sizer_1_staticbox;
    wxPanel* graphPanel;
    // end wxGlade

    void CmdPhraser(params* pCmd);

    void OnTimerTimeout(wxTimerEvent& event);

protected:
    DECLARE_EVENT_TABLE()
}; // wxGlade: end class

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_PAINT(MainFrame::OnPaint)
    EVT_TIMER(10,MainFrame::OnTimerTimeout)
END_EVENT_TABLE();

#endif // GRAPHTEST_H
