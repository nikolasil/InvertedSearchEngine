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
}

TEST_LIST = {
    {"StartQuery", startQuery},
    {"MatchDocument", matchDocument},
    {"GetNextAvailableRes", getNextAvailableRes},

    {NULL, NULL} /* zeroed record marking the end of the list */
};