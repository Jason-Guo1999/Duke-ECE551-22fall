#include <cmath>

#include "point.hpp"
#define PI 3.1415926535
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
      double a1 = 2.0 * acos((dis * dis + this->radius * this->radius -
                              otherCircle.radius * otherCircle.radius) /
                             (2.0 * dis * this->radius));
      double a2 = 2.0 * acos((dis * dis + otherCircle.radius * otherCircle.radius -
                              this->radius * this->radius) /
                             (2.0 * dis * otherCircle.radius));
      double s1 = a1 * pow(this->radius, 2) / 2 - sin(a1) * pow(this->radius, 2) / 2;
      double s2 =
          a2 * pow(otherCircle.radius, 2) / 2 - sin(a2) * pow(otherCircle.radius, 2) / 2;
      return s1 + s2;
    }
  }
};
