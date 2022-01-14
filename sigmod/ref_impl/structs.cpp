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
  pthread_mutex_init(&(this->mutex0), NULL);
  pthread_mutex_init(&(this->mutex1), NULL);
  pthread_mutex_init(&(this->mutex2), NULL);
  pthread_mutex_init(&(this->mutex3), NULL);
  pthread_mutex_init(&(this->mutex4), NULL);
  pthread_mutex_init(&(this->mutex5), NULL);
  pthread_mutex_init(&(this->mutex6), NULL);
  pthread_mutex_init(&(this->mutex7), NULL);
  pthread_mutex_init(&(this->mutex8), NULL);
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
  this->maxQueryId = max;
};

void DataStructs::setLastServedDocId(int docid) {
  this->lastServedDocId = docid;
};