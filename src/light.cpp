
#include "light.h"
#include "shape.h"
#include "camera.h"
#include <vector>

Light::Light(const Vector & cente, color_t colo) : center(cente){
   color = colo;
}

color_t Light::getColor(unsigned char a, unsigned char b, unsigned char c){
   color_t color {a, b, c};
   return color;
}

Autonoma::Autonoma(const Camera& c): camera(c){
   lightStart = NULL;
   lightEnd = NULL;
   depth = 10;
   skybox = BLACK;
}

Autonoma::Autonoma(const Camera& c, Texture* tex): camera(c){
   lightStart = NULL;
   lightEnd = NULL;
   depth = 10;
   skybox = tex;
}

void Autonoma::addShape(std::unique_ptr<Shape> r){
   shapes.push_back(std::move(r));
}

void Autonoma::addLight(Light* r){
   LightNode* hi = (LightNode*)malloc(sizeof(LightNode));
   hi->data = r;
   hi->next = hi->prev = NULL;
   if(lightStart==NULL){
      lightStart = lightEnd = hi;
   }
   else{
      lightEnd->next = hi;
      hi->prev = lightEnd;
      lightEnd = hi;
   }
}


void getLight(double* tColor, const Autonoma* const aut, Vector point, Vector norm, unsigned char flip){
   tColor[0] = tColor[1] = tColor[2] = 0.;
   LightNode *t = aut->lightStart;
   while(t!=NULL){
      double lightColor[3];     
      lightColor[0] = t->data->color.r/255.;
      lightColor[1] = t->data->color.g/255.;
      lightColor[2] = t->data->color.b/255.;
      Vector ra = t->data->center-point;
      bool hit = false;
      for (auto & shape : aut->shapes) {
         hit = shape->getLightIntersection(Ray(point+ra*.01, ra), lightColor);
         if (hit) {
            break;
         }
      }

      double perc = (norm.dot(ra)/(ra.mag()*norm.mag()));
      if(!hit){
      if(flip && perc<0) perc=-perc;
        if(perc>0){
      
         tColor[0]+= perc*(lightColor[0]);
         tColor[1]+= perc*(lightColor[0]);
         tColor[2]+= perc*(lightColor[0]);
         if(tColor[0]>1.) tColor[0] = 1.;
         if(tColor[1]>1.) tColor[1] = 1.;
         if(tColor[2]>1.) tColor[2] = 1.;
        }
      }
      t =t->next;
   }
}
