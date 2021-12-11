#ifndef MATCH_ARRAY_H
#define MATCH_ARRAY_H

#include "../../sigmod/include/core.h"
#include "../string/String.h"
#include "MatchTree.h"

class MatchArray {
private:
  MatchTree **array;
  int size;

public:
  MatchArray(int size);
  ~MatchArray();
  int getSize();
  void insert(String *queryWord, int queryId, int maxQueryWords);
  void deleteMatchTree(int queryId);
};

#endif