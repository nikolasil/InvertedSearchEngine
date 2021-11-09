#include "entry.h"
#include "../string/String.h"
#include <iostream>

using namespace std;

// entry
entry::entry(const word *w, void *payload) {
  this->w = (word *)w;
  this->payload = payload;
}

entry::entry() {
  this->w = nullptr;
  this->payload = nullptr;
  this->next = nullptr;
}

entry::~entry() {
  if (this->w != nullptr) {
    delete this->w;
  }
  if (this->next != nullptr) {
    delete this->next;
  }
  // delete this->payload;
}

void entry::print() {
  w->print();
  if (this->next)
    cout << " -> ";
  else
    cout << "\n";
}
