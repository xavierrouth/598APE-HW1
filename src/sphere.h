#ifndef __SPHERE_H__
#define __SPHERE_H__
#include "shape.h"

class Sphere : public Shape{
public:
  double radius;
  Sphere(const Vector &c, Texture* t, double ya, double pi, double ro, double radius);
  double getIntersection(Ray ray) final;
  void move() final;
  bool getLightIntersection(Ray ray, double* fill) final;
  void getColor(unsigned char* __restrict__ toFill, double* __restrict__ am, double* __restrict__ op, double* __restrict__ ref, const Autonoma* const __restrict__ r, Ray ray, unsigned int depth) final;
  Vector getNormal(Vector point) final;
  unsigned char reversible() final;
  void setAngles(double a, double b, double c) final;
  void setYaw(double a) final;
  void setPitch(double b) final;
  void setRoll(double c) final;
};
#endif
