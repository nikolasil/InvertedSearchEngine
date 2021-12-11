#include "MatchArray.h"
#include "MatchTree.h"
#include <cstring>
#include <iostream>

using namespace std;

MatchArray::MatchArray(int size) {
  this->array = new MatchTree *[size](); // initialize MatchArray to null
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

void MatchArray::insert(String *queryWord, int queryId, int maxQueryWords) {
  MatchTree *matchTree = this->array[queryId];

  if (matchTree == NULL) {
    this->array[queryId] = new MatchTree(maxQueryWords); // create and initialize matchTree
    matchTree = this->array[queryId];
  }

  matchTree->insert(queryWord); // insert query word to matchTree
}

void MatchArray::deleteMatchTree(int queryId) {
  // hard delete
  delete this->array[queryId];

  // soft delete
  //   this->array[queryId]->setDeleted(true);
}
