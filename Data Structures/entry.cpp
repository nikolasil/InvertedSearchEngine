#include <iostream>
#include "entry.h"
#include "string/String.h"
// entry
entry::entry(const word *w, void *payload) {
  this->w = (word *)w;
  this->payload = payload;
}

entry::~entry() {
  delete this->w;
  delete this->payload;
  delete this->next;
}

void entry::print() {
  w->print();
  if (this->next)
    cout << " -> ";
  else
    cout << "\n";
}

// word
word::word(const char *string) { this->str = new String(string); }

word::~word() { delete this->str; }