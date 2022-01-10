#include "../include/structs.h"

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