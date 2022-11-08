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
  BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }

  Node * copy(Node * current) {
    if (current == NULL) {
      return NULL;
    }
    Node * newRoot = new Node(current->key, current->value);
    newRoot->left = copy(current->left);
    newRoot->right = copy(current->right);
    return newRoot;
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
    Node ** it = lookupNode(key);
    Node * temp = *it;
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
    if (root == NULL) {
      return;
    }
    Node ** target = lookupNode(key);
    Node * temp = *target;
    if (temp == NULL) {
      return;
    }
    if (temp->left == NULL) {
      *target = temp->right;
    }
    else {
      Node ** predecessor = &(temp->left);
      while ((*predecessor)->right != NULL) {
        predecessor = &((*predecessor)->right);
      }
      *target = *predecessor;
      *predecessor = (*predecessor)->left;
      (*target)->left = temp->left;
      (*target)->right = temp->right;
    }

    delete temp;
  }
};
