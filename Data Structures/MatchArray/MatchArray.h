#ifndef MATCH_ARRAY_H
#define MATCH_ARRAY_H

#include "../../sigmod/include/core.h"
#include "../queryList/heInfoList.h"
#include "../string/String.h"
#include "MatchTree.h"
#include "ResultList.h"
#include <pthread.h>

class MatchArray {
private:
  MatchTree **array;
  int size;
  ResultList *matchedIds;

public:
  MatchArray(int size);
  ~MatchArray();
  // Getters
  MatchTree *getMatchTree(int index) { return this->array[index]; };
  int getSize() { return this->size; };
  ResultList *getMatchedIds() { return this->matchedIds; };
  // Setters
  void setMatchTree(int index, MatchTree *matchTree) { this->array[index] = matchTree; };
  void setSize(int size) { this->size = size; };
  void setMatchedIds(ResultList *matchedIds) { this->matchedIds = matchedIds; };
  // Methods
  void insert(String *queryWord, int queryId, int maxQueryWords);
  void insertNoLock(String *queryWord, int queryId, int maxQueryWords);
  void update(String *word, heInfoList *list, int threshold, ResultList *forDeletion);
  void deleteMatchTree(int queryId);
  void print(int queryId);
  void print();
};

#endif