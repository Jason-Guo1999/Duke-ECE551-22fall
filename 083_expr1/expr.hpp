#include <cstdlib>
#include <sstream>
#include <string>
class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long _number) : number(_number) {}
  virtual std::string toString() const {
    std::stringstream s;
    s << number;
    return s.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * _lhs, Expression * _rhs) : lhs(_lhs), rhs(_rhs) {}
  virtual std::string toString() const {
    std::string string1 = lhs->toString();
    std::string string2 = rhs->toString();
    return "(" + string1 + " + " + string2 + ")";
  }
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};
