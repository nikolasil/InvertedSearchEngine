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

void DocumentList::addToEnd(Document doc) {
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

void DocumentList::removeFromStart() {
  pthread_mutex_lock(&(this->mutex));
  if (count > 0) {
    DocumentNode *temp = this->head;
    this->head = this->head->getNext();
    if (this->head == nullptr) {
      this->last = nullptr;
    }
    count--;
    delete temp;
  }
  pthread_mutex_unlock(&(this->mutex));
}

Document DocumentList::getDoc(DocID docId) {
  pthread_mutex_lock(&(this->mutex));
  DocumentNode *curr = this->head;
  while (curr != NULL) {
    if (curr->getDoc().doc_id == docId) {
      pthread_mutex_unlock(&(this->mutex));
      return curr->getDoc();
    }
    curr = curr->getNext();
  }
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
      pthread_mutex_unlock(&(this->mutex));
      return;
    }
    prev = curr;
    curr = curr->getNext();
  }
  pthread_mutex_unlock(&(this->mutex));
}

bool DocumentList::search(DocID docId) {
  pthread_mutex_lock(&(this->mutex));
  DocumentNode *curr = this->head;
  while (curr != nullptr) {
    if (curr->getDoc().doc_id == docId) {
      pthread_mutex_unlock(&(this->mutex));
      return true;
    }
    curr = curr->getNext();
  }
  pthread_mutex_unlock(&(this->mutex));
  return false;
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