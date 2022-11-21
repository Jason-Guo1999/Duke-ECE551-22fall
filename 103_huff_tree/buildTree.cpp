#include "node.h"

Node * buildTree(uint64_t * counts) {
  //WRITE ME!
  priority_queue_t pqt;
  for (size_t i = 0; i < 257; i++) {
    if (counts[i] == 0) {
      continue;
    }
    pqt.push(new Node(i, counts[i]));
  }

  while (pqt.size() >= 2) {
    Node * temp1 = pqt.top();
    pqt.pop();
    Node * temp2 = pqt.top();
    pqt.pop();
    Node * newNode = new Node(temp1, temp2);
    pqt.push(newNode);
  }

  return pqt.top();
}
