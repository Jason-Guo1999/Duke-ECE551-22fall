#include <cmath>

#include "point.hpp"
#define PI 3.1415926536
class Circle {
 private:
  Point center;
  double radius;

 public:
  Circle(Point _center, double _radius) : center(_center), radius(_radius) {}

  void move(double dx, double dy) { this->center.move(dx, dy); }

  double intersectionArea(const Circle & otherCircle) {
    double dis = this->center.distanceFrom(otherCircle.center);
    if (dis >= this->radius + otherCircle.radius) {
      return 0.0;
    }
    else if (dis >= 0 && dis <= std::abs(this->radius - otherCircle.radius)) {
      if (this->radius > otherCircle.radius) {
        return PI * pow(this->radius, 2);
      }
      else {
        return PI * pow(otherCircle.radius, 2);
      }
    }
    else {
      double a1 = 2 * acos((dis * dis + this->radius * this->radius -
                            otherCircle.radius * otherCircle.radius) /
                           (2 * dis * this->radius));
      double a2 = 2 * acos((dis * dis + otherCircle.radius * otherCircle.radius -
                            this->radius * this->radius) /
                           (2 * dis * otherCircle.radius));
      double s1 = 1 / 2 * this->radius * this->radius * sin(a1) +
                  1 / 2 * otherCircle.radius * otherCircle.radius * sin(a2);
      double s2 = a1 / 2 * this->radius * this->radius +
                  a2 / 2 * otherCircle.radius * otherCircle.radius;
      return s2 - s1;
    }
  }
};
