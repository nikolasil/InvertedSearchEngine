#include "queryList.h"
#include <cstring>
#include <iostream>
using namespace std;

// queryList
queryList::queryList() {
  this->head = nullptr;
  this->last = nullptr;
  this->count = 0;
}
queryList::~queryList() {
  delete this->head;
}
void queryList::addQuery(WordInfo wordInfo) {
  queryNode *newNode = new queryNode(wordInfo.query_id, wordInfo.maxQueryWords);

  if (this->head == nullptr) { // no entries in list
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
}

void queryList::print() {
  this->head->print();
  cout << endl;
}
// queryNode

queryNode::queryNode(int id, int maxQueryWords) {
  this->id = id;
  this->maxQueryWords = maxQueryWords;
  this->next = nullptr;
}
queryNode::~queryNode() {
  delete this->next;
}
void queryNode::print() {
  cout << this->id << " ";
  if (this->next) {
    this->next->print();
  }
}
