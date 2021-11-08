#ifndef ENTRY_H
#define ENTRY_H

#include "../string/String.h"

typedef String word;

class entry {
private:
  word *w;
  void *payload;
  entry *next;

public:
  entry(const word *w, void *payload);
  ~entry();
  // GETTERS
  word *getWord() { return this->w; };
  void *getPayload() { return this->payload; };
  entry *getNext() { return this->next; };
  // SETTERS
  void setNext(entry *e) { this->next = e; };

  void print();
};
#endif