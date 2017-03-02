#ifndef __OBSTACLE
#define __OBsTACLE

class Obstacle
{
protected:
   double centerX, centerY;
public:
   Obstacle();
   Obstacle(double x, double y);

   void SetCenter(double x, double y);
   virtual double Beta(double x, double y); 
};

#endif
