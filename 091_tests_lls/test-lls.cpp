#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);

    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    il.addFront(0);
    assert(il.head == il.tail && il.getSize() == 1);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    il.addFront(1);
    assert(il.head->data == 1);
    assert(il.tail->data == 0);
    assert(il.head->next == il.tail && il.tail->prev->data == 1);
    assert(il.getSize() == 2);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    il.addBack(1);
    assert(il.head == il.tail && il.getSize() == 1);
    assert(il.tail->next == NULL);
    assert(il.head->prev == NULL);
    il.addBack(2);
    assert(il.head->data == 1);
    assert(il.tail->data == 2);
    assert(il.tail->next == NULL);
    assert(il.getSize() == 2);
  }

  void testRemove() {
    IntList il;
    assert(il.remove(10) == false);
    il.addFront(1);
    bool ans1 = il.remove(1);
    assert(ans1 == true && il.head == il.tail && il.getSize() == 0 && il.head == NULL);
    il.addFront(2);
    il.addFront(3);
    il.addFront(5);
    bool ans2 = il.remove(4);
    assert(ans2 == false);
    assert(il.head->data == 5);
    assert(il.head->next->data == 3);
    assert(il.tail->prev->data == 3);
    assert(il.tail->data == 2);
    assert(il.getSize() == 3);
    il.addBack(2);
    bool ans3 = il.remove(5);
    assert(ans3 == true);
    assert(il.head->data == 3 && il.head->next->data == 2 && il.head->prev == NULL);
    assert(il.tail->data == 2 && il.tail->prev->data == 2 && il.tail->next == NULL);
    il.addBack(1);
    il.remove(1);
    assert(il.head->data == 3 && il.head->next->data == 2 && il.head->prev == NULL);
    assert(il.tail->data == 2 && il.tail->prev->data == 2 && il.tail->next == NULL);
    il.remove(2);
    assert(il.head->data == 3 && il.tail->data == 2 && il.head->prev == NULL);
    assert(il.tail->data == 2 && il.tail->prev->data == 3 && il.tail->next == NULL);
    il.remove(3);
    il.remove(2);
    assert(il.head == il.tail && il.head == NULL);
  }

  void testRuleofThree() {
    IntList il;
    il.addBack(1);
    il.addBack(2);
    IntList il2(il);
    assert(il2.head->data == 1);
    assert(il2.getSize() == 2);
    assert(il2.head->next->data == 2);
    IntList il3 = il2;
    assert(il3.tail->data == 2);
    assert(il3.tail->next == NULL);
    assert(il3.getSize() == 2);
    il2.addFront(1);
    il = il2;
    assert(il.head->data == 1 && il.getSize() == 3);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  t.testRemove();
  t.testRuleofThree();

  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
