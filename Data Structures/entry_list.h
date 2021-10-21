#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include "entry.h"
#include "string/String.h"
class entry_list {
private:
  entry *start;
  entry *end;
  int count;

public:
  entry_list();
  ~entry_list();
  int addEntry(entry *e);
  int getCount();
  entry *getStart() { return this->start; };
  entry *getEnd() { return this->end; };
  void print();
};

#endif