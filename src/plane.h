#ifndef __PLANE_H__
#define __PLANE_H__

#include "shape.h"

class Plane : public Shape{
public:
  Vector vect, right, up;
  double d;
  Plane(const Vector &c, Texture* t, double ya, double pi, double ro, double tx, double ty);
  double getIntersection(Ray ray);
  bool getLightIntersection(Ray ray, double* toFill);
  void move() final;
  void getColor(unsigned char* __restrict__ toFill, double* __restrict__ am, double* __restrict__ op, double* __restrict__ ref, Autonoma* __restrict__ r, Ray ray, unsigned int depth) final;
  Vector getNormal(Vector point) final;
  unsigned char reversible() final;
  void setAngles(double yaw, double pitch, double roll) final;
  void setYaw(double d) final;
  void setPitch(double d) final;
  void setRoll(double d) final;
};

#endif
