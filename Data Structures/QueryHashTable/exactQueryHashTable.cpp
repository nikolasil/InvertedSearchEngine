#include "exactQueryHashTable.h"
#include <cstring>
#include <iostream>
#include <pthread.h>

using namespace std;

// HashTable
ExactQueryHashTable::ExactQueryHashTable(int size) {
  this->size = size;

  this->table = new ExactQueryBucket *[size]();
  for (int i = 0; i < size; i++) {
    this->table[i] = new ExactQueryBucket();
  }
}

ExactQueryHashTable::~ExactQueryHashTable() {
  for (int i = 0; i < size; i++) {
    delete this->table[i];
  }
  delete[] this->table;
}

void ExactQueryHashTable::insert(ExactInfo *exactInfo) {
  this->table[((exactInfo->query_id) % (TABLE_SIZE - 1))]->addNode(exactInfo);
}

void ExactQueryHashTable::setFlagFalse(unsigned int query) {
  ExactQueryBucketNode *node = this->table[(query % (TABLE_SIZE - 1))]->getNode(query);
  if (node != NULL) {
    node->getInfo()->flag = false;
  }
}

void ExactQueryHashTable::print() {
  for (int i = 0; i < size; i++) {
    this->table[i]->print();
  }
}

// ExactQueryBucket
ExactQueryBucket::ExactQueryBucket() {
  this->head = NULL;
  this->last = NULL;
  this->count = 0;
  pthread_mutex_init(&this->mutex, NULL);
}
ExactQueryBucket::~ExactQueryBucket() {
  pthread_mutex_destroy(&this->mutex);
}
void ExactQueryBucket::addNode(ExactInfo *queryInfo) {
  pthread_mutex_lock(&this->mutex);
  ExactQueryBucketNode *newNode = new ExactQueryBucketNode(queryInfo);
  if (this->head == NULL) {
    this->head = newNode;
    this->last = newNode;
  } else {
    this->last->setNext(newNode);
    this->last = newNode;
  }
  pthread_mutex_unlock(&this->mutex);
}

ExactQueryBucketNode *ExactQueryBucket::getNode(unsigned int query) {
  ExactQueryBucketNode *current = this->head;
  while (current != NULL) {
    if (current->getInfo()->query_id == query) {
      return current;
    }
    current = current->getNext();
  }
  return NULL;
}

void ExactQueryBucket::print() {
  ExactQueryBucketNode *current = this->head;
  while (current != NULL) {
    current->print();
    current = current->getNext();
  }
}
// ExactQueryBucketNode
ExactQueryBucketNode::ExactQueryBucketNode(ExactInfo *queryInfo) {
  this->info = queryInfo;
  this->next = NULL;
}
ExactQueryBucketNode::~ExactQueryBucketNode() {
  delete this->info;
}
void ExactQueryBucketNode::print() {
  cout << "Query: " << this->info->query_id << " Flag: " << this->info->flag << endl;
}