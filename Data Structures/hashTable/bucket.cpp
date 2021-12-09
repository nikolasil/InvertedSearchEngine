#include "bucket.h"
#include <cstring>
#include <iostream>
using namespace std;
// Linked List
Bucket::Bucket() {
  this->head = nullptr;
  this->last = nullptr;
  this->count = 0;
}

Bucket::~Bucket() {
  if (this->head != nullptr) {
    delete this->head;
  }
}

void Bucket::print() {
  this->head->print();
  cout << endl;
}

bucketNode *Bucket::addNode(String *word) {

  bucketNode *newNode = new bucketNode(word);
  if (this->head == nullptr) { // no entries in entry list
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
  return 0;
}

bucketNode *Bucket::getNode(String *word) {
  bucketNode *current = this->head;
  while (current) {
    if (!strcmp(current->getWord()->getStr(), word->getStr())) {
      return current;
    }
    current = current->getNext();
  }
  return nullptr;
}

// List Node

bucketNode::bucketNode(String *word) {
  this->word = word;
  this->next = nullptr;
}

bucketNode::~bucketNode() {
  if (this->next != nullptr) {
    delete this->next;
  }
}

void bucketNode::print() {
  cout << this->word->getStr() << " ";
  if (this->next) {
    this->next->print();
  }
}

String *bucketNode::getWord() {
  return this->word;
}

void bucketNode::setNext(bucketNode *next) {
  this->next = next;
}

bucketNode *bucketNode::getNext() {
  return this->next;
}
