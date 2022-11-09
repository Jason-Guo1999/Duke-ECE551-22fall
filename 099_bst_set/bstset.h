#include <stdexcept>

#include "bstmap.h"
#include "map.h"
#include "set.h"

template<typename T>
class BstSet : public Set<T> {
 private:
  BstMap<T, int> mybst;

 public:
  virtual void add(const T & key) { mybst.add(key, 0); }

  virtual bool contains(const T & key) {
    bool ans;
    try {
      ans = mybst.lookup(key);
    }
    catch (std::invalid_argument & re) {
      std::cerr << re.what() << std::endl;
      exit(EXIT_FAILURE);
    }
    return ans;
  }

  virtual void remove(const T & key) { mybst.remove(key); }

  virtual ~BstSet() {}
};
