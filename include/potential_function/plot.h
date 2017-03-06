#ifndef PLOT_H
#define PLOT_H

#include <cmath>
#include <string>
#include <limits>
#include <sstream>
#include <iostream>
#include <fstream>

#include <mgl2/mgl.h>

//#include "misc.h"

class Plot
{
public:
	virtual void drawPlot(mglGraph *graph);
	void setPlotData(float *dX,float *dY, unsigned int num);
};

#endif
