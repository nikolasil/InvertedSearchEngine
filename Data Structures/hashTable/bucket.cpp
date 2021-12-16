#include "bucket.h"
#include <cstring>
#include <iostream>
using namespace std;

// Bucket List

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
}

exactInfoList *Bucket::lookup(String *word, String **matchedWord) {
  bucketNode *temp = this->head;
  while (temp != nullptr) {
    if (temp->getWord()->exactMatch(word)) {
      (*matchedWord)->setStr(temp->getWord()->getStr());
      return temp->getList();
    }
    temp = temp->getNext();
  }
  return nullptr;
}

bucketNode *Bucket::addNode(String *word, ExactInfo *wordInfo) {
  bucketNode *exists = this->getNode(word);
  if (exists != nullptr) {
    exists->addToQueryList(wordInfo);
    return exists;
  }

  bucketNode *newNode = new bucketNode(word, wordInfo);
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

bucketNode::bucketNode(String *word, ExactInfo *wordInfo) {
  this->word = word;
  this->next = nullptr;
  this->list = new exactInfoList();
  this->addToQueryList(wordInfo);
}

bucketNode::~bucketNode() {
  // if (this->word != nullptr) {
  //   delete this->word;
  // }
  if (this->next != nullptr) {
    delete this->next;
  }
  if (this->list != nullptr) {
    delete this->list;
  }
}

void bucketNode::addToQueryList(ExactInfo *wordInfo) {
  this->list->addQuery(wordInfo);
}

void bucketNode::print() {
  cout << "\t" << this->word->getStr() << " ";
  this->list->print();
  if (this->next) {
    this->next->print();
  }
}