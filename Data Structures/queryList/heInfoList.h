#ifndef HEINFOLIST_H
#define HEINFOLIST_H

#include "../../sigmod/include/core.h"
#include <pthread.h>
class heInfoNode {
private:
  HEInfo *info;
  heInfoNode *next;

public:
  heInfoNode(HEInfo *info);
  ~heInfoNode();
  void destroy();
  //  Getters
  int getId() const { return this->info->query_id; };
  unsigned int getMaxQueryWords() const { return this->info->maxQueryWords; };
  HEInfo *getWordInfo() const { return this->info; };
  heInfoNode *getNext() const { return this->next; };
  bool getFlag() const { return this->info->flag; };
  unsigned int getMatchDist() const { return this->info->matchDist; };
  // Setters
  void setId(int id) { this->info->query_id = id; };
  void setMaxQueryWords(int max) { this->info->maxQueryWords = max; };
  void setWordInfo(HEInfo *wi) { this->info = wi; };
  void setNext(heInfoNode *n) { this->next = n; };
  void setFlag(bool flag) { this->info->flag = flag; };
  void setMatchDist(unsigned int dist) { this->info->matchDist = dist; };
  void print();
};

class heInfoList {
private:
  heInfoNode *head;
  heInfoNode *last;
  int count;
  pthread_mutex_t mutex;

public:
  heInfoList();
  ~heInfoList();
  void destroy();
  // Getters
  heInfoNode *getHead() const { return this->head; };
  heInfoNode *getLast() const { return this->last; };
  int getCount() const { return this->count; };
  // Setters
  void setHead(heInfoNode *head) { this->head = head; };
  void setLast(heInfoNode *last) { this->last = last; };
  void setCount(int count) { this->count = count; };
  // Methods
  void addQuery(HEInfo *wordInfo);
  void print();
};

#endif