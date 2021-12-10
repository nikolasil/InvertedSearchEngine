#include "MatchArray.h"
#include <cstring>
#include <iostream>

using namespace std;

MatchArray::MatchArray(int size) {
  this->array = new tree *[size](); // initialize MatchArray to null
  this->size = size;
}

MatchArray::~MatchArray() {
  for (int i = 0; i < this->size; i++) {
    delete this->array[i];
  }
  delete[] this->array;
}

int MatchArray::getSize() {
  return this->size;
}

void MatchArray::insert(String queryWord, int queryId, int maxQueryWords) {
  tree *matchTree = this->array[queryId];

  if (matchTree == NULL) {
    matchTree = new tree(queryId, maxQueryWords); // create and initialize matchTree
  }

  matchTree->insert(queryWord); // insert query word to matchTree
}

void MatchArray::deleteMatchTree(int queryId) {
  // hard delete
  delete this->array[queryId];

  // soft delete
  //   this->array[queryId]->setDeleted(true);
}
