#include "bucket.h"
#include <cstring>
#include <iostream>
using namespace std;

// Bucket List

Bucket::~Bucket() {
  if (this->head != nullptr) {
    delete this->head;
  }
}

void Bucket::print() {
  this->head->print();
  // cout << endl;
}

bucketNode *Bucket::addNode(String *word, int qId) {
  bucketNode *exists = this->getNode(word);
  if (exists != nullptr) {
    exists->addToQueryList(qId);
    return exists;
  }

  bucketNode *newNode = new bucketNode(word, qId);
  if (this->head == nullptr) { // no entries
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
  return newNode;
}

bucketNode *Bucket::getNode(String *word) {
  bucketNode *current = this->head;
  while (current != nullptr) {
    if (!strcmp(current->getWord()->getStr(), word->getStr())) {
      return current;
    }
    current = current->getNext();
  }
  return nullptr;
}

// Bucket Node

bucketNode::bucketNode(String *word, int qId) {
  this->word = word;
  this->next = nullptr;
  this->list = new queryList();
  this->list->addQuery(qId);
}

bucketNode::~bucketNode() {
  if (this->next != nullptr) {
    delete this->next;
  }
}

void bucketNode::addToQueryList(int qId) {
  this->list->addQuery(qId);
}

void bucketNode::print() {
  cout << "\t" << this->word->getStr() << " ";
  this->list->print();
  if (this->next) {
    this->next->print();
  }
}