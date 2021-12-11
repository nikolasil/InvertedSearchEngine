#include "ResultList.h"
#include <iostream>

using namespace std;
// ResultList
ResultList::ResultList() {
  this->head = NULL;
  this->last = NULL;
  this->count = 0;
}
ResultList::~ResultList() {
}
void ResultList::add(int id) {
  ResultListNode *newNode = new ResultListNode(id);
  if (this->head == nullptr) {
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
}

void ResultList::remove(int id) {
  ResultListNode *current = this->head;
  ResultListNode *previous = nullptr;
  while (current != nullptr) {
    if (current->getId() == id) {
      if (previous == nullptr) {
        this->head = current->getNext();
      } else {
        previous->setNext(current->getNext());
      }
      delete current;
      count--;
      break;
    }
    previous = current;
    current = current->getNext();
  }
}
void ResultList::print() {
  ResultListNode *current = this->head;
  while (current != nullptr) {
    cout << current->getId() << " ";
    current = current->getNext();
  }
  cout << endl;
}
// ResultListNode
ResultListNode::ResultListNode(int id) {
  this->id = id;
  this->next = nullptr;
}
ResultListNode::~ResultListNode() {}