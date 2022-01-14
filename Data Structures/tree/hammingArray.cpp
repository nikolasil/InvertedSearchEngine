
#include "hammingArray.h"
#include "../string/String.h"
#include "BK_Tree.h"
#include <cstring>
#include <iostream>
using namespace std;
// hammingArray
hammingArray::hammingArray() {
  this->array = new BK_Tree *[ARRAY_SIZE]();
}

hammingArray::~hammingArray() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (this->array[i] != nullptr) {
      delete this->array[i];
      this->array[i] = nullptr;
    }
  }
  delete[] this->array;
  this->array = nullptr;
}

void hammingArray::insert(String *word, HEInfo *info) {
  if (this->array[word->getSize() - 4] == nullptr) {
    this->array[word->getSize() - 4] = new BK_Tree();
  }
  this->array[word->getSize() - 4]->add(word, info);
}

void hammingArray::print() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (this->array[i] != nullptr) {
      this->array[i]->print();
    }
  }
}

void hammingArray::lookup(String *word, MatchArray *matchArray, ResultList *forDeletion) {
  BK_Tree *tree = this->array[word->getSize() - 4];
  if (tree)
    tree->hammingLookup(word, matchArray, forDeletion);
}