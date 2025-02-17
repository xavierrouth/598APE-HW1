#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "shape.h"

class Sphere : public Shape{
public:
  double radius;
  Sphere(const Vector &c, Texture* t, double ya, double pi, double ro, double radius);
  double getIntersection(Ray ray);
  void move();
  bool getLightIntersection(Ray ray, double* fill);
  void getColor(unsigned char* __restrict__ toFill, double* __restrict__ am, double* __restrict__ op, double* __restrict__ ref, Autonoma* __restrict__ r, Ray ray, unsigned int depth);
  Vector getNormal(Vector point);
  unsigned char reversible();
  void setAngles(double a, double b, double c);
  void setYaw(double a);
  void setPitch(double b);
  void setRoll(double c);
};
#endif
