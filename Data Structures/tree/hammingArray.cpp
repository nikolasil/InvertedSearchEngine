
#include "hammingArray.h"
#include "../string/String.h"
#include <cstring>
#include <iostream>
using namespace std;
// hammingArray
hammingArray::hammingArray() {
  this->array = new tree *[ARRAY_SIZE];
}

void hammingArray::insert(String *word) {
  this->array[strlen(word->getStr()) - 4]->add(word);
}