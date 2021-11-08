#include "entry.h"
#include "../string/String.h"
#include <iostream>

using namespace std;

// entry
entry::entry(const word *w, void *payload) {
  this->w = (word *)w;
  this->payload = payload;
}

entry::~entry() {
  delete this->w;
  // delete this->payload;
  delete this->next;
}

void entry::print() {
  w->print();
  if (this->next)
    cout << " -> ";
  else
    cout << "\n";
}
