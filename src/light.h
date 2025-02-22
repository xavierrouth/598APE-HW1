#ifndef __LIGHT_H__
#define __LIGHT_H__
#include "vector.h"
#include "camera.h"
#include "Textures/texture.h"
#include "Textures/colortexture.h"
#include <vector>
#include <memory>

typedef struct {
   unsigned char r;
   unsigned char g;
   unsigned char b;
} color_t;

class Light{
  public:
   color_t color;
   color_t getColor(unsigned char a, unsigned char b, unsigned char c);
   Vector center;
   Light(const Vector & cente, color_t colo);
};

struct LightNode{
   Light* data;
   LightNode* prev, *next;
};

class Shape;

class Autonoma{
public:
   Camera camera;
   Texture* skybox;
   unsigned int depth;
   std::vector<std::unique_ptr<Shape>> shapes;
   LightNode *lightStart, *lightEnd;
   Autonoma(const Camera &c);
   Autonoma(const Camera &c, Texture* tex);
   void addShape(std::unique_ptr<Shape> s);
   void addLight(Light* s);
};

void getLight(double* toFill, const Autonoma* const aut, Vector point, Vector norm, unsigned char r);

#endif
