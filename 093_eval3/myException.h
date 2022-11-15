#ifndef _MYEXCEPTIONH_
#define _MYEXCEPTIONH_

#include <exception>
class myException : public std::exception {
 public:
  const char * msg;
  myException(const char * m) : msg(m) {}
  virtual const char * what() const throw() { return msg; }
};

#endif
