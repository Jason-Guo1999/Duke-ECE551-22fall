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

  bool contains(const T & key) const {
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

  void remove(const T & key) { mybst.remove(key); }

  ~BstSet() { delete mybst; }
};
