#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression(long _number) : number(_number) {}
  std::string toString() const {
    std::stringstream s;
    s << number;
    return s.str();
  }
  long evaluate() const { return number; }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression(Expression * _lhs, Expression * _rhs) : lhs(_lhs), rhs(_rhs) {}
  std::string toString() const {
    std::stringstream s;
    s << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return s.str();
  }

  long evaluate() const { return lhs->evaluate() + rhs->evaluate(); }

  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
};

class MinusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  MinusExpression(Expression * _lhs, Expression * _rhs) : lhs(_lhs), rhs(_rhs) {}
  std::string toString() const {
    std::stringstream s;
    s << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return s.str();
  }
  long evaluate() const { return lhs->evaluate() - rhs->evaluate(); }

  virtual ~MinusExpression() {
    delete lhs;
    delete rhs;
  }
};

class TimesExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  TimesExpression(Expression * _lhs, Expression * _rhs) : lhs(_lhs), rhs(_rhs) {}
  std::string toString() const {
    std::stringstream s;
    s << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return s.str();
  }

  long evaluate() const { return lhs->evaluate() * rhs->evaluate(); }
  virtual ~TimesExpression() {
    delete lhs;
    delete rhs;
  }
};

class DivExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  DivExpression(Expression * _lhs, Expression * _rhs) : lhs(_lhs), rhs(_rhs) {}
  std::string toString() const {
    std::stringstream s;
    s << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return s.str();
  }
  long evaluate() const { return lhs->evaluate() / rhs->evaluate(); }
  virtual ~DivExpression() {
    delete lhs;
    delete rhs;
  }
};
