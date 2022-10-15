#include <cmath>
class Point {
 private:
  double x;
  double y;

 public:
  void move(double dx, double dy) {
    this->x += dx;
    this->y += dy;
  }
  double distanceFrom(const Point & p) {
    return sqrt((this->x - p.x) * (this->x - p.x) + (this->y - p.y) * (this->y - p.y));
  }
};
