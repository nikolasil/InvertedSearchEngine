
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
}

void hammingArray::insert(String *word, HEInfo info) {

  if (this->array[strlen(word->getStr()) - 4] == nullptr) {
    this->array[strlen(word->getStr()) - 4] = new BK_Tree();
  }
  this->array[strlen(word->getStr()) - 4]->add(word, info);
}

void hammingArray::print() {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    if (this->array[i] != nullptr) {
      this->array[i]->print();
    }
  }
}