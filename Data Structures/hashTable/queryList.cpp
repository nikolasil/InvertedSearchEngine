#include "queryList.h"
#include <cstring>
#include <iostream>
using namespace std;

// queryList
void queryList::addQuery(int id) {
  queryNode *newNode = new queryNode(id);

  if (this->head == nullptr) { // no entries in list
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
}

void queryList::print() {
  this->head->print();
  cout << endl;
}
// queryNode
void queryNode::print() {
  cout << this->id << " ";
  if (this->next) {
    this->next->print();
  }
}
