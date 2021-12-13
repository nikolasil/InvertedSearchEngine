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
  if (this->array[queryId] == NULL) {
    this->array[queryId] = new MatchTree(maxQueryWords); // create and initialize matchTree
  }
  this->array[queryId]->insert(queryWord); // insert query word to matchTree
  cout << "Query word: " << queryWord->getStr() << " inserted to matchTree " << queryId << endl;
  // check if the query word is matched
  if (this->array[queryId]->matched()) {
    this->matchedIds->add(queryId);
  }
}

void MatchArray::deleteMatchTree(int queryId) {
  // hard delete
  delete this->array[queryId];

  // soft delete
  //   this->array[queryId]->setDeleted(true);
}

void MatchArray::print(int queryId) {
  this->array[queryId]->print();
}