#ifndef __OBSTACLE
#define __OBSTACLE

class Obstacle
{
public:
   Obstacle();
   Obstacle(double x, double y);

   double centerX, centerY;
   Obstacle *parentObs;

   void SetCenter(double x, double y);
   virtual double Beta(double x, double y) {return 0;}
   virtual double Rho(double x, double y) {return 0;}
};

#endif
