#ifndef STRUCTS_H
#define STRUCTS_H

class HashTable;
class hammingArray;
class BK_Tree;
class ResultList;
class DocumentList;
class exactInfoList;
class heInfoList;
class Bucket;
class MatchArray;

#include "../../Data Structures/DocumentList/DocumentList.h"
#include "../../Data Structures/MatchArray/MatchArray.h"
#include "../../Data Structures/hashTable/bucket.h"
#include "../../Data Structures/hashTable/hashTable.h"
#include "../../Data Structures/string/String.h"
#include "../../Data Structures/tree/BK_Tree.h"
#include "../../Data Structures/tree/hammingArray.h"
#include <pthread.h>
class DataStructs {
private:
  HashTable *ht;
  hammingArray *hamming;
  BK_Tree *edit;
  ResultList *forDeletion;
  DocumentList *docs;
  unsigned int maxQueryId;
  int lastServedDocId;
  exactInfoList *exactStructsList;
  heInfoList *heStructsList;

  pthread_mutex_t mutex;

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
  int getLastServedDocId() { return this->lastServedDocId; };
  exactInfoList *getExactStructsList() { return this->exactStructsList; };
  heInfoList *getHeStructsList() { return this->heStructsList; };

  // Setters
  void setMaxQueryId(int max);
  void setLastServedDocId(int docid);
};

#endif