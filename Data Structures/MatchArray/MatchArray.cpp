#include "MatchArray.h"
#include "MatchTree.h"
#include <cstring>
#include <iostream>

using namespace std;

MatchArray::MatchArray(int size) {
  this->array = new MatchTree *[size](); // initialize MatchArray to null
  this->size = size;
  this->matchedIds = new ResultList();
}

MatchArray::~MatchArray() {
  for (int i = 0; i < this->size; i++) {
    delete this->array[i];
  }
  delete[] this->array;
}

void MatchArray::insert(String *queryWord, int queryId, int maxQueryWords) {
  MatchTree *matchTree = this->array[queryId];

  if (matchTree == NULL) {
    this->array[queryId] = new MatchTree(maxQueryWords); // create and initialize matchTree
    matchTree = this->array[queryId];
  }
  matchTree->insert(queryWord); // insert query word to matchTree

  // check if the query word is matched
  if (matchTree->matched()) {
    this->matchedIds->add(queryId);
  }
}

void MatchArray::deleteMatchTree(int queryId) {
  // hard delete
  delete this->array[queryId];

  // soft delete
  //   this->array[queryId]->setDeleted(true);
}
