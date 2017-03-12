#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <cmath>
#include <string>
#include <limits>
#include <sstream>
#include <iostream>
#include <fstream>

#include <mgl2/mgl.h>

#include "world.h"

//#include "misc.h"

class Visualizer
{
	mglData _contourData,_mainData,_backgroundData,_zeroX,_zeroY;
	double _xStart, _xEnd, _yStart, _yEnd;
public:
	Visualizer();

	virtual void DrawPlot(mglGraph *graph);
	void SetBoundaryPlotData(World &w);
	void SetPotentialPlotData(World &w);
	void SetZeroPlotData(World &w);
};

#endif
