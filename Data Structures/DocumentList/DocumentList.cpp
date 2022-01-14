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

void DocumentList::remove(DocID docId) {
  pthread_mutex_lock(&(this->mutex));
  DocumentNode *curr = this->head;
  DocumentNode *prev = NULL;
  while (curr != NULL) {
    if (curr->getDoc().doc_id == docId) {
      if (prev == NULL) {
        this->head = curr->getNext();
        if (this->head == NULL) {
          this->last = NULL;
        }
      } else {
        prev->setNext(curr->getNext());
        if (curr == this->last) {
          this->last = prev;
        }
      }
      count--;
      delete curr;
      // cout << "count: " << count << endl;
      pthread_mutex_unlock(&(this->mutex));
      return;
    }
    prev = curr;
    curr = curr->getNext();
  }
  pthread_mutex_unlock(&(this->mutex));
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
  pthread_mutex_init(&(this->mutex), NULL);
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