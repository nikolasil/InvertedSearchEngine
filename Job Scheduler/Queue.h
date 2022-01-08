#ifndef Queue_H
#define Queue_H

#include "Job.h"

class QueueNode {
private:
  Job *job;
  QueueNode *next;

public:
  QueueNode(Job *data);
  ~QueueNode();
  // Getters
  Job *getJob() { return this->job; };
  QueueNode *getNext() { return this->next; };
  // Setters
  void setJob(Job *data) { this->job = data; };
  void setNext(QueueNode *next) { this->next = next; };
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
  void add(Job *job);
  QueueNode *remove();

  void print();
};

#endif