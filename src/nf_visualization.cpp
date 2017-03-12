#include "ros/ros.h"
#include "std_msgs/String.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/timer.h>
#include <mgl2/mgl.h>

#include "nf_visualization.h"
#include "roslistener.h"
#include "visualizer.h"

#include <iostream>

#include "sphere.h"
#include "world.h"

using namespace std;

MainFrame::MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: MainFrame::MainFrame
    sizer_1_staticbox = new wxStaticBox(this, -1, wxT("sizer_1"));
    graphPanel = new wxPanel(this, wxID_ANY);
    graphPanel->SetMinClientSize(wxSize(800,800));


    theSphere.SetCenter(0,0);
    theSphere.SetRadius(6);
    theSphere1.SetCenter(2,2);
    theSphere1.SetRadius(0.5);
    theSphere2.SetCenter(-2,-2);
    theSphere2.SetRadius(0.5);
    theWorld.SetFrame(-6.2,6.2,-6.2,6.2,0.02);
    theWorld.mainObs = &theSphere;
    theWorld.obsArray.push_back(&theSphere1);
    theWorld.obsArray.push_back(&theSphere2);
    theWorld.destX = -3.2;
    theWorld.destY = 3.2;
    theWorld.rBubble = 0.2;
    theWorld.kappa = 4;

    theSquare.SetCenter(0,0);
    theSquare.SetRadius(4);
    theSquare.SetScale(1,1);
    theSquare.parentObs = &theSphere;
    theSquare1.SetCenter(2,2);
    theSquare1.SetRadius(0.6);
    theSquare1.SetScale(1,1);
    theSquare1.parentObs = &theSphere1;
    theSquare2.SetCenter(-2,-2);
    theSquare2.SetRadius(0.6);
    theSquare2.SetScale(1,1);
    theSquare2.parentObs = &theSphere2;
    theWorld1.SetFrame(-4.2,4.2,-4.2,4.2,0.02);
    theWorld1.mainObs = &theSquare;
    theWorld1.obsArray.push_back(&theSquare1);
    theWorld1.obsArray.push_back(&theSquare2);
    theWorld1.destX = -3.2;
    theWorld1.destY = 3.2;
    theWorld1.rBubble = 0.2;
    theWorld1.kappa = 50000;
    theWorld1.SetParentWorld(&theWorld);

    thePlot.SetBoundaryPlotData(theWorld1);
    thePlot.SetPotentialPlotData(theWorld1);
    thePlot.SetZeroPlotData(theWorld1);


    set_properties();
    do_layout();

    // end wxGlade
}

void MainFrame::set_properties()
{
    // begin wxGlade: MainFrame::set_properties
    SetTitle(wxT("Main Window"));
    // end wxGlade
}

void MainFrame::do_layout()
{
    // begin wxGlade: MainFrame::do_layout
    wxStaticBoxSizer* sizer_1 = new wxStaticBoxSizer(sizer_1_staticbox, wxVERTICAL);
    sizer_1->Add(graphPanel, 1, wxEXPAND, 0);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    Layout();
    // end wxGlade
}

void MainFrame::OnPaint(wxPaintEvent &event)
{
	int w,h;
	w=0;h=0;

	graphPanel->GetClientSize(&w,&h);
	
	if(!w || !h)
		return;
	mglGraph gr(w,h);
        
        gr.SetSize(w,h);
        gr.InPlot(-0.1,1.1,-0.1,1.1);
	thePlot.DrawPlot(&gr);	
	
	wxDC *dc=0;
	dc=new wxClientDC(graphPanel);
	
	wxImage img(w,h,const_cast<unsigned char*>(gr.GetRGB()),true);

	dc->DrawBitmap(wxBitmap(img),0,0);
	delete dc;
}

class GraphTestApp: public wxApp {
public:
    bool OnInit();
    ROSListener rl;
};

IMPLEMENT_APP(GraphTestApp)

bool GraphTestApp::OnInit()
{
    wxInitAllImageHandlers();
    MainFrame* mainFrame = new MainFrame(NULL, wxID_ANY, wxEmptyString, wxPoint(50, 50), wxSize(450, 340));
    SetTopWindow(mainFrame);
    mainFrame->Show();
    
    rl.Start();
    return true;
}
