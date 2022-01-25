#include "heQueryHashTable.h"
#include <cstring>
#include <iostream>

using namespace std;

// HashTable
HEQueryHashTable::HEQueryHashTable(int size) {
  this->size = size;
  this->table = new HEQueryBucket *[size]();
  for (int i = 0; i < size; i++) {
    this->table[i] = new HEQueryBucket();
  }
}

HEQueryHashTable::~HEQueryHashTable() {
  for (int i = 0; i < size; i++) {
    delete this->table[i];
  }
  delete[] this->table;
}

void HEQueryHashTable::insert(HEInfo *HEInfo) {
  this->table[((HEInfo->query_id) % (TABLE_SIZE - 1))]->addNode(HEInfo);
}

void HEQueryHashTable::setFlagFalse(unsigned int query) {
  HEQueryBucketNode *node = this->table[(query % (TABLE_SIZE - 1))]->getNode(query);
  if (node != NULL) {
    node->getInfo()->flag = false;
  }
}

void HEQueryHashTable::print() {
  for (int i = 0; i < size; i++) {
    this->table[i]->print();
  }
}

// HEQueryBucket
HEQueryBucket::HEQueryBucket() {
  this->head = NULL;
  this->last = NULL;
  this->count = 0;
  pthread_mutex_init(&this->mutex, NULL);
}
HEQueryBucket::~HEQueryBucket() {
  pthread_mutex_destroy(&this->mutex);
}
void HEQueryBucket::addNode(HEInfo *queryInfo) {
  pthread_mutex_lock(&this->mutex);
  HEQueryBucketNode *newNode = new HEQueryBucketNode(queryInfo);
  if (this->head == NULL) {
    this->head = newNode;
    this->last = newNode;
  } else {
    this->last->setNext(newNode);
    this->last = newNode;
  }
  pthread_mutex_unlock(&this->mutex);
}

HEQueryBucketNode *HEQueryBucket::getNode(unsigned int query) {
  HEQueryBucketNode *current = this->head;
  while (current != NULL) {
    if (current->getInfo()->query_id == query) {
      return current;
    }
    current = current->getNext();
  }
  return NULL;
}

void HEQueryBucket::print() {
  HEQueryBucketNode *current = this->head;
  while (current != NULL) {
    current->print();
    current = current->getNext();
  }
}
// HEQueryBucketNode
HEQueryBucketNode::HEQueryBucketNode(HEInfo *queryInfo) {
  this->info = queryInfo;
  this->next = NULL;
}
HEQueryBucketNode::~HEQueryBucketNode() {
  delete this->info;
}
void HEQueryBucketNode::print() {
  cout << "Query: " << this->info->query_id << " Flag: " << this->info->flag << endl;
}