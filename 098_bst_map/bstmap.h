
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K key;
    V value;
    Node * left;
    Node * right;
    Node() : key(0), value(0), left(NULL), right(NULL) {}
    Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
  };
  Node * root;

 public:
  BstMap() : root(NULL) {}
  BstMap(const BstMap & rhs) { root = copy(rhs.root); }

  Node * copy(Node * target) {
    if (target == NULL) {
      return NULL;
    }
    Node * root = new Node(target->key, target->value);
    root->left = copy(target->left);
    root->right = copy(target->right);
    return root;
  }
  BstMap & operator=(const BstMap & rhs) {
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
  virtual ~BstMap<K, V>() { destructor(root); }
  virtual void add(const K & key, const V & value) {
    Node ** it = &root;
    while (*it != NULL) {
      if (key == (*it)->key) {
        (*it)->value = value;
        return;
      }
      else if (key < (*it)->key) {
        it = &((*it)->left);
      }
      else {
        it = &((*it)->right);
      }
    }
    *it = new Node(key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    Node ** target = lookupNode(key);
    Node * temp = *target;
    if (temp == NULL) {
      throw std::invalid_argument("Can't find key!");
    }
    return temp->value;
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
          (*target)->value = (*current)->value;
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
