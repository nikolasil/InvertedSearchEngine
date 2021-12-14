#include "exactInfoList.h"
#include <cstring>
#include <iostream>
using namespace std;

// exactInfoList
exactInfoList::exactInfoList() {
  this->head = nullptr;
  this->last = nullptr;
  this->count = 0;
}
exactInfoList::~exactInfoList() {
  delete this->head;
}
void exactInfoList::addQuery(ExactInfo wordInfo) {
  exactInfoNode *newNode = new exactInfoNode(wordInfo);

  if (this->head == nullptr) { // no entries in list
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
}

void exactInfoList::print() {
  this->head->print();
  cout << endl;
}
// exactInfoNode

exactInfoNode::exactInfoNode(ExactInfo info) {
  this->info = info;
  this->next = nullptr;
}
exactInfoNode::~exactInfoNode() {
  delete this->next;
}
void exactInfoNode::print() {
  cout << "{" << this->getId() << "," << this->getMaxQueryWords() << "}  ";
  if (this->next) {
    this->next->print();
  }
}
