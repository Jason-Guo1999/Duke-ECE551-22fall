// define the structure for reading template //
#include <stdlib.h>
struct _file {
  // store each line //
  char ** lines;
  // line number //
  size_t nums;
};

typedef struct _file file;
