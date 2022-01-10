#include "Queue.h"
#include <iostream>

using namespace std;

QueueNode::QueueNode(Job *data) {
  this->job = data;
  this->next = NULL;
}

QueueNode ::~QueueNode() {}

void QueueNode::print() {
  cout << "Job: " << this->job->getType() << endl;
}

Queue::Queue() {
  this->head = NULL;
  this->tail = NULL;
  this->size = 0;
}

Queue::~Queue() {}

void Queue::add(Job *job) {
  QueueNode *node = new QueueNode(job);
  if (this->head == NULL) {
    this->head = node;
    this->tail = node;
  } else {
    node->setNext(this->head);
    this->head = node;
  }
  this->size++;
}

QueueNode *Queue::remove() {
  QueueNode *node = this->tail;
  if (this->tail == this->head) {
    this->head = NULL;
    this->tail = NULL;
  } else {
    QueueNode *temp = this->head;
    while (temp->getNext() != this->tail) {
      temp = temp->getNext();
    }
    this->tail = temp;
    this->tail->setNext(NULL);
  }
  this->size--;
  return node;
}

int Queue::getLastJobEpoch() {
  int epoch = 0;
  if (this->head != NULL) {
    epoch = this->head->getJob()->getEpoch();
  }
  return epoch;
}

void Queue::print() {
  QueueNode *temp = this->head;
  while (temp != NULL) {
    temp->print();
    temp = temp->getNext();
  }
}