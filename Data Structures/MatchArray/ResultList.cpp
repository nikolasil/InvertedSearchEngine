#include "ResultList.h"
#include <iostream>

using namespace std;
// ResultList
ResultList::ResultList() {
  this->head = NULL;
  this->last = NULL;
  this->count = 0;
  pthread_mutex_init(&(this->mutex), NULL);
}
ResultList::~ResultList() {
  if (this->head != nullptr) {
    delete this->head;
    this->head = nullptr;
  }
}
void ResultList::add(int id) {
  pthread_mutex_lock(&(this->mutex));
  ResultListNode *newNode = new ResultListNode(id);
  ResultListNode *curr = this->head;
  ResultListNode *prev = nullptr;
  if (curr == NULL) {
    this->head = newNode;
    this->last = newNode;
    count++;
    pthread_mutex_unlock(&(this->mutex));
    return;
  }
  while (curr != nullptr) {
    if (curr->getId() > id) {
      if (prev == nullptr) {
        this->head = newNode;
        newNode->setNext(curr);
        count++;
        pthread_mutex_unlock(&(this->mutex));
        return;
      }
      newNode->setNext(curr);
      prev->setNext(newNode);
      count++;
      pthread_mutex_unlock(&(this->mutex));
      return;
    }
    prev = curr;
    curr = curr->getNext();
  }
  this->last = newNode;
  prev->setNext(newNode);
  count++;
  pthread_mutex_unlock(&(this->mutex));
}

void ResultList::remove(int id) {
  pthread_mutex_lock(&(this->mutex));
  ResultListNode *current = this->head;
  ResultListNode *previous = nullptr;
  while (current != nullptr) {
    if (current->getId() == id) {
      if (previous == nullptr) {
        this->head = current->getNext();
        this->last = this->head;
      } else {
        previous->setNext(current->getNext());
      }
      delete current;
      count--;
      pthread_mutex_unlock(&(this->mutex));
      break;
    }
    previous = current;
    current = current->getNext();
  }
  pthread_mutex_unlock(&(this->mutex));
}
bool ResultList::search(int id) {
  ResultListNode *current = this->head;
  while (current != nullptr) {
    if (current->getId() == id) {
      return true;
    }
    current = current->getNext();
  }
  return false;
}

bool ResultList::searchRemove(int id) {
  pthread_mutex_lock(&(this->mutex));
  ResultListNode *current = this->head;
  ResultListNode *previous = nullptr;
  while (current != nullptr) {
    if (current->getId() == id) {
      if (previous == nullptr) {
        this->head = current->getNext();
        this->last = this->head;
      } else {
        previous->setNext(current->getNext());
      }
      delete current;
      count--;
      pthread_mutex_unlock(&(this->mutex));
      return true;
    }
    previous = current;
    current = current->getNext();
  }
  pthread_mutex_unlock(&(this->mutex));
  return false;
}
void ResultList::print() {
  ResultListNode *current = this->head;
  while (current != nullptr) {
    cout << current->getId() << " ";
    current = current->getNext();
  }
  cout << endl;
}
// ResultListNode
ResultListNode::ResultListNode(int id) {
  this->id = id;
  this->next = nullptr;
}
ResultListNode::~ResultListNode() {}

void ResultList::destroy() {
  ResultListNode *current = this->getHead();
  while (current != nullptr) {
    ResultListNode *temp = current->getNext();
    delete current;
    current = temp;
  }
  this->setHead(nullptr);
}