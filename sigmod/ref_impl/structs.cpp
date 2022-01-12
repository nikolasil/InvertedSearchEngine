#include "../include/structs.h"
#include <pthread.h>
DataStructs::DataStructs() {
  this->ht = new HashTable();
  this->hamming = new hammingArray();
  this->edit = new BK_Tree();
  this->forDeletion = new ResultList();
  this->docs = new DocumentList();
  this->maxQueryId = 0;
  this->lastServedDocId = 0;
  this->exactStructsList = new exactInfoList();
  this->heStructsList = new heInfoList();

  pthread_mutex_init(&(this->mutex), NULL);
}

DataStructs::~DataStructs() {
  delete ht;
  delete hamming;
  delete edit;

  exactStructsList->destroy();
  heStructsList->destroy();
  forDeletion->destroy();
  // docs->destroy();
  delete exactStructsList;
  delete heStructsList;
  delete forDeletion;
  delete docs;
}

void DataStructs::setMaxQueryId(int max) {
  pthread_mutex_lock(&(this->mutex));
  this->maxQueryId = max;
  pthread_mutex_unlock(&(this->mutex));
};

void DataStructs::setLastServedDocId(int docid) {
  pthread_mutex_lock(&(this->mutex));
  this->lastServedDocId = docid;
  pthread_mutex_unlock(&(this->mutex));
};