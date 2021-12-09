#ifndef hammingArray_H
#define hammingArray_H

#include "../string/String.h"
#include "tree.h"

#define ARRAY_SIZE 28

class hammingArray {
private:
  tree **array;

public:
  hammingArray();
  ~hammingArray();
  // Getters
  tree *getTree(int index) { return array[index]; };
  // Setters
  void setTree(int index, tree *t) { array[index] = t; };
  // Methods
  void insert(String *word);
};

#endif