#ifndef queryList_H
#define queryList_H

#include "../../sigmod/include/core.h"
class queryNode {
private:
  WordInfo info;
  queryNode *next;

public:
  queryNode(WordInfo info);
  ~queryNode();
  //  Getters
  int getId() const { return this->info.query_id; };
  unsigned int getMaxQueryWords() const { return this->info.maxQueryWords; };
  WordInfo getWordInfo() const { return this->info; };
  queryNode *getNext(queryNode *next) const { return this->next; };
  // Setters
  void setId(int id) { this->info.query_id = id; };
  void setMaxQueryWords(int max) { this->info.maxQueryWords = max; };
  void setWordInfo(WordInfo wi) { this->info = wi; };
  void setNext(queryNode *next) { this->next = next; };
  void print();
};

class queryList {
private:
  queryNode *head;
  queryNode *last;
  int count;

public:
  queryList();
  ~queryList();
  // Getters
  queryNode *getHead() const { return this->head; };
  queryNode *getLast() const { return this->last; };
  int getCount() const { return this->count; };
  // Setters
  void setHead(queryNode *head) { this->head = head; };
  void setLast(queryNode *last) { this->last = last; };
  void setCount(int count) { this->count = count; };
  // Methods
  void addQuery(WordInfo wordInfo);
  void print();
};

#endif