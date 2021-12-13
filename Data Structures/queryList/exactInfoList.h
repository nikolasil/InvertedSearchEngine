#ifndef EXACTINFOLIST_H
#define EXACTINFOLIST_H

#include "../../sigmod/include/core.h"
class exactInfoNode {
private:
  ExactInfo info;
  exactInfoNode *next;

public:
  exactInfoNode(ExactInfo info);
  ~exactInfoNode();
  //  Getters
  int getId() const { return this->info.query_id; };
  unsigned int getMaxQueryWords() const { return this->info.maxQueryWords; };
  ExactInfo getWordInfo() const { return this->info; };
  exactInfoNode *getNext() const { return this->next; };
  // Setters
  void setId(int id) { this->info.query_id = id; };
  void setMaxQueryWords(int max) { this->info.maxQueryWords = max; };
  void setWordInfo(ExactInfo wi) { this->info = wi; };
  void setNext(exactInfoNode *next) { this->next = next; };
  void print();
};

class exactInfoList {
private:
  exactInfoNode *head;
  exactInfoNode *last;
  int count;

public:
  exactInfoList();
  ~exactInfoList();
  // Getters
  exactInfoNode *getHead() const { return this->head; };
  exactInfoNode *getLast() const { return this->last; };
  int getCount() const { return this->count; };
  // Setters
  void setHead(exactInfoNode *head) { this->head = head; };
  void setLast(exactInfoNode *last) { this->last = last; };
  void setCount(int count) { this->count = count; };
  // Methods
  void addQuery(ExactInfo wordInfo);
  void print();
};

#endif