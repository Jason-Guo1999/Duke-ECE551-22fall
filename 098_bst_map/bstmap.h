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

  Node * copy(Node * target) {
    if (target == NULL) {
      return NULL;
    }
    Node * root = new Node(target->key, target->value);
    root->left = copy(target->left);
    root->right = copy(target->right);
    return root;
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
    if (temp->left == NULL && temp->right != NULL) {
      *target = temp->right;
      delete temp;
    }
    else if (temp->right == NULL && temp->left != NULL) {
      *target = temp->left;
      delete temp;
    }
    else {
      Node ** predecessor = &((*target)->left);
      while ((*predecessor)->right != NULL) {
        predecessor = &((*predecessor)->right);
      }
      /*
      const V predValue = (*predecessor)->value;
      const K predKey = (*predecessor)->key;
      temp->key = predKey;
      temp->value = predValue;
      Node * deleteNode = *predecessor;
      *predecessor = deleteNode->left;
      delete deleteNode;
      */
      (*target)->key = (*predecessor)->key;
      const V value = (*predecessor)->value;
      Node * t = (*predecessor)->left;
      delete *predecessor;
      *predecessor = t;
      add((*target)->key, value);
    }
    return;
  }
};
