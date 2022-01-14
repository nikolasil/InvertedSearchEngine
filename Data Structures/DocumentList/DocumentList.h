
#ifndef DOCUMENT_LIST_H
#define DOCUMENT_LIST_H

#include "../../sigmod/include/core.h"
#include "../string/String.h"
#include <pthread.h>

class DocumentNode {
private:
  Document doc;
  DocumentNode *next;
  pthread_mutex_t mutex;

public:
  DocumentNode(Document doc);
  ~DocumentNode();
  void destroy();
  // void remove();
  // Getters
  Document getDoc() { return this->doc; };
  DocumentNode *getNext() { return this->next; };
  // Setters
  void setDoc(Document doc) {
    pthread_mutex_lock(&(this->mutex));
    this->doc = doc;
    pthread_mutex_unlock(&(this->mutex));
  };
  void setNext(DocumentNode *next) {
    pthread_mutex_lock(&(this->mutex));
    this->next = next;
    pthread_mutex_unlock(&(this->mutex));
  };
};

class DocumentList {
private:
  DocumentNode *head;
  DocumentNode *last;
  pthread_mutex_t mutex;
  int count;

public:
  DocumentList();
  ~DocumentList();
  void destroy();
  // Getters
  int getCount() { return this->count; };
  DocumentNode *getHead() { return this->head; };
  DocumentNode *getLast() { return this->last; };
  // Setters
  void setCount(int count) { this->count = count; };
  void setHead(DocumentNode *head) { this->head = head; };
  void setLast(DocumentNode *last) { this->last = last; };
  // Methods
  void print();
  void add(Document doc);
  void remove(DocID docId);
  Document getFirst();
  // void addToEnd(Document doc);
  // void removeFromStart();
  // Document getDoc(DocID docId);
  // bool search(DocID docId);
  // void addSorted(Document doc);
};

#endif