#ifndef ResultList_H
#define ResultList_H

#include "../string/String.h"
#include <pthread.h>
class ResultListNode {
private:
  int id;
  ResultListNode *next;

public:
  ResultListNode(int id);
  ~ResultListNode();
  // Getters
  int getId() { return this->id; };
  ResultListNode *getNext() { return this->next; };
  // Setters
  void setId(int id) { this->id = id; };
  void setNext(ResultListNode *next) { this->next = next; };
};

class ResultList {
private:
  ResultListNode *head;
  ResultListNode *last;
  int count;
  pthread_mutex_t mutex;

public:
  ResultList();
  ~ResultList();
  void destroy();
  // Getters
  int getCount() { return this->count; };
  ResultListNode *getHead() { return this->head; };
  ResultListNode *getLast() { return this->last; };
  // Setters
  void setCount(int count) { this->count = count; };
  void setHead(ResultListNode *head) { this->head = head; };
  void setLast(ResultListNode *last) { this->last = last; };
  // Methods
  void add(int id);
  void remove(int id);
  bool search(int id);
  bool searchRemove(int id);
  void print();
};

#endif