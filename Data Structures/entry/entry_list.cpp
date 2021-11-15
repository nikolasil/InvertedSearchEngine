#include "entry_list.h"
#include "../linkedList/linkedList.h"
#include <iostream>

using namespace std;
entry_list::entry_list() {
  this->start = nullptr;
  this->end = nullptr;
  this->count = 0;
}

int entry_list::addEntry(entry *e) {
  if (this->start == nullptr) { // no entries in entry list
    this->start = e;
  } else {
    this->end->setNext(e);
  }
  this->end = e;
  count++;
  return 0;
}

entry_list::~entry_list() {
  if (this->start != nullptr) {
    delete this->start;
  }
}

unsigned int entry_list::getCount() const {
  return this->count;
}

void entry_list::print() {
  entry *current = this->start;
  while (current) {
    current->print();
    current = current->getNext();
  }
}

linkedList *entry_list::generateLinkedList() const {
  linkedList *list = new linkedList();
  entry *current = this->start;

  while (current != nullptr) {
    list->addNode(current->getWord());
    current = current->getNext();
  }
  return list;
}
