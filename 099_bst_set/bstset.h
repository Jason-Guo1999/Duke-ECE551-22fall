
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename K>
class BstSet : public Set<K> {
 public:
  class Node {
   public:
    K key;
    Node * left;
    Node * right;
    Node() : key(0), left(NULL), right(NULL) {}
    Node(const K & k) : key(k), left(NULL), right(NULL) {}
  };
  Node * root;

  BstSet() : root(NULL) {}
  BstSet(const BstSet & rhs) { root = copy(rhs.root); }

  Node * copy(Node * target) {
    if (target == NULL) {
      return NULL;
    }
    Node * root = new Node(target->key);
    root->left = copy(target->left);
    root->right = copy(target->right);
    return root;
  }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      destructor(root);
      root = copy(rhs.root);
    }
    return *this;
  }
  void destructor(Node * root) {
    if (root != NULL) {
      destructor(root->left);
      destructor(root->right);
      delete root;
    }
  }
  virtual ~BstSet<K>() { destructor(root); }
  virtual void add(const K & key) {
    Node ** it = &root;
    while (*it != NULL) {
      if (key == (*it)->key) {
        return;
      }
      else if (key < (*it)->key) {
        it = &((*it)->left);
      }
      else {
        it = &((*it)->right);
      }
    }
    *it = new Node(key);
  }

  virtual bool contains(const K & key) const {
    Node ** target = lookupNode(key);
    Node * temp = *target;
    try {
      if (temp == NULL) {
        throw std::invalid_argument("Can't find key!");
      }
    }
    catch (std::invalid_argument & re) {
      return false;
    }
    return true;
  }

  Node ** lookupNode(const K & key) const {
    Node ** it = const_cast<Node **>(&root);
    while ((*it) != NULL) {
      if ((*it)->key == key) {
        break;
      }
      else if ((*it)->key > key) {
        it = &((*it)->left);
      }
      else {
        it = &((*it)->right);
      }
    }
    return it;
  }

  virtual void remove(const K & key) {
    Node ** current = &root;
    Node * temp = NULL;
    while (*current != NULL) {
      if ((*current)->key == key) {
        if ((*current)->left == NULL) {
          temp = (*current)->right;
          delete *current;
          *current = temp;
        }
        else if ((*current)->right == NULL) {
          temp = (*current)->left;
          delete *current;
          *current = temp;
        }
        else {
          Node ** target = current;
          current = &((*current)->left);
          while ((*current)->right != NULL) {
            current = &((*current)->right);
          }
          (*target)->key = (*current)->key;
          temp = (*current)->left;
          delete *current;
          *current = temp;
        }
      }
      else if (key < (*current)->key) {
        current = &(*current)->left;
      }
      else {
        current = &(*current)->right;
      }
    }
  }
};
