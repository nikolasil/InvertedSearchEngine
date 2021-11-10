#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../string/String.h"

class listNode {
private:
  String *word;
  listNode *next;

public:
  listNode(String *word);
  ~listNode();
  String *getWord();
  void setNext(listNode *next);
  listNode *getNext();
  void print();
};
class linkedList {
private:
  listNode *head;
  listNode *last;
  int count;

public:
  linkedList();
  ~linkedList();
  listNode *addNode(String *word);
  listNode *getNode(String *word);
  listNode *getHead() const { return this->head; };
  void print();
};

#endif