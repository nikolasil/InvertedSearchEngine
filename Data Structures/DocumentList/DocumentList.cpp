#include "DocumentList.h"
#include <iostream>

using namespace std;
// ResultList
DocumentList::DocumentList() {
  this->head = NULL;
  this->last = NULL;
  this->count = 0;
  pthread_mutex_init(&(this->mutex), NULL);
}
DocumentList::~DocumentList() {
  DocumentNode *curr = this->head;
  while (curr != nullptr) {
    DocumentNode *temp = curr->getNext();
    delete curr;
    curr = temp;
  }
}

Document DocumentList::getFirst() {
  return this->head->getDoc();
}

void DocumentList::add(Document doc) {
  pthread_mutex_lock(&(this->mutex));
  DocumentNode *newNode = new DocumentNode(doc);

  if (count == 0) {
    this->head = newNode;
    this->last = newNode;
    count++;
    pthread_mutex_unlock(&(this->mutex));
    return;
  }

  this->last->setNext(newNode);
  this->last = newNode;
  count++;
  pthread_mutex_unlock(&(this->mutex));
}

DocumentNode *DocumentList::removeFirst() {
  DocumentNode *temp = this->head;
  this->head = this->head->getNext();
  count--;
  return temp;
}

void DocumentList::print() {
  DocumentNode *curr = this->head;
  while (curr != nullptr) {
    cout << curr->getDoc().doc_id << " ";
    curr = curr->getNext();
  }
  cout << endl;
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