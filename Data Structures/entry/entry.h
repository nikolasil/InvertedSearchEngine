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
  entry();
  ~entry();

  // Getters
  word *getWord() { return this->w; };           // get word
  void *getPayload() { return this->payload; };  // get payload
  entry *getNext() const { return this->next; }; // get next entry node
  // Setters
  void setNext(entry *e) { this->next = e; };
  void setPayload(void *payload) { this->payload = payload; } // update payload
  void setWord(word *w) { this->w = w; }                      // update word

  void print();
};
#endif