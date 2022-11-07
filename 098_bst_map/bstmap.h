

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
    Node(K & t1, V & t2) : key(t1), value(t2), left(nullptr), right(nullptr) {}
  };

  Node * root;

 public:
  BstMap() : root(nullptr) {}
  virtual void add(const K & key, const V & value) {
    if (this->root == nullptr) {
      this->root = new Node(key, value);
      return;
    }
    Node ** it = &root;
    while (*it != nullptr) {
      if ((*it)->key == key) {
        (*it)->value = value;
        return;
      }
      else if ((*it)->key > key) {
        it = &((*it)->left);
      }
      else {
        it = &((*it)->right);
      }
    }
    *it = new Node(key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    if (root == nullptr) {
      throw std::invalid_argument("Can't find key!");
    }
    Node ** it = &root;
    while (*it != nullptr) {
      if ((*it)->key == key) {
        return (*it)->value;
      }
      else if ((*it)->key > key) {
        it = &((*it)->left);
      }
      else {
        it = &((*it)->right);
      }
    }
    throw std::invalid_argument("Can't find key!");
  }

  virtual void remove(const K & key) {
    if (root == nullptr) {
      return;
    }
    Node ** it = &root;
    while (*it != nullptr) {
      if ((*it)->key == key) {
        Node * target = *it;
        if (target->left == nullptr && target->right == nullptr) {
          delete target;
          return;
        }
        else if (target->left == nullptr && target->right != nullptr) {
          Node * temp = target->right;
          delete target;
          *it = temp;
        }
        else if (target->left != nullptr && target->right == nullptr) {
          Node * temp = target->left;
          delete target;
          *it = temp;
        }
        else {
          Node * predecessor = *it->left;
          while (predecessor != nullptr) {
            predecessor = predecessor->right;
          }
          Node * temp = target->right;
          delete target;
          predecessor->right = temp;
        }
      }
      else if ((*it)->key > key) {
        it = &((*it)->left);
      }
      else {
        it = &((*it)->right);
      }
    }
  }

  virtual ~BstMap<K, V>() { deconstructor(root); }

  void deconstructor(Node * root) {
    if (root != nullptr) {
      deconstructor(root->left);
      deconstructor(root->right);
    }
    delete root;
  }
};
