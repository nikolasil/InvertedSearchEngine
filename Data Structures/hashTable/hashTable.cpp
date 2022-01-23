#include "hashTable.h"
#include <cstring>
#include <iostream>

using namespace std;

// HashTable

HashTable::HashTable(int size) {
  this->table = new Bucket *[size]();
  this->size = size;
  for (int i = 0; i < size; i++) {
    this->table[i] = new Bucket();
  }
  pthread_mutex_init(&this->mutex, NULL);
}

HashTable::~HashTable() {
  for (int i = 0; i < this->size; i++) {
    if (this->table[i] != nullptr) {
      delete this->table[i];
      this->table[i] = nullptr;
    }
  }
  delete[] this->table;
  this->table = nullptr;
}

// unsigned HashTable::hash_string(char *s) {
//   unsigned h = FIRSTH;
//   while (*s) {
//     h = (h * A) ^ (s[0] * B);
//     s++;
//   }
//   return h; // or return h % C;
// }

uint32_t HashTable::hash_string(char *s) {
  uint32_t hash = 0;

  for (; *s; ++s) {
    hash += *s;
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);

  return hash;
}

void HashTable::insert(String *word, ExactInfo *wordInfo) {
  // Insert Word into Bucket
  // cout << "Inserting " << word->getStr() << " into Bucket " << index << endl;
  this->table[(hash_string(word->getStr()) % (TABLE_SIZE - 1)) + 1]->addNode(word, wordInfo);
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

void HashTable::lookup(String *H, MatchArray *MatchArray, ResultList *forDelition) {
  // cout << "Looking up " << H->getStr() << " in Bucket " << index << endl;
  this->table[(hash_string(H->getStr()) % (TABLE_SIZE - 1)) + 1]->lookup(H, MatchArray, forDelition);
}