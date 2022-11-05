#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

//YOUR CODE GOES HERE
class myException : public std::exception {
 private:
  const char * message;

 public:
  myException(const char * m) : message(m) {}
  virtual const char * what() const throw() { return message; }
};

template<typename T>

class dll {
 private:
  class Node {
   private:
    T val;
    Node * next;
    Node * prev;

   public:
    Node() : val(0), prev(NULL), next(NULL) {}
    Node(T & item) : val(item), next(NULL), prev(NULL) {}
    Node(T & item, Node * n1, Node * n2) : val(item), next(n1), prev(n2) {}
  };
  Node * head;
  Node * tail;
  int len;

 public:
  dll() {
    head = NULL;
    tail = NULL;
    len = 0;
  }

  dll(dll & rhs) {
    head = NULL;
    tail = NULL;
    len = 0;
    Node * it = rhs.head;
    while (it != NULL) {
      this->addBack(it->val);
      it = it->next;
    }
  }

  dll & operator=(dll & rhs) {
    while (head != NULL) {
      Node * temp = head;
      head = head->next;
      delete temp;
    }
    len = 0;
    Node * it = rhs.head;
    while (it != NULL) {
      this->addBack(it->val);
      it = it->next;
    }
    return *this;
  }

  void addFront(const T & item) {
    if (this->len == 0) {
      head = new Node(item);
      tail = head;
      len = 1;
    }
    else {
      Node * temp = new Node(item);
      temp->next = head;
      head->prev = temp;
      head = temp;
      len++;
    }
  }

  void addBack(const T & item) {
    if (this->len == 0) {
      head = new Node(item);
      tail = head;
      len = 1;
    }
    else {
      Node * temp = new Node(item, NULL, tail);
      tail->next = temp;
      tail = temp;
      len++;
    }
  }

  bool remove(const T & item) {
    if (head == NULL) {
      return false;
    }
    Node * it = head;
    // special case: delete head
    if (head->val == item) {
      if (len == 1) {
        len--;
        delete head;
      }
      else {
        Node * temp = head;
        head = head->next;
        head->prev = NULL;
        delete temp;
        len--;
      }
      return true;
    }
    while (it != NULL) {
      if (it->val != item) {
        it = it->next;
      }
      else {
        // special case: delete tail
        if (it == tail) {
          Node * temp = tail;
          tail = tail->prev;
          tail->next = NULL;
          delete temp;
          len--;
        }
        else {
          Node * temp1 = it->prev;
          Node * temp2 = it->next;
          temp1->next = temp2;
          temp2->prev = temp1;
          delete it;
          len--;
        }
        return true;
      }
    }
    return false;
  }

  T & operator[](int index) {
    if (index < 0 || index >= len) {
      throw myException("Invalid index");
    }
    Node * ans = head;
    for (int i = 0; i < index; i++) {
      ans = ans->next;
    }
    return ans->val;
  }

  const T & operator[](int index) const {
    if (index < 0 || index >= len) {
      throw myException("Invalid index");
    }
    Node * ans = head;
    for (int i = 0; i < index; i++) {
      ans = ans->next;
    }
    return ans->val;
  }
  int find(const T & item) {
    Node * it = head;
    for (int i = 0; i < len; i++) {
      if (it->val == item) {
        return i;
      }
      it = it->next;
    }
    return -1;
  }
  int getSize() { return this->len; }
  ~dll() {
    while (head != NULL) {
      Node * temp = head;
      head = head->next;
      delete temp;
    }
    len = 0;
    tail = NULL;
  }
};

#endif
