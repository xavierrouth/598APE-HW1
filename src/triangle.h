#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "plane.h"

class Triangle final : public Plane{
public:
   double thirdX;
   Triangle(Vector c, Vector b, Vector a, Texture* t);
   double getIntersection(Ray ray) final;
   bool getLightIntersection(Ray ray, double* fill) final;
};

#endif
