
#include "hammingArray.h"
#include "../string/String.h"
#include "BK_Tree.h"
#include <cstring>
#include <iostream>
using namespace std;
// hammingArray
hammingArray::hammingArray() {
  this->array = new BK_Tree *[ARRAY_SIZE];
}

hammingArray::~hammingArray() {
}

void hammingArray::insert(String *word, HEInfo info) {
  BK_Tree *tree = this->array[strlen(word->getStr()) - 4];
  if (tree == nullptr) {
    tree = new BK_Tree();
  }
  tree->add(word, info);
}