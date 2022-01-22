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
    if (this->array[i] != nullptr) {
      delete this->array[i];
      this->array[i] = nullptr;
    }
  }
  delete[] this->array;
  this->array = nullptr;

  this->matchedIds->destroy();
  delete this->matchedIds;
  // this->matchedIds;
}

void MatchArray::insert(String *queryWord, int queryId, int maxQueryWords) {
  if (this->array[queryId - 1] == NULL) {
    // cout << "null" << endl;
    this->array[queryId - 1] = new MatchTree(maxQueryWords); // create and initialize matchTree
  }
  this->array[queryId - 1]->insert(queryWord); // insert query word to matchTree
  // cout << "Query word: " << queryWord->getStr() << " inserted to matchTree " << queryId << endl;
  // check if the query word is matched
  if (this->array[queryId - 1]->matched()) {
    this->matchedIds->add(queryId);
  }
}

void MatchArray::update(String *word, heInfoList *infoList, int threshold, ResultList *forDeletion) {
  heInfoNode *curr = infoList->getHead();

  while (curr != nullptr) {

    if (curr->getMatchDist() >= (unsigned int)threshold) {
      if (forDeletion->searchRemove(curr->getId())) {
        curr->setFlag(false);
      } else if (curr->getFlag())
        this->insert(word, curr->getId(), curr->getMaxQueryWords());
    }
    curr = curr->getNext();
  }
}

void MatchArray::deleteMatchTree(int queryId) {
  // hard delete
  delete this->array[queryId];

  // soft delete
  //   this->array[queryId]->setDeleted(true);
}

void MatchArray::print(int queryId) {
  if (this->array[queryId - 1] != NULL) {
    this->array[queryId - 1]->print();
  }
}
void MatchArray::print() {
  for (int i = 0; i < this->size; i++) {
    if (this->array[i] != NULL) {
      cout << "MatchTree " << i << endl;
      this->array[i]->print();
    }
  }
  cout << "Result" << endl;
  this->matchedIds->print();
}