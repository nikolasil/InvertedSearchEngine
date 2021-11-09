#include "linkedList.h"
#include <cstring>
#include <iostream>
using namespace std;
// Linked List
linkedList::linkedList() {
  this->head = nullptr;
  this->last = nullptr;
  this->count = 0;
}

linkedList::~linkedList() {
  delete this->head;
}

void linkedList::print() {
  this->head->print();
  cout << endl;
}

listNode *linkedList::addNode(String *word) {

  listNode *newNode = new listNode(word);
  if (this->head == nullptr) { // no entries in entry list
    this->head = newNode;
  } else {
    this->last->setNext(newNode);
  }
  this->last = newNode;
  count++;
  return 0;
}

listNode *linkedList::getNode(String *word) {
  listNode *current = this->head;
  while (current) {
    if (!strcmp(current->getWord()->getStr(), word->getStr())) {
      return current;
    }
    current = current->getNext();
  }
  return nullptr;
}

// List Node

listNode::listNode(String *word) {
  this->word = word;
}

listNode::~listNode() {
  delete this->word;
  delete this->next;
}

void listNode::print() {
  cout << this->word->getStr() << " ";
  if (this->next) {
    this->next->print();
  }
}

String *listNode::getWord() {
  return this->word;
}

void listNode::setNext(listNode *next) {
  this->next = next;
}

listNode *listNode::getNext() {
  return this->next;
}
