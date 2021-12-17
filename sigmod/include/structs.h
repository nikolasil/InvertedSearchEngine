#ifndef STRUCTS_H
#define STRUCTS_H

#include "../../Data Structures/DocumentList/DocumentList.h"
#include "../../Data Structures/MatchArray/MatchArray.h"
#include "../../Data Structures/hashTable/bucket.h"
#include "../../Data Structures/hashTable/hashTable.h"
#include "../../Data Structures/string/String.h"
#include "../../Data Structures/tree/BK_Tree.h"
#include "../../Data Structures/tree/hammingArray.h"

class DataStructs {
private:
  HashTable *ht;
  hammingArray *hamming;
  BK_Tree *edit;
  ResultList *forDeletion;
  DocumentList *docs;
  unsigned int maxQueryId;
  exactInfoList *exactStructsList;
  heInfoList *heStructsList;

public:
  DataStructs();
  ~DataStructs();
  // Getters
  HashTable *getHashTable() { return this->ht; };
  hammingArray *getHamming() { return this->hamming; };
  BK_Tree *getEdit() { return this->edit; };
  ResultList *getForDeletion() { return this->forDeletion; };
  DocumentList *getDocs() { return this->docs; };
  unsigned int getMaxQueryId() { return this->maxQueryId; };
  exactInfoList *getExactStructsList() { return this->exactStructsList; };
  heInfoList *getHeStructsList() { return this->heStructsList; };

  // Setters
  void setMaxQueryId(int max) { this->maxQueryId = max; };
};

#endif