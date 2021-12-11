#include "hashTable.h"
#include <cstring>
#include <iostream>
using namespace std;

// HashTable

HashTable::HashTable(int size) {
  this->table = new Bucket *[size];
  this->size = size;
}

HashTable::~HashTable() {
  for (int i = 0; i < this->size; i++) {
    if (this->table[i] != NULL) {
      delete this->table[i];
    }
  }
  delete[] this->table;
}

void HashTable::insert(String *word, WordInfo wordInfo) {
  // Hash word with SHA1
  char *returnHash = new char[SHA_DIGEST_LENGTH];
  generateHashString(word->getStr(), returnHash);

  // Get Bucket Index in Hash Table
  int index = getIndex(returnHash);

  // If Bucket is Empty, Create a new Bucket
  if (this->table[index] == NULL) {
    this->table[index] = new Bucket();
  }

  // Insert Word into Bucket
  // cout << "Inserting " << word->getStr() << " into Bucket " << index << endl;
  this->table[index]->addNode(word, wordInfo);
}

int HashTable::getIndex(char *hash) {
  return (hexadecimalToDecimal(hash) % (TABLE_SIZE - 1)) + 1;
}

void HashTable::print() {
  for (int i = 0; i < this->size; i++) {
    if (this->table[i] != NULL) {
      cout << "Bucket " << i << ": " << endl;
      this->table[i]->print();
      cout << "------------" << endl;
    }
  }
}

// Hashing Related Methods
void HashTable::generateHashString(char key[256], char *returnHash) {
  size_t length = strlen(key);
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1((const unsigned char *)key, length, hash);
  memcpy(returnHash, (char *)hash, SHA_DIGEST_LENGTH);
}

int HashTable::hexadecimalToDecimal(char hexVal[]) {
  int len = strlen(hexVal);

  int base = 1;

  int dec_val = 0;
  for (int i = len - 1; i >= 0; i--) {
    if (hexVal[i] >= '0' && hexVal[i] <= '9') {
      dec_val += (hexVal[i] - 48) * base;
      base = base * 16;
    } else if ((hexVal[i] >= 'A' && hexVal[i] <= 'F') || (hexVal[i] >= 'a' && hexVal[i] <= 'f')) {
      dec_val += (hexVal[i] - 55) * base;

      base = base * 16;
    }
  }
  return abs(dec_val);
}