#ifndef EXACTINFOLIST_H
#define EXACTINFOLIST_H

#include "../../sigmod/include/core.h"
#include <pthread.h>
class exactInfoNode {
private:
  ExactInfo *info;
  exactInfoNode *next;
  pthread_mutex_t mutex;

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
    pthread_mutex_lock(&(this->mutex));
    this->info->query_id = id;
    pthread_mutex_unlock(&(this->mutex));
  };
  void setMaxQueryWords(int max) {
    pthread_mutex_lock(&(this->mutex));
    this->info->maxQueryWords = max;
    pthread_mutex_unlock(&(this->mutex));
  };
  void setWordInfo(ExactInfo *wi) {
    pthread_mutex_lock(&(this->mutex));
    this->info = wi;
    pthread_mutex_unlock(&(this->mutex));
  };
  void setFlag(bool flag) {
    pthread_mutex_lock(&(this->mutex));
    this->info->flag = flag;
    pthread_mutex_unlock(&(this->mutex));
  };
  void setNext(exactInfoNode *next) {
    pthread_mutex_lock(&(this->mutex));
    this->next = next;
    pthread_mutex_unlock(&(this->mutex));
  };
  void print();
};

class exactInfoList {
private:
  exactInfoNode *head;
  exactInfoNode *last;
  int count;
  pthread_mutex_t mutex;

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