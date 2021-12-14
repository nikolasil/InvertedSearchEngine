#ifndef hammingArray_H
#define hammingArray_H

#include "../../sigmod/include/core.h"
#include "../string/String.h"
#include "BK_Tree.h"

#define ARRAY_SIZE 28

class hammingArray {
private:
  BK_Tree **array;

public:
  hammingArray();
  ~hammingArray();
  // Getters
  BK_Tree *getTree(int index) { return array[index]; };
  // Setters
  void setTree(int index, BK_Tree *t) { array[index] = t; };
  // Methods
  void insert(String *word, HEInfo info);
  void lookup(String *word, MatchArray *matchArray);
  void print();
};

#endif