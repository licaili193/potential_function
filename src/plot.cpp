#include "plot.h"

//Apple are special....
#ifdef __APPLE__
	#include <math.h>
#endif

#include <iostream>

#ifndef ASSERT
	#define ASSERT(f)
#endif

using std::endl;
using std::cerr;
using std::string;

//Nasty string conversion functions.

void Plot::setPlotData(float *dX,float *dY, unsigned int num)
{
	//Do nothing first
}



void Plot::drawPlot(mglGraph *gr)
{
        mglData dat(30,40);	// data to for plotting
            for(long i=0;i<30;i++)   for(long j=0;j<40;j++)
                dat.a[i+30*j] = 1/(1+(i-15)*(i-15)/225.+(j-20)*(j-20)/400.);
	gr->Alpha(true);         // draws something using MathGL
  	gr->Light(true);
        gr->Rotate(50,60);	// rotate axis

        gr->Surf(dat);		// plot surface
        gr->Cont(dat,"y");	// plot yellow contour lines
        gr->Axis();			// draw axis

}

