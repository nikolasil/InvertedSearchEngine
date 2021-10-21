#ifndef ENTRY_H
#define ENTRY_H

#include "string/String.h"

class entry {
private:
  word *w;
  void *payload;
  entry *next;

public:
  entry(const word *w, void *payload);
  entry *getNext() { return this->next; };
  void setNext(entry *e) { this->next = e; };
  ~entry();
};

class word {
private:
  String *str;

public:
  word(const char *string);
  ~word();
};

#endif