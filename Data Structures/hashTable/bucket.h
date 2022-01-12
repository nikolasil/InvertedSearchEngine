#ifndef Bucket_H
#define Bucket_H

#include "../../sigmod/include/core.h"
#include "../queryList/exactInfoList.h"
#include "../string/String.h"
#include <pthread.h>

class bucketNode {
private:
  String *word;
  exactInfoList *list;
  bucketNode *next;
  pthread_mutex_t mutex;

public:
  bucketNode(String *word, ExactInfo *wordInfo);
  ~bucketNode();
  // Getters
  String *getWord() const { return this->word; };
  exactInfoList *getList() const { return this->list; };
  bucketNode *getNext() const { return this->next; };
  // Setters
  void setWord(String *word) {
    pthread_mutex_lock(&(this->mutex));
    this->word = word;
    pthread_mutex_unlock(&(this->mutex));
  };
  void setList(exactInfoList *list) {
    pthread_mutex_lock(&(this->mutex));
    this->list = list;
    pthread_mutex_unlock(&(this->mutex));
  };
  void setNext(bucketNode *next) {
    pthread_mutex_lock(&(this->mutex));
    this->next = next;
    pthread_mutex_unlock(&(this->mutex));
  };
  // Methods
  void addToQueryList(ExactInfo *wordInfo);
  void print();
};

class Bucket {
private:
  bucketNode *head;
  bucketNode *last;
  int count;
  pthread_mutex_t mutex;

public:
  Bucket();
  ~Bucket();
  // Getters
  bucketNode *getHead() const { return this->head; };
  bucketNode *getLast() const { return this->last; };
  int getCount() const { return this->count; };
  // Setters
  void setHead(bucketNode *head) { this->head = head; };
  void setLast(bucketNode *last) { this->last = last; };
  void setCount(int count) { this->count = count; };
  // Methods
  exactInfoList *lookup(String *word, String **matchedWord);
  bucketNode *addNode(String *word, ExactInfo *wordInfo);
  bucketNode *getNode(String *word);
  void print();
};

#endif