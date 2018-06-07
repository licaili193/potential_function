#include "visualizer.h"
#include "world.h"

// Apple are special....
#ifdef __APPLE__
#include <math.h>
#endif

#include <mgl2/mgl.h>
#include <iostream>

#include <vector>

#ifndef ASSERT
#define ASSERT(f)
#endif

using namespace std;

Visualizer::Visualizer() {
  _contourData.Create(41);
  for (int i = 0; i < 41; i++) _contourData.a[i] = 0.025 * (double)i;
}

void Visualizer::SetBoundaryPlotData(World &w) {
  double steps, xs, xe, ys, ye;
  int nx = 0, ny = 0;
  w.GetFrame(xs, xe, ys, ye, steps);
  _xStart = xs;
  _xEnd = xe;
  _yStart = ys;
  _yEnd = ye;
  nx = (int)((xe - xs) / steps) + 1;
  ny = (int)((ye - ys) / steps) + 1;

  _backgroundData.Create(nx, ny);

  int nObs = w.obsArray.size();
  for (int i = 0; i < nx; i++)
    for (int j = 0; j < ny; j++) {
      double x, y;
      x = xs + steps * i;
      y = ys + steps * j;
      int i0 = i + j * ny;
      _backgroundData.a[i0] = w.mainObs->Beta(x, y) <= 0 ? 1 : 0;
      for (int k = 0; k < nObs; k++)
        _backgroundData.a[i0] =
            w.obsArray[k]->Beta(x, y) <= 0 ? 0 : _backgroundData.a[i0];
    }
}

void Visualizer::SetPotentialPlotData(World &w) {
  double steps, xs, xe, ys, ye;
  int nx = 0, ny = 0;
  w.GetFrame(xs, xe, ys, ye, steps);
  _xStart = xs;
  _xEnd = xe;
  _yStart = ys;
  _yEnd = ye;
  nx = (int)((xe - xs) / steps) + 1;
  ny = (int)((ye - ys) / steps) + 1;

  _mainData.Create(nx, ny);

  for (int i = 0; i < nx; i++)
    for (int j = 0; j < ny; j++) {
      double x, y;
      x = xs + steps * i;
      y = ys + steps * j;
      int i0 = i + j * ny;
      double temp = w.PotentialValue(x, y, w.kappa);
      _mainData.a[i0] = temp < 0 ? NAN : temp;
    }
}

void Visualizer::SetZeroPlotData(World &w) {
  _zeroX.Create(30);
  _zeroY.Create(30);
  for (int i = 0; i < 30; i++) {
    _zeroX.a[i] = w.destX + w.rBubble * cos(i * 12.0 / 180.0 * M_PI);
    _zeroY.a[i] = w.destY + w.rBubble * sin(i * 12.0 / 180.0 * M_PI);
  }
}

void Visualizer::DrawPlot(mglGraph *gr) {
  gr->AddRange('x', _xStart, _xEnd);
  gr->AddRange('y', _yStart, _yEnd);
  gr->SetTicks('x', 1, 5, 0);
  gr->SetTicks('y', 1, 5, 0);
  gr->SetOriginTick(true);
  gr->Box("W");
  gr->Axis();
  gr->Cont(_contourData, _mainData, "k");
  gr->Plot(_zeroX, _zeroY, "2");
  gr->Dens(_backgroundData, "kw");
}
