#ifndef ExactQueryHashTable_H
#define ExactQueryHashTable_H
#include "../../sigmod/include/core.h"
#include "../MatchArray/MatchArray.h"
#include "../MatchArray/ResultList.h"
#include "../string/String.h"

#include <pthread.h>

#define TABLE_SIZE 500000

class ExactQueryBucketNode {
private:
  ExactInfo *info;
  ExactQueryBucketNode *next;

public:
  ExactQueryBucketNode(ExactInfo *queryInfo);
  ~ExactQueryBucketNode();
  // Getters
  ExactInfo *getInfo() { return info; };
  ExactQueryBucketNode *getNext() { return next; };
  // Setters
  void setInfo(ExactInfo *queryInfo) { info = queryInfo; };
  void setNext(ExactQueryBucketNode *nextNode) { next = nextNode; };
  // Methods
  void print();
};

class ExactQueryBucket {
private:
  ExactQueryBucketNode *head;
  ExactQueryBucketNode *last;
  int count;
  pthread_mutex_t mutex;

public:
  ExactQueryBucket();
  ~ExactQueryBucket();
  // Getters
  ExactQueryBucketNode *getHead() const { return this->head; };
  ExactQueryBucketNode *getLast() const { return this->last; };
  int getCount() const { return this->count; };
  // Setters
  void setHead(ExactQueryBucketNode *head) { this->head = head; };
  void setLast(ExactQueryBucketNode *last) { this->last = last; };
  void setCount(int count) { this->count = count; };
  // Methods
  ExactQueryBucketNode *addNode(ExactInfo *queryInfo);
  ExactQueryBucketNode *getNode(unsigned int query);
  void print();
};

class ExactQueryHashTable {
private:
  ExactQueryBucket **table;
  int size;
  // pthread_mutex_t mutex;

public:
  ExactQueryHashTable(int size = TABLE_SIZE);
  ~ExactQueryHashTable();
  // Getters
  int getSize() const { return this->size; };
  ExactQueryBucket **getTable() const { return this->table; };
  // Setters
  void setSize(int size) { this->size = size; };
  void setTable(ExactQueryBucket **table) { this->table = table; };
  // Methods
  ExactQueryBucket *getExactQueryBucket(int i) { return this->table[i]; };
  void setExactQueryBucket(ExactQueryBucket *b, int i) { this->table[i] = b; };

  void insert(ExactInfo *exactInfo);
  void setFlagFalse(unsigned int query);
  void print();
};

#endif