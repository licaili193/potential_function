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

#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <stdio.h>

using namespace std;
extern params Msg;

MainFrame::MainFrame(wxWindow* parent, int id, const wxString& title, const wxPoint& pos, const wxSize& size, long style):
    wxFrame(parent, id, title, pos, size, wxDEFAULT_FRAME_STYLE)
{
    // begin wxGlade: MainFrame::MainFrame
    sizer_1_staticbox = new wxStaticBox(this, -1, wxT("sizer_1"));
    graphPanel = new wxPanel(this, wxID_ANY);
    graphPanel->SetMinClientSize(wxSize(800,800));

    theWorlds.LoadSample();

    set_properties();
    do_layout();

    m_pTimer = new wxTimer(this,10);
    m_pTimer->Start(100); 

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

void MainFrame::OnExit(wxCommandEvent& event)
{
    delete m_pTimer;
    Close( true );
}

void MainFrame::OnTimerTimeout(wxTimerEvent& event)
{
    CmdPhraser(&Msg);
}

class GraphTestApp: public wxApp {
public:
    bool OnInit();
    int OnExit();
    ROSListener rl;
};

//PROCESS cmd
template<typename Out>
void split(const string &s, char delim, Out result) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        *(result++) = item;
    }
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, back_inserter(elems));
    return elems;
}

void MainFrame::CmdPhraser(params* pCmd)
{
    static int sCurrentWorld = 0;
    string cmd;
    pthread_mutex_lock(&pCmd->mutex);
    cmd = pCmd->cmd;
    pCmd->cmd = "";
    pthread_mutex_unlock(&pCmd->mutex);

    vector<string>args = split(cmd,' ');
    int length = args.size();
    if(length>0)
    {
        if(args[0]=="world")
        {
            cout<<"Draw world: ";
            if(length>1)
            {
                int num;
                sscanf(args[1].c_str(),"%d",&num);
                cout<<num<<endl;
                thePlot.SetBoundaryPlotData(*theWorlds.GetWorld(num));
                thePlot.SetPotentialPlotData(*theWorlds.GetWorld(num));
                thePlot.SetZeroPlotData(*theWorlds.GetWorld(num));
                sCurrentWorld = num;
                Refresh(); 
                Update();
            }
        }
        if(args[0]=="goal")
        {
            cout<<"Set goal: ";
            if(length>2)
            {
                double x,y;
                sscanf(args[1].c_str(),"%lf",&x);
                sscanf(args[2].c_str(),"%lf",&y);
                cout<<x<<" "<<y<<endl;
                theWorlds.SetGoal(x,y);
                thePlot.SetBoundaryPlotData(*theWorlds.GetWorld(sCurrentWorld));
                thePlot.SetPotentialPlotData(*theWorlds.GetWorld(sCurrentWorld));
                thePlot.SetZeroPlotData(*theWorlds.GetWorld(sCurrentWorld));
                Refresh(); 
                Update();
            }
        }
    }
}
//PROCESS end

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

int GraphTestApp::OnExit()
{
    cout<<"About to kill the listener thread."<<endl;
    rl.Kill();
    return 0;
}
