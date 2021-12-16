#include "heInfoList.h"
#include <cstring>
#include <iostream>
using namespace std;

// heInfoList
heInfoList::heInfoList() {
  this->head = nullptr;
  this->last = nullptr;
  this->count = 0;
}
heInfoList::~heInfoList() {
  if (this->head) {
    delete this->head;
  }
}
void heInfoList::addQuery(HEInfo *wordInfo) {
  heInfoNode *newNode = new heInfoNode(wordInfo);

  if (this->head == nullptr) { // no entries in list
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
}

void heInfoList::print() {
  if (this->head != nullptr) {
    this->head->print();
    cout << endl;
  }
}
// heInfoNode

heInfoNode::heInfoNode(HEInfo *info) {
  this->info = info;
  this->next = nullptr;
}
heInfoNode::~heInfoNode() {
  // if (this->info != nullptr) {
  //   delete this->info;
  // }
  if (this->next != nullptr) {
    delete this->next;
  }
}
void heInfoNode::print() {
  cout << "{" << this->getId() << "," << this->getMaxQueryWords() << "," << this->getMatchDist() << "}  ";
  if (this->next) {
    this->next->print();
  }
}
