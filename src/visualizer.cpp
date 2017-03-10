#include "visualizer.h"
#include "world.h"

//Apple are special....
#ifdef __APPLE__
	  #include <math.h>
#endif

#include <iostream>
#include <mgl2/mgl.h>

#include <vector>

#ifndef ASSERT
	  #define ASSERT(f)
#endif

using namespace std;

//Nasty string conversion functions.
void mgls_prepare2d(mglData *a, mglData *b=0, mglData *v=0)
{
    register long i,j,n=50,m=40,i0;
    if(a) a->Create(n,m);   if(b) b->Create(n,m);
    if(v) { v->Create(9); v->Fill(-1,1);  }
    mreal x,y;
    for(i=0;i<n;i++)  for(j=0;j<m;j++)
    {
      x = i/(n-1.); y = j/(m-1.); i0 = i+n*j;
      if(a) a->a[i0] = 0.6*sin(2*M_PI*x)*sin(3*M_PI*y)+0.4*cos(3*M_PI*x*y);
      if(b) b->a[i0] = 0.6*cos(2*M_PI*x)*cos(3*M_PI*y)+0.4*cos(3*M_PI*x*y);
    }
}

Visualizer::Visualizer()
{
    _contourData.Create(41);
    for(int i=0;i<41;i++) _contourData.a[i] = 0.025*(double)i;
}

void Visualizer::SetBoundaryPlotData(World &w)
{
	  double steps, xs, xe, ys, ye;
    int nx = 0, ny = 0;
    w.GetFrame(xs, xe, ys, ye, steps);
    _xStart = xs; _xEnd = xe; _yStart = ys; _yEnd = ye;
    nx = (int)((xe-xs)/steps)+1;
    ny = (int)((ye-ys)/steps)+1;

    _mainData.Create(nx, ny);
    _backgroundData.Create(nx, ny);

    int nObs = w.obsArray.size();
    for(int i=0;i<nx;i++)  for(int j=0;j<ny;j++)
    {
        double x, y;
        x = xs + steps*i; 
        y = ys + steps*j;
        int i0 = i*nx+j;
        _backgroundData.a[i0] = w.mainObs->Beta(x,y)<=0?0:1;
        for(int k=0;k<nObs;k++) _backgroundData.a[i0] = w.obsArray[k]->Beta(x,y)<=0?1:0;
    }
}

void Visualizer::DrawPlot(mglGraph *gr)
{
    gr->AddRange('x',_xStart,_xEnd);
    gr->AddRange('y',_yStart,_yEnd);
    gr->SetTicks('x',1,5,0);
    gr->SetTicks('y',1,5,0);
    gr->SetOriginTick(true);
    gr->Box("W");
    gr->Axis();
    gr->Dens(_backgroundData);
    //gr->Cont(a,"2H");
}
