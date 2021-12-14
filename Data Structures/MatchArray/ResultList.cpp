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
  ResultListNode *curr = this->head;
  ResultListNode *prev = nullptr;
  if (curr == NULL) {
    this->head = newNode;
    this->last = newNode;
    count++;
    return;
  }
  while (curr != nullptr) {
    if (curr->getId() > id) {
      if (prev == nullptr) {
        this->head = newNode;
        newNode->setNext(curr);
        count++;
        return;
      }
      newNode->setNext(curr);
      prev->setNext(newNode);
      count++;
      return;
    }
    prev = curr;
    curr = curr->getNext();
  }
  this->last = newNode;
  prev->setNext(newNode);

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