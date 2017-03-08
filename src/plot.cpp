#include "plot.h"

//Apple are special....
#ifdef __APPLE__
	#include <math.h>
#endif

#include <iostream>
#include <mgl2/mgl.h>

#ifndef ASSERT
	#define ASSERT(f)
#endif

using std::endl;
using std::cerr;
using std::string;

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

void Plot::setPlotData(float *dX,float *dY, unsigned int num)
{
	//Do nothing first
}

void Plot::drawPlot(mglGraph *gr)
{
    mglData a,v(5); mgls_prepare2d(&a); v.a[0]=-0.5;  v.a[1]=-0.15; v.a[2]=0; v.a[3]=0.15;  v.a[4]=0.5;
    gr->AddRange('x',-4,4);
    gr->AddRange('y',-4,4);
    gr->SetTicks('x',1,5,0);
    gr->SetTicks('y',1,5,0);
    gr->SetOriginTick(true);
    gr->Box("W");
    gr->Axis();
    gr->Cont(a,"2H");
}

