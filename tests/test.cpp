#include "../sigmod/include/core.h"
#include "../sigmod/include/structs.h"
#include "acutest.h"
#include <cstring>
#include <iostream>

using namespace std;

void startQuery(void) { // Test startQuery function

  int queryId = 10;
  const char *query_str = "Nikolas Michalis Kostas";
  int result = StartQuery(queryId, query_str, MT_EXACT_MATCH, 0);
  TEST_ASSERT(result == EC_SUCCESS);

  HashTable *ht = getStructs()->getHashTable();

  TEST_ASSERT(result == EC_SUCCESS);
  unsigned char *returnHash = SHA1((const unsigned char *)("Nikolas"), strlen("Nikolas"), NULL);
  int index = ht->getIndex(returnHash);
  int diff = strcmp(ht->getBucket(index)->getHead()->getWord()->getStr(), "Nikolas");
  TEST_ASSERT(diff == 0);
  returnHash = SHA1((const unsigned char *)("Michalis"), strlen("Michalis"), NULL);
  index = ht->getIndex(returnHash);
  diff = strcmp(ht->getBucket(index)->getHead()->getWord()->getStr(), "Michalis");
  TEST_ASSERT(diff == 0);
  returnHash = SHA1((const unsigned char *)("Kostas"), strlen("Kostas"), NULL);
  index = ht->getIndex(returnHash);
  diff = strcmp(ht->getBucket(index)->getHead()->getNext()->getWord()->getStr(), "Kostas");
  TEST_ASSERT(diff == 0);

  result = StartQuery(queryId + 1, query_str, MT_HAMMING_DIST, 2);
  TEST_ASSERT(result == EC_SUCCESS);
  hammingArray *hamming = getStructs()->getHamming();

  // Check first word
  diff = strcmp(hamming->getTree(strlen("Nikolas") - 4)->getRoot()->getData()->getStr(), "Nikolas");
  TEST_ASSERT(diff == 0);
  // Check 2nd word
  diff = strcmp(hamming->getTree(strlen("Michalis") - 4)->getRoot()->getData()->getStr(), "Michalis");
  TEST_ASSERT(diff == 0);
  // Check 3rd word
  diff = strcmp(hamming->getTree(strlen("Kostas") - 4)->getRoot()->getData()->getStr(), "Kostas");
  TEST_ASSERT(diff == 0);

  result = StartQuery(queryId + 2, query_str, MT_EDIT_DIST, 3);
  BK_Tree *edit = getStructs()->getEdit();
  diff = strcmp(edit->getRoot()->getData()->getStr(), "Nikolas");
  TEST_ASSERT(diff == 0);
  diff = strcmp(edit->getRoot()->findChild(5)->getData()->getStr(), "Michalis");
  TEST_ASSERT(diff == 0);
  diff = strcmp(edit->getRoot()->findChild(5)->findChild(6)->getData()->getStr(), "Kostas");
  TEST_ASSERT(diff == 0);

  TEST_ASSERT(result == EC_SUCCESS);
}

void matchDocument() {
  int doc_id = 1;
  int maxQueryId = 5;
  const char *query_str = "Nikolas Michalis Kostas";
  const char *query_str2 = "Michalis Airport Code";
  const char *query_str3 = "Nikolas Catfsd Strong Real";
  const char *query_str4 = "Kostas Test";

  StartQuery(1, query_str, MT_EXACT_MATCH, 0);
  StartQuery(2, query_str2, MT_HAMMING_DIST, 2);
  StartQuery(3, query_str3, MT_HAMMING_DIST, 2);
  StartQuery(4, query_str, MT_EDIT_DIST, 2);
  StartQuery(5, query_str4, MT_EDIT_DIST, 3);

  const char *doc_str = "Nikolaw Nikolas Michalvs Kastss Michalis Kostas Serlas Mivdflis Nikcfsa Nikobk afdop fasmi lorem asrlas fsniko michss kostav kowgb kostas ";
  MatchDocument(doc_id, doc_str);

  DocumentList *docList = getStructs()->getDocs();

  DocumentNode *node = docList->getHead();

  TEST_ASSERT(node->getDoc().num_res == 2);
  TEST_ASSERT(node->getDoc().query_ids[0] == 1);
  TEST_ASSERT(node->getDoc().query_ids[1] == 4);
}

void getNextAvailableRes() {
  int doc_id = 1;
  int maxQueryId = 5;
  const char *query_str = "Nikolas Michalis Kostas";
  const char *query_str2 = "Michalis Airport Code";
  const char *query_str3 = "Nikolas Catfsd Strong Real";
  const char *query_str4 = "Kostas Test";

  StartQuery(1, query_str, MT_EXACT_MATCH, 0);
  StartQuery(2, query_str2, MT_HAMMING_DIST, 2);
  StartQuery(3, query_str3, MT_HAMMING_DIST, 2);
  StartQuery(4, query_str, MT_EDIT_DIST, 2);
  StartQuery(5, query_str4, MT_EDIT_DIST, 3);

  const char *doc_str = "Nikolaw Nikolas Michalvs Kastss Michalis Kostas Serlas Mivdflis Nikcfsa Nikobk afdop fasmi lorem asrlas fsniko michss kostav kowgb kostas ";
  const char *doc_str2 = "Nikolaw Nikolas Sefrlas Mivdflhcxis Nikcfsa Nfasb fasmi lorem asrlas fsniko michss kostav kowgb kostas ";
  const char *doc_str3 = "Nikolaw Michalvs Kastss Mivdflis Nikcfsa Nikobk afdop fasmi lorem asrlas fsniko michss kostav kowgb kostas ";

  MatchDocument(doc_id, doc_str);
  MatchDocument(doc_id + 1, doc_str2);
  MatchDocument(doc_id + 2, doc_str3);

  DocID *docId = new DocID();
  unsigned int *p_num_res = new unsigned int();
  QueryID *p_query_ids = nullptr;
  GetNextAvailRes(docId, p_num_res, &p_query_ids);

  TEST_ASSERT(*docId == 1);
  TEST_ASSERT(*p_num_res == 2);
  TEST_ASSERT(p_query_ids[0] == 1);
  TEST_ASSERT(p_query_ids[1] == 4);

  GetNextAvailRes(docId, p_num_res, &p_query_ids);

  TEST_ASSERT(*docId == 2);
  TEST_ASSERT(*p_num_res == 0);
  GetNextAvailRes(docId, p_num_res, &p_query_ids);

  TEST_ASSERT(*docId == 3);
  TEST_ASSERT(*p_num_res == 1);
  TEST_ASSERT(p_query_ids[0] == 4);
}

void endQuery() {
  int doc_id = 1;
  int maxQueryId = 5;
  const char *query_str = "Nikolas Michalis Kostas";
  const char *query_str2 = "Michalis Airport Code";
  const char *query_str3 = "Nikolas Catfsd Strong Real";
  const char *query_str4 = "Kostas Test";

  StartQuery(1, query_str, MT_EXACT_MATCH, 0);
  StartQuery(2, query_str2, MT_HAMMING_DIST, 2);
  StartQuery(3, query_str3, MT_HAMMING_DIST, 2);
  StartQuery(4, query_str, MT_EDIT_DIST, 2);
  StartQuery(5, query_str4, MT_EDIT_DIST, 3);

  EndQuery(1);
  EndQuery(5);
  TEST_ASSERT(getStructs()->getForDeletion()->getHead()->getId() == 1);
  TEST_ASSERT(getStructs()->getForDeletion()->getHead()->getNext()->getId() == 5);
}

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
  TEST_ASSERT(ht->getBucket(1)->getHead()->getWord()->exactMatch(new String("Michalis")));
  TEST_ASSERT(ht->getBucket(1)->getHead()->getList()->getHead()->getWordInfo() == info3);
  TEST_ASSERT(ht->getBucket(1)->getHead()->getNext()->getWord()->exactMatch(new String("Kostas")));
  TEST_ASSERT(ht->getBucket(1)->getHead()->getNext()->getList()->getHead()->getWordInfo() == info5);
  TEST_ASSERT(ht->getBucket(5)->getHead()->getWord()->exactMatch(new String("Nikolas")));
  TEST_ASSERT(ht->getBucket(5)->getHead()->getList()->getHead()->getWordInfo() == info2);
  TEST_ASSERT(ht->getBucket(5)->getHead()->getList()->getHead()->getNext()->getWordInfo() == info4);
  TEST_ASSERT(ht->getBucket(33)->getHead()->getWord()->exactMatch(new String("Nikolas1")));
  TEST_ASSERT(ht->getBucket(33)->getHead()->getList()->getHead()->getWordInfo() == info1);
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
  String *mw = nullptr;
  exactInfoList *l = ht->lookup(new String("Nikolas"), &mw);

  TEST_ASSERT(l->getHead()->getWordInfo() == info2);
  TEST_ASSERT(l->getHead()->getNext()->getWordInfo() == info4);
  TEST_ASSERT(mw->exactMatch(new String("Nikolas")));
  l = ht->lookup(new String("Niko"), &mw);
  TEST_ASSERT(l == nullptr);
  TEST_ASSERT(mw == nullptr);
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
  tree->editLookup(new String("Kostas"), matchArray, forDel);
  tree->editLookup(new String("Nikolas"), matchArray, forDel);
  // tree->editLookup(new String("Kostas"), matchArray, forDel);
  // matchArray->print();
  TEST_ASSERT(matchArray->getMatchedIds()->getHead()->getId() == 2);
  delete matchArray;
  matchArray = new MatchArray(5);
  tree->hammingLookup(new String("Kostas"), matchArray, forDel);
  tree->hammingLookup(new String("Nikolas"), matchArray, forDel);
  TEST_ASSERT(matchArray->getMatchedIds()->getHead()->getId() == 2);
}

TEST_LIST = {
    {"Hash Table Insert", htInsert},
    {"Hash Table Lookup", htLookup},
    {"ΒΚ Tree Insert", BKTreeInsert},
    {"ΒΚ Tree Lookup", BKTreeLookup},
    {"StartQuery", startQuery},
    {"MatchDocument", matchDocument},
    {"GetNextAvailableRes", getNextAvailableRes},
    {"endQuery", endQuery},

    {NULL, NULL} /* zeroed record marking the end of the list */
};