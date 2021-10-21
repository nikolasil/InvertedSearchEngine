#include "entry_list.h"

entry_list::entry_list() {
  this->start = this->end = nullptr;
  this->count = 0;
}

int entry_list::addEntry(entry *e) {
  if (!this->start || !this->end) {
    return -1; //entry list not initialized
  }
  if (this->start == nullptr) { //no entries in entry list
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

int entry_list::getCount() {
  if (!this->count) {
    return -1;
  } else {
    return this->count;
  }
}
