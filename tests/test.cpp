#include "../Job Scheduler/Job.h"
#include "../Job Scheduler/Queue.h"
#include "../sigmod/include/core.h"
#include "../sigmod/include/structs.h"
#include "acutest.h"
#include <cstring>
#include <iostream>

using namespace std;

void htInsert() {
  HashTable *ht = new HashTable();
  ExactInfo *info1 = new ExactInfo();
  info1->query_id = 1;
  info1->flag = true;
  info1->maxQueryWords = 5;
  ExactInfo *info2 = new ExactInfo();
  info2->query_id = 2;
  info2->flag = true;
  info2->maxQueryWords = 5;
  ExactInfo *info3 = new ExactInfo();
  info3->query_id = 3;
  info3->flag = true;
  info3->maxQueryWords = 5;
  ExactInfo *info4 = new ExactInfo();
  info4->query_id = 4;
  info4->flag = true;
  info4->maxQueryWords = 5;
  ExactInfo *info5 = new ExactInfo();
  info5->query_id = 5;
  info5->flag = true;
  info5->maxQueryWords = 5;
  ht->insert(new String("Nikolas1"), info1);
  ht->insert(new String("Nikolas"), info2);
  ht->insert(new String("Michalis"), info3);
  ht->insert(new String("Nikolas"), info4);
  ht->insert(new String("Kostas"), info5);
  // ht->print();
  int size = ht->getSize();
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Michalis"))->getStr()) % (ht->getSize() - 1))->getHead()->getWord()->exactMatch(new String("Michalis")));
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Michalis"))->getStr()) % (ht->getSize() - 1))->getHead()->getList()->getHead()->getWordInfo() == info3);
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Kostas"))->getStr()) % (ht->getSize() - 1))->getHead()->getWord()->exactMatch(new String("Kostas")));
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Kostas"))->getStr()) % (ht->getSize() - 1))->getHead()->getList()->getHead()->getWordInfo() == info5);
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Nikolas"))->getStr()) % (ht->getSize() - 1))->getHead()->getWord()->exactMatch(new String("Nikolas")));
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Nikolas"))->getStr()) % (ht->getSize() - 1))->getHead()->getList()->getHead()->getWordInfo() == info2);
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Nikolas"))->getStr()) % (ht->getSize() - 1))->getHead()->getList()->getHead()->getNext()->getWordInfo() == info4);
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Nikolas1"))->getStr()) % (ht->getSize() - 1))->getHead()->getWord()->exactMatch(new String("Nikolas1")));
  TEST_ASSERT(ht->getBucket(ht->hash_string((new String("Nikolas1"))->getStr()) % (ht->getSize() - 1))->getHead()->getList()->getHead()->getWordInfo() == info1);
}

void htLookup() {
  HashTable *ht = new HashTable();
  ExactInfo *info1 = new ExactInfo();
  info1->query_id = 1;
  info1->flag = true;
  info1->maxQueryWords = 5;
  ExactInfo *info2 = new ExactInfo();
  info2->query_id = 2;
  info2->flag = true;
  info2->maxQueryWords = 1;
  ExactInfo *info3 = new ExactInfo();
  info3->query_id = 3;
  info3->flag = true;
  info3->maxQueryWords = 5;
  ExactInfo *info4 = new ExactInfo();
  info4->query_id = 4;
  info4->flag = true;
  info4->maxQueryWords = 2;
  ExactInfo *info5 = new ExactInfo();
  info5->query_id = 5;
  info5->flag = true;
  info5->maxQueryWords = 5;
  ht->insert(new String("Nikolas1"), info1);
  ht->insert(new String("Nikolas"), info2);
  ht->insert(new String("Michalis"), info3);
  ht->insert(new String("Nikolas"), info4);
  ht->insert(new String("Kostas"), info4);
  // ht->print();
  MatchArray *matchArray = new MatchArray(5);
  ht->lookup(new String("Nikolas"), matchArray);
  TEST_ASSERT(matchArray->getMatchedIds()->getHead()->getId() == 2);
  ht->lookup(new String("Kostas"), matchArray);
  TEST_ASSERT(matchArray->getMatchedIds()->getHead()->getNext()->getId() == 4);
}

void BKTreeInsert() {
  BK_Tree *tree = new BK_Tree();
  HEInfo *info1 = new HEInfo();
  info1->query_id = 1;
  info1->flag = true;
  info1->maxQueryWords = 2;
  info1->matchDist = 2;
  HEInfo *info2 = new HEInfo();
  info2->query_id = 2;
  info2->flag = true;
  info2->maxQueryWords = 2;
  info2->matchDist = 3;
  HEInfo *info3 = new HEInfo();
  info3->query_id = 3;
  info3->flag = true;
  info3->maxQueryWords = 2;
  info3->matchDist = 2;
  HEInfo *info4 = new HEInfo();
  info4->query_id = 4;
  info4->flag = true;
  info4->maxQueryWords = 2;
  info4->matchDist = 2;
  HEInfo *info5 = new HEInfo();
  info5->query_id = 5;
  info5->flag = true;
  info5->maxQueryWords = 2;
  info5->matchDist = 2;
  tree->add(new String("Nikolas"), info2);
  tree->add(new String("Michalis"), info1);
  tree->add(new String("Kostas"), info2);
  tree->add(new String("Nikolas"), info4);
  tree->add(new String("Kostas"), info5);
  // tree->print();
  TEST_ASSERT(tree->getRoot()->getData()->exactMatch(new String("Nikolas")));
  TEST_ASSERT(tree->getRoot()->findChild(5)->getData()->exactMatch(new String("Michalis")));
  TEST_ASSERT(tree->getRoot()->findChild(5)->findChild(6)->getData()->exactMatch(new String("Kostas")));
}
void BKTreeLookup() {
  BK_Tree *tree = new BK_Tree();
  HEInfo *info1 = new HEInfo();
  info1->query_id = 1;
  info1->flag = true;
  info1->maxQueryWords = 2;
  info1->matchDist = 2;
  HEInfo *info2 = new HEInfo();
  info2->query_id = 2;
  info2->flag = true;
  info2->maxQueryWords = 2;
  info2->matchDist = 3;
  HEInfo *info3 = new HEInfo();
  info3->query_id = 3;
  info3->flag = true;
  info3->maxQueryWords = 2;
  info3->matchDist = 2;
  HEInfo *info4 = new HEInfo();
  info4->query_id = 4;
  info4->flag = true;
  info4->maxQueryWords = 2;
  info4->matchDist = 2;
  HEInfo *info5 = new HEInfo();
  info5->query_id = 5;
  info5->flag = true;
  info5->maxQueryWords = 2;
  info5->matchDist = 2;
  tree->add(new String("Nikolas"), info2);
  tree->add(new String("Michalis"), info1);
  tree->add(new String("Kostas"), info2);
  tree->add(new String("Nikolas"), info4);
  tree->add(new String("Kostas"), info5);
  MatchArray *matchArray = new MatchArray(5);
  // matchArray->print();
  ResultList *forDel = new ResultList();
  tree->editLookup(new String("Kostas"), matchArray);
  tree->editLookup(new String("Nikolas"), matchArray);
  // tree->editLookup(new String("Kostas"), matchArray, forDel);
  // matchArray->print();
  TEST_ASSERT(matchArray->getMatchedIds()->getHead()->getId() == 2);
  delete matchArray;
  matchArray = new MatchArray(5);
  tree->hammingLookup(new String("Kostas"), matchArray);
  tree->hammingLookup(new String("Nikolas"), matchArray);
  TEST_ASSERT(matchArray->getMatchedIds()->getHead()->getId() == 2);
}
ErrorCode test_job_func(int numArgs, void **args) {
  return EC_SUCCESS;
}

void QueueFlow() {

  void **args0 = new void *[1];
  Job *job0 = new Job('t', &test_job_func, args0, 1);
  Job *job1 = new Job('o', &test_job_func, args0, 1);
  Queue *queue = new Queue();
  queue->add(job0);
  queue->add(job1);
  TEST_ASSERT(queue->getHead()->getJob() == job0);
  TEST_ASSERT(queue->getHead()->getNext()->getJob() == job1);
  TEST_ASSERT(queue->remove()->getJob() == job0);
  TEST_ASSERT(queue->remove()->getJob() == job1);
}

TEST_LIST = {
    {"Hash Table Insert", htInsert},
    {"Hash Table Lookup", htLookup},
    {"ΒΚ Tree Insert", BKTreeInsert},
    {"ΒΚ Tree Lookup", BKTreeLookup},
    {"Queue Flow", QueueFlow},
    {NULL, NULL} /* zeroed record marking the end of the list */
};