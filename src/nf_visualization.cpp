#include "ros/ros.h"
#include "std_msgs/String.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/timer.h>
#include <mgl2/mgl.h>

#include "nf_visualization.h"

#include <iostream>

void ROSTimer::Notify()
{
    ros::spinOnce();
    ROS_INFO("ROS Spined.");
}
 
void ROSTimer::start()
{
    wxTimer::Start(1000);
}

MainFrame::MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: MainFrame::MainFrame
    sizer_1_staticbox = new wxStaticBox(this, -1, wxT("sizer_1"));
    graphPanel = new wxPanel(this, wxID_ANY);

    set_properties();
    do_layout();

    timer = new ROSTimer();
    timer->start();
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

	mglGraph gr;
        std::cout<<"Width: "<<w<<" Height: "<<h<<std::endl;

	thePlot.drawPlot(&gr);	
	
	wxDC *dc=0;
	dc=new wxClientDC(graphPanel);


	
	wxImage img(600,400,const_cast<unsigned char*>(gr.GetRGB()),true);

	dc->DrawBitmap(wxBitmap(img),0,0);
	delete dc;
}


class GraphTestApp: public wxApp {
public:
    bool OnInit();
};

IMPLEMENT_APP(GraphTestApp)

bool GraphTestApp::OnInit()
{
    wxInitAllImageHandlers();
    MainFrame* mainFrame = new MainFrame(NULL, wxID_ANY, wxEmptyString, wxPoint(50, 50), wxSize(450, 340));
    SetTopWindow(mainFrame);
    mainFrame->Show();

    ros::init(argc, argv, "nf_visualization");
    ros::NodeHandle n;
    ROS_INFO("This node will create a window for visualization.");

    return true;
}




