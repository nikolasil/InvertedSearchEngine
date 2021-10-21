#ifndef ENTRY_H
#define ENTRY_H

#include "string/String.h"

class entry
{
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

class word
{
private:
  String *str;

public:
  word(const char *string);
  ~word();
  // GETTERS
  String *getWord() { return this->str; };
  // SETTERS
  void setWord(char *string) { this->str = new String(string); };
  void setWord(String *string) { this->str = string; };
};

#endif