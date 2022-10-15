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
    return sqrt(pow(this->x - p.x, 2) + pow(this->y - p.y, 2));
  }
};
