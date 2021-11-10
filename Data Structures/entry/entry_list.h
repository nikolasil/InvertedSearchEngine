#ifndef ENTRYLIST_H
#define ENTRYLIST_H

#include "../linkedList/linkedList.h"
#include "../string/String.h"
#include "entry.h"

class entry_list {
private:
  entry *start;
  entry *end;
  unsigned int count;

public:
  entry_list();
  ~entry_list();
  int addEntry(entry *e);
  unsigned int getCount() const;
  entry *getStart() const { return this->start; };
  entry *getEnd() const { return this->end; };
  entry *getNext(const entry *e) const { return e->getNext(); }
  linkedList *generateLinkedList() const;
  void print();
};

#endif