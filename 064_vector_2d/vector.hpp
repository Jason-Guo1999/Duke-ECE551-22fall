/* write your class interface in this file
   write function definitions only if they are very short
 */
#include <cmath>
#include <cstdio>
using namespace std;
class Vector2D {
 private:
  double x;
  double y;

 public:
  void initVector(double x, double y) {
    this->x = x;
    this->y = y;
  }

  double getMagnitude() const { return sqrt(this->x * this->x + this->y * this->y); }

  Vector2D operator+(const Vector2D & rhs) const {
    Vector2D * newVector = new Vector2D();
    newVector->x = this->x + rhs.x;
    newVector->y = this->y + rhs.y;
    return *newVector;
  }

  Vector2D & operator+=(const Vector2D & rhs) {
    this->x = this->x + rhs.x;
    this->y = this->y + rhs.y;
    return *this;
  }

  double dot(const Vector2D & rhs) { return this->x * rhs.x + this->y * rhs.y; }

  void print() const { std::printf("<%.2f, %.2f>", this->x, this->y); }
};
