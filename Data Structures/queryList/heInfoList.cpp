#include "heInfoList.h"
#include <cstring>
#include <iostream>
using namespace std;

// heInfoList
heInfoList::heInfoList() {
  this->head = nullptr;
  this->last = nullptr;
  this->count = 0;
  pthread_mutex_init(&(this->mutex), NULL);
}
heInfoList::~heInfoList() {
  if (this->head != nullptr) {
    delete this->head;
    this->head = nullptr;
  }
}
void heInfoList::addQuery(HEInfo *wordInfo) {
  pthread_mutex_lock(&(this->mutex));
  heInfoNode *newNode = new heInfoNode(wordInfo);

  if (this->head == nullptr) { // no entries in list
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
  pthread_mutex_unlock(&(this->mutex));
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
  pthread_mutex_init(&(this->mutex), NULL);
}
heInfoNode::~heInfoNode() {
  if (this->next != nullptr) {
    delete this->next;
    this->next = nullptr;
  }
}
void heInfoNode::print() {
  cout << "{" << this->getId() << "," << this->getMaxQueryWords() << "," << this->getMatchDist() << "}  ";
  if (this->next) {
    this->next->print();
  }
}

void heInfoNode::destroy() {
  delete this->info;
  if (this->next != nullptr) {
    this->next->destroy();
  }
}

void heInfoList::destroy() {
  if (this->head != nullptr) {
    this->head->destroy();
  }
}