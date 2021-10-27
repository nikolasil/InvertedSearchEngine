#include "linkedList.h"
#include <cstring>
#include <iostream>
using namespace std;
// Linked List
linkedList::linkedList() {
  this->head = nullptr;
}

linkedList::~linkedList() {
  delete this->head;
}

void linkedList::print() {
  this->head->print();
}

listNode *linkedList::addNode(String *word) {

  listNode *newNode = new listNode(word);
  newNode->setNext(this->head);
  return (this->head = newNode);
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
  if (!this->next)
    return;

  cout << this->word->getStr() << " ";
  this->next->print();
  cout << endl;
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
