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
    this->head = nullptr;
  }
}

void Bucket::print() {
  this->head->print();
}

void Bucket::lookup(String *word, MatchArray *MatchArray, ResultList *forDelition) {
  bucketNode *temp = this->head;
  while (temp != nullptr) {
    if (temp->getWord()->exactMatch(word)) {

      exactInfoNode *cur = temp->getList()->getHead();
      while (cur != nullptr) {
        if (forDelition->searchRemove(cur->getId())) {
          cur->setFlag(false);
        } else if (cur->getFlag())
          MatchArray->insert(temp->getWord(), cur->getId(), cur->getMaxQueryWords());
        cur = cur->getNext();
      }
    }
    temp = temp->getNext();
  }
  return;
}

bucketNode *Bucket::addNode(String *word, ExactInfo *wordInfo) {
  bucketNode *exists = this->getNode(word);
  if (exists != nullptr) {
    exists->addToQueryList(wordInfo);
    delete word;
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
    if (current->getWord()->exactMatch(word)) {
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
  if (this->word != nullptr) {
    delete this->word;
    this->word = nullptr;
  }
  if (this->next != nullptr) {
    delete this->next;
    this->next = nullptr;
  }
  if (this->list != nullptr) {
    delete this->list;
    this->list = nullptr;
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