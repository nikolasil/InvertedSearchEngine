
#include "hammingArray.h"
#include "../string/String.h"
#include <cstring>
#include <iostream>
using namespace std;
// hammingArray
hammingArray::hammingArray() {
  this->array = new BK_Tree *[ARRAY_SIZE];
}

void hammingArray::insert(String *word, HEInfo info) {
  this->array[strlen(word->getStr()) - 4]->add(word, info);
}