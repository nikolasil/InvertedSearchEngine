#ifndef Queue_H
#define Queue_H

#include "Job.h"

class QueueNode {
private:
  Job *job;
  QueueNode *next;
  QueueNode *prev;

public:
  QueueNode(Job *data);
  ~QueueNode();
  // Getters
  Job *getJob() { return this->job; };
  QueueNode *getNext() { return this->next; };
  QueueNode *getPrev() { return this->prev; };
  // Setters
  void setJob(Job *data) { this->job = data; };
  void setNext(QueueNode *next) { this->next = next; };
  void setPrev(QueueNode *prev) { this->prev = prev; };
  // Utility
  void print();
};

class Queue {
private:
  QueueNode *head;
  QueueNode *tail;
  int size;

public:
  Queue();
  ~Queue();
  // Getters
  QueueNode *getHead() { return this->head; };
  QueueNode *getTail() { return this->tail; };
  int getSize() { return this->size; };
  // Setters
  void setHead(QueueNode *head) { this->head = head; };
  void setTail(QueueNode *tail) { this->tail = tail; };
  void setSize(int size) { this->size = size; };
  // Utility
  void addToHead(Job *job);
  void add(Job *job);
  QueueNode *remove();
  char getLastJobType();

  void print();
};

#endif