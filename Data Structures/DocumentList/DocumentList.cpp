#include "DocumentList.h"
#include <iostream>

using namespace std;
// ResultList
DocumentList::DocumentList() {
  this->head = NULL;
  this->last = NULL;
  this->count = 0;
}
DocumentList::~DocumentList() {
  DocumentNode *curr = this->head;
  while (curr != nullptr) {
    DocumentNode *temp = curr->getNext();
    delete curr;
    curr = temp;
  }
}
void DocumentList::addToEnd(Document doc) {
  DocumentNode *newNode = new DocumentNode(doc);

  if (count == 0) {
    this->head = newNode;
    this->last = newNode;
    count++;
    return;
  }

  this->last->setNext(newNode);
  this->last = newNode;
  count++;
}

void DocumentList::removeFromStart() {
  if (count > 0) {
    DocumentNode *temp = this->head;
    this->head = this->head->getNext();
    if (this->head == nullptr) {
      this->last = nullptr;
    }
    count--;
    delete temp;
  }
}

// DocumentNode
DocumentNode::DocumentNode(Document doc) {
  this->doc = doc;
  this->next = nullptr;
}
DocumentNode::~DocumentNode() {}

void DocumentList::destroy() {
  if (this->head != nullptr) {
    this->head->destroy();
  }
}

void DocumentNode::destroy() {
  if (this->next != nullptr) {
    this->next->destroy();
  }
}