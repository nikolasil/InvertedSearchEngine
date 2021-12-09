#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "../string/String.h"
#include "bucket.h"
#include <openssl/sha.h>
#define TABLE_SIZE 50

class HashTable {
private:
  Bucket **table;
  int size;

public:
  HashTable(int size = TABLE_SIZE);
  ~HashTable();
  void print();
  void insert(String *word);
  void generateHashString(char key[256], char *returnHash);
  int getIndex(char *H);
  int hexadecimalToDecimal(char hexVal[]);
};

#endif