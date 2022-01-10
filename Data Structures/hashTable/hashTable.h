#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "../../sigmod/include/core.h"
#include "../string/String.h"
#include "bucket.h"
#include <openssl/sha.h>
#include <pthread.h>
#define TABLE_SIZE 10000

class HashTable {
private:
  Bucket **table;
  int size;
  pthread_mutex_t mutex;

public:
  HashTable(int size = TABLE_SIZE);
  ~HashTable();
  // Getters
  int getSize() const { return this->size; };
  Bucket **getTable() const { return this->table; };
  // Setters
  void setSize(int size) { this->size = size; };
  void setTable(Bucket **table) { this->table = table; };
  // Methods
  Bucket *getBucket(int i) { return this->table[i]; };
  void setBucket(Bucket *b, int i) { this->table[i] = b; };
  void insert(String *word, ExactInfo *wordInfo);
  int getIndex(unsigned char *H);
  exactInfoList *lookup(String *H, String **matchedWord);
  void print();
  // Hashing Related Methods
  int hexadecimalToDecimal(unsigned char hexVal[]);
};

#endif