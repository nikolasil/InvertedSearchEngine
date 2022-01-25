#include "Queue.h"
#include <iostream>

using namespace std;

QueueNode::QueueNode(Job *data) {
  this->job = data;
  this->next = NULL;
  this->prev = NULL;
}

QueueNode ::~QueueNode() {
  if (this->job != NULL) {
    delete this->job;
  }
  if (this->next != NULL) {
    delete this->next;
  }
}

void QueueNode::print() {
  cout << "Job: " << this->job->getType() << endl;
}

Queue::Queue() {
  this->head = NULL;
  this->tail = NULL;
  this->size = 0;
}

Queue::~Queue() {
  if (this->head != NULL) {
    delete this->head;
  }
}

void Queue::add(Job *job) {
  QueueNode *node = new QueueNode(job);
  if (this->head == NULL) {
    this->head = node;
    this->tail = node;
  } else {
    this->tail->setNext(node);
    node->setPrev(this->tail);
    this->tail = node;
  }
  this->size++;
}
void Queue::addToHead(Job *job) {
  QueueNode *node = new QueueNode(job);
  if (this->head == NULL) {
    this->head = node;
    this->tail = node;
  } else {
    this->head->setPrev(node);
    node->setNext(this->head);
    this->head = node;
  }
  this->size++;
}

QueueNode *Queue::remove() {
  QueueNode *node = this->head;
  if (this->head == NULL) {
    return NULL;
  }
  if (this->head == this->tail) {
    this->head = NULL;
    this->tail = NULL;
  } else {
    this->head = this->head->getNext();
    this->head->setPrev(NULL);
  }
  this->size--;
  node->setNext(NULL);
  node->setPrev(NULL);
  return node;
}

char Queue::getLastJobType() {
  char type = 't';
  if (this->tail != NULL) {
    type = this->tail->getJob()->getType();
  }
  return type;
}

void Queue::print() {
  QueueNode *temp = this->head;
  while (temp != NULL) {
    temp->print();
    temp = temp->getNext();
  }
}