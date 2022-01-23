
#ifndef DOCUMENT_LIST_H
#define DOCUMENT_LIST_H

#include "../../sigmod/include/core.h"
#include "../string/String.h"
#include <pthread.h>

class DocumentNode {
private:
  Document doc;
  DocumentNode *next;
  DocumentNode *prev;

public:
  DocumentNode(Document doc);
  ~DocumentNode();
  void destroy();
  // void remove();
  // Getters
  Document getDoc() { return this->doc; };
  DocumentNode *getNext() { return this->next; };
  DocumentNode *getPrev() { return this->prev; };
  // Setters
  void setDoc(Document doc) { this->doc = doc; };
  void setNext(DocumentNode *next) { this->next = next; };
  void setPrev(DocumentNode *prev) { this->prev = prev; };
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
  DocumentNode *removeFirst();
  Document getFirst();
  // void addToEnd(Document doc);
  // void removeFromStart();
  // Document getDoc(DocID docId);
  // bool search(DocID docId);
  // void addSorted(Document doc);
};

#endif