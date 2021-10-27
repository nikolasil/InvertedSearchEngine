#ifndef ENTRY_H
#define ENTRY_H

#include "../string/String.h"

class word {
private:
  String *str;

public:
  word(const char *string);
  ~word();
  // GETTERS
  String *getStr() { return this->str; };
  // SETTERS
  void setStr(char *string) { this->str = new String(string); };
  void setStr(String *string) { this->str = string; };
  void print() { this->str->print(); };
};

class entry {
private:
  word *w;
  void *payload;
  entry *next;

public:
  entry(const word *w, void *payload);
  ~entry();
  // GETTERS
  word *getWord() { return this->w->getStr(); };
  void *getPayload() { return this->payload; };
  entry *getNext() { return this->next; };
  // SETTERS
  void setNext(entry *e) { this->next = e; };

  void print();
};
#endif