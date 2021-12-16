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
  if (this->head != nullptr) {
    delete this->head;
  }
}
void DocumentList::addToEnd(Document *doc) {
  DocumentNode *newNode = new DocumentNode(doc);

  if (count == 0) {
    this->head = this->last = newNode;
    count++;
    return;
  }

  this->last->setNext(newNode);
  this->last = newNode;
  count++;
}

void DocumentList::removeFromStart() {
  if (count > 0) {
    this->head = this->head->getNext();
    if (this->head == nullptr) {
      this->last = nullptr;
    }
    count--;
  }
}

// DocumentNode
DocumentNode::DocumentNode(Document *doc) {
  this->doc = doc;
  this->next = nullptr;
}
DocumentNode::~DocumentNode() {
  // if (this->doc != nullptr) {
  //   if (doc->query_ids != nullptr) {
  //     delete[] doc->query_ids;
  //   }
  //   delete doc;
  // }
  if (this->next != nullptr) {
    delete this->next;
  }
}