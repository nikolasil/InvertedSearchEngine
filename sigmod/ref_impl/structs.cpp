#include "../include/structs.h"
#include <pthread.h>
DataStructs::DataStructs() {
  this->ht = new HashTable();
  this->hamming = new hammingArray();
  this->edit = new BK_Tree();
  this->ExactQueryHT = new ExactQueryHashTable();
  this->HEQueryHT = new HEQueryHashTable();
  this->docs = new DocumentList();
  this->maxQueryId = 0;
  this->lastServedDocId = 0;
  this->exactStructsList = new exactInfoList();
  this->heStructsList = new heInfoList();
  pthread_mutex_init(&(this->mutex0), NULL);
}

DataStructs::~DataStructs() {
  delete ht;
  delete hamming;
  delete edit;

  delete ExactQueryHT;
  delete HEQueryHT;

  exactStructsList->destroy();
  heStructsList->destroy();
  // docs->destroy();
  delete exactStructsList;
  delete heStructsList;
  delete docs;
}

void DataStructs::setMaxQueryId(int max) {
  this->maxQueryId = max;
};

void DataStructs::setLastServedDocId(int docid) {
  this->lastServedDocId = docid;
};