#ifndef EXACTINFOLIST_H
#define EXACTINFOLIST_H

#include "../../sigmod/include/core.h"
#include <pthread.h>
class exactInfoNode {
private:
  ExactInfo *info;
  exactInfoNode *next;

public:
  exactInfoNode(ExactInfo *info);
  ~exactInfoNode();
  void destroy();
  //  Getters
  int getId() const { return this->info->query_id; };
  unsigned int getMaxQueryWords() const { return this->info->maxQueryWords; };
  bool getFlag() const { return this->info->flag; };
  ExactInfo *getWordInfo() const { return this->info; };
  exactInfoNode *getNext() const { return this->next; };
  // Setters
  void setId(int id) {
    this->info->query_id = id;
  };
  void setMaxQueryWords(int max) {
    this->info->maxQueryWords = max;
  };
  void setWordInfo(ExactInfo *wi) {
    this->info = wi;
  };
  void setFlag(bool flag) {
    this->info->flag = flag;
  };
  void setNext(exactInfoNode *next) {
    this->next = next;
  };
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
  void destroy();
  // Getters
  exactInfoNode *getHead() const { return this->head; };
  exactInfoNode *getLast() const { return this->last; };
  int getCount() const { return this->count; };
  // Setters
  void setHead(exactInfoNode *head) { this->head = head; };
  void setLast(exactInfoNode *last) { this->last = last; };
  void setCount(int count) { this->count = count; };
  // Methods
  void addQuery(ExactInfo *wordInfo);
  void print();
};

#endif