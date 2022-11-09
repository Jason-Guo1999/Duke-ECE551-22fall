#include <stdexcept>

#include "bstmap.h"
#include "map.h"
#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  BstMap<T, int> mybst;

 public:
  void add(const T & key) { mybst.add(key, 0); }

  bool contains(const T & key) { return mybst.lookup(key); }

  void remove(const T & key) { mybst.remove(key); }

  ~BstSet() {}
};
