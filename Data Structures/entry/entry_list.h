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

  // Getters
  entry *getStart() const { return this->start; }; // get start
  entry *getEnd() const { return this->end; };     // get end
  unsigned int getCount() const;                   // get count

  // Setters
  void setStart(entry *start) { this->start = start; } // set start
  void setEnd(entry *end) { this->end = end; }         // set end

  // Utils
  linkedList *generateLinkedList() const;                       // generate a linked list based from the word of each entry
  entry *getNext(const entry *e) const { return e->getNext(); } // get next
  int addEntry(entry *e);
  void print();
};

#endif