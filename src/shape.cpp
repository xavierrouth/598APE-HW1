#include "shape.h"
#include <vector>
#include <algorithm>
Shape::Shape(const Vector &c, Texture* t, double ya, double pi, double ro): center(c), texture(t), yaw(ya), pitch(pi), roll(ro){
};

void Shape::setAngles(double a, double b, double c){
   yaw =a; pitch = b; roll = c;
   xcos = cos(yaw);
   xsin = sin(yaw);
   ycos = cos(pitch);
   ysin = sin(pitch);
   zcos = cos(roll);
   zsin = sin(roll);
}

void Shape::setYaw(double a){
   yaw =a;
   xcos = cos(yaw);
   xsin = sin(yaw);
}

void Shape::setPitch(double b){
   pitch = b;
   ycos = cos(pitch);
   ysin = sin(pitch);
}

void Shape::setRoll(double c){
   roll = c;
   zcos = cos(roll);
   zsin = sin(roll);
}

typedef struct {
   double time;
   Shape* shape;
} TimeAndShape;

void insertionSort(TimeAndShape *arr, int n) {
    for (int i = 1; i < n; ++i) {
        TimeAndShape key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].time > key.time) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

struct less_than_key
{
    inline bool operator() (const TimeAndShape& struct1, const TimeAndShape& struct2)
    {
        return (struct1.time < struct2.time);
    }
};

void calcColor(unsigned char* __restrict__ toFill,const Autonoma* const __restrict__  c, Ray ray, unsigned int depth){
   
   double curTime = inf;
   Shape* curShape = nullptr;

   for (auto & shape : c->shapes) {
      double time = shape->getIntersection(ray);
      TimeAndShape a = {time, shape.get()};
      if (time < curTime) {
         curShape = shape.get();
         curTime = time;
      }
      
   }

   if (curShape == nullptr || curTime == inf) {
      double opacity, reflection, ambient;
      Vector temp = ray.vector.normalize();
      const double x = temp.x;
      const double z = temp.z;
      const double me = (temp.y<0)?-temp.y:temp.y;
      const double angle = atan2(z, x);
      c->skybox->getColor(toFill, &ambient, &opacity, &reflection, fix(angle/M_TWO_PI),fix(me));
      return;
   }

   Vector intersect = curTime*ray.vector+ray.point;
   double opacity, reflection, ambient;
   curShape->getColor(toFill, &ambient, &opacity, &reflection, c, Ray(intersect, ray.vector), depth);
   
   double lightData[3];
   Vector normal = curShape->getNormal(intersect);
   unsigned char reversible = curShape->reversible();
   getLight(lightData, c, intersect, normal, reversible);
   toFill[0] = (unsigned char)(toFill[0]*(ambient+lightData[0]*(1-ambient)));
   toFill[1] = (unsigned char)(toFill[1]*(ambient+lightData[1]*(1-ambient)));
   toFill[2] = (unsigned char)(toFill[2]*(ambient+lightData[2]*(1-ambient)));
   if(depth<c->depth && (opacity<1-1e-6 || reflection>1e-6)){
      unsigned char col[4];
      if(opacity<1-1e-6){
         Ray nextRay = Ray(intersect+ray.vector*1E-4, ray.vector);
         calcColor(col, c, nextRay, depth+1);
         toFill[0]= (unsigned char)(toFill[0]*opacity+col[0]*(1-opacity));
         toFill[1]= (unsigned char)(toFill[1]*opacity+col[1]*(1-opacity));
         toFill[2]= (unsigned char)(toFill[2]*opacity+col[2]*(1-opacity));        
      }
      if(reflection>1e-6){
         Vector norm = curShape->getNormal(intersect).normalize();
         Vector vec = ray.vector-2*norm*(norm.dot(ray.vector));
         Ray nextRay = Ray(intersect+vec*1E-4, vec);
         calcColor(col, c, nextRay, depth+1);
      
         toFill[0]= (unsigned char)(toFill[0]*(1-reflection)+col[0]*(reflection));
         toFill[1]= (unsigned char)(toFill[1]*(1-reflection)+col[1]*(reflection));
         toFill[2]= (unsigned char)(toFill[2]*(1-reflection)+col[2]*(reflection));
      }
   }
}
