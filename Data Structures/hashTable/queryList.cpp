#include "queryList.h"
#include <cstring>
#include <iostream>
using namespace std;

// queryList
queryList::queryList() {
  this->head = nullptr;
  this->last = nullptr;
  this->count = 0;
}
queryList::~queryList() {
  delete this->head;
}
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

queryNode::queryNode(int id) {
  this->id = id;
  this->next = nullptr;
}
queryNode::~queryNode() {
  delete this->next;
}
void queryNode::print() {
  cout << this->id << " ";
  if (this->next) {
    this->next->print();
  }
}
