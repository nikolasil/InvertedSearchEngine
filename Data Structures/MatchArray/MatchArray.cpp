#include "MatchArray.h"
#include "MatchTree.h"
#include <cstring>
#include <iostream>

using namespace std;

MatchArray::MatchArray(int size) {
  this->array = new MatchTree *[size + 1](); // initialize MatchArray to null
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
    // cout << "null" << endl;
    this->array[queryId] = new MatchTree(maxQueryWords); // create and initialize matchTree
  }
  this->array[queryId]->insert(queryWord); // insert query word to matchTree
  // cout << "Query word: " << queryWord->getStr() << " inserted to matchTree " << queryId << endl;
  // check if the query word is matched
  if (this->array[queryId]->matched()) {
    this->matchedIds->add(queryId);
  }
}
void MatchArray::update(String *word, heInfoList *infoList, int threshold) {
  heInfoNode *curr = infoList->getHead();
  // infoList->print();
  while (curr != nullptr) {
    // cout << threshold << " " << curr->getWordInfo().matchDist << " " << curr->getId() << endl;
    if (curr->getWordInfo().matchDist >= (unsigned int)threshold) {
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
  if (this->array[queryId] != NULL) {
    this->array[queryId]->print();
  }
}
void MatchArray::print() {
  for (int i = 0; i <= this->size; i++) {
    if (this->array[i] != NULL) {
      cout << "MatchTree " << i << endl;
      this->array[i]->print();
    }
  }
  cout << "Result" << endl;
  this->matchedIds->print();
}