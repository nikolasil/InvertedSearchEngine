#ifndef Bucket_H
#define Bucket_H

#include "../string/String.h"

class bucketNode {
private:
  String *word;
  bucketNode *next;

public:
  bucketNode(String *word);
  ~bucketNode();
  String *getWord();
  void setNext(bucketNode *next);
  bucketNode *getNext();
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
  bucketNode *addNode(String *word);
  bucketNode *getNode(String *word);
  bucketNode *getHead() const { return this->head; };
  void print();
};

#endif