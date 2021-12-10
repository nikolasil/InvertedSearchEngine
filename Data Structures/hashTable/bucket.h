#ifndef Bucket_H
#define Bucket_H

#include "../string/String.h"
#include "queryList.h"

class bucketNode {
private:
  String *word;
  queryList *list;
  bucketNode *next;

public:
  bucketNode(String *word, int qId);
  ~bucketNode();
  // Getters
  String *getWord() const { return this->word; };
  queryList *getList() const { return this->list; };
  bucketNode *getNext() const { return this->next; };
  // Setters
  void setWord(String *word) { this->word = word; };
  void setList(queryList *list) { this->list = list; };
  void setNext(bucketNode *next) { this->next = next; };
  // Methods
  void addToQueryList(int qId);
  void print();
};

class Bucket {
private:
  bucketNode *head;
  bucketNode *last;
  int count;

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
  bucketNode *addNode(String *word, int qId);
  bucketNode *getNode(String *word);
  void print();
};

#endif