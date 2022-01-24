#ifndef HEQueryHashTable_H
#define HEQueryHashTable_H
#include "../../sigmod/include/core.h"
#include "../MatchArray/MatchArray.h"
#include "../MatchArray/ResultList.h"
#include "../string/String.h"

#include <pthread.h>

#define TABLE_SIZE 500000

class HEQueryBucketNode {
private:
  HEInfo *info;
  HEQueryBucketNode *next;

public:
  HEQueryBucketNode(HEInfo *queryInfo);
  ~HEQueryBucketNode();
  // Getters
  HEInfo *getInfo() { return info; };
  HEQueryBucketNode *getNext() { return next; };
  // Setters
  void setInfo(HEInfo *queryInfo) { info = queryInfo; };
  void setNext(HEQueryBucketNode *nextNode) { next = nextNode; };
  // Methods
  void print();
};

class HEQueryBucket {
private:
  HEQueryBucketNode *head;
  HEQueryBucketNode *last;
  int count;
  pthread_mutex_t mutex;

public:
  HEQueryBucket();
  ~HEQueryBucket();
  // Getters
  HEQueryBucketNode *getHead() const { return this->head; };
  HEQueryBucketNode *getLast() const { return this->last; };
  int getCount() const { return this->count; };
  // Setters
  void setHead(HEQueryBucketNode *head) { this->head = head; };
  void setLast(HEQueryBucketNode *last) { this->last = last; };
  void setCount(int count) { this->count = count; };
  // Methods
  HEQueryBucketNode *addNode(HEInfo *queryInfo);
  HEQueryBucketNode *getNode(unsigned int query);
  void print();
};

class HEQueryHashTable {
private:
  HEQueryBucket **table;
  int size;
  // pthread_mutex_t mutex;

public:
  HEQueryHashTable(int size = TABLE_SIZE);
  ~HEQueryHashTable();
  // Getters
  int getSize() const { return this->size; };
  HEQueryBucket **getTable() const { return this->table; };
  // Setters
  void setSize(int size) { this->size = size; };
  void setTable(HEQueryBucket **table) { this->table = table; };
  // Methods
  HEQueryBucket *getHEQueryBucket(int i) { return this->table[i]; };
  void setHEQueryBucket(HEQueryBucket *b, int i) { this->table[i] = b; };

  void insert(HEInfo *HEInfo);
  void setFlagFalse(unsigned int query);
  void print();
};

#endif