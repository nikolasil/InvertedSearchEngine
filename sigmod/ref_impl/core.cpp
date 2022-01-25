/*
 * core.cpp version 1.0
 * Copyright (c) 2013 KAUST - InfoCloud Group (All Rights Reserved)
 * Author: Amin Allam
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "../include/core.h"
#include "../../Data Structures/DocumentList/DocumentList.h"
#include "../../Data Structures/MatchArray/MatchArray.h"
#include "../../Data Structures/hashTable/bucket.h"
#include "../../Data Structures/hashTable/hashTable.h"
#include "../../Data Structures/queryList/exactInfoList.h"
#include "../../Data Structures/queryList/heInfoList.h"
#include "../../Data Structures/string/String.h"
#include "../../Data Structures/tree/BK_Tree.h"
#include "../../Data Structures/tree/hammingArray.h"

#include "../../Job Scheduler/JobScheduler.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>

using namespace std;

JobScheduler jobScheduler(NUM_THREADS);
DataStructs structs;

ErrorCode InitializeIndex() {
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////
ErrorCode end(int numArgs, void **args) {
  return EC_SUCCESS;
}
ErrorCode DestroyIndex() {
  for (int i = 0; i < NUM_THREADS; i++) {
    void **args0 = new void *[1];

    jobScheduler.addJob(new Job('.', &end, args0, 0));
    delete args0;
  }
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

DataStructs *getStructs() {
  return &structs;
}

ErrorCode query(int numArgs, void **args) {
  QueryID query_id = *(QueryID *)args[0];
  const char *query_str = (const char *)args[1];
  MatchType match_type = *((MatchType *)args[2]);
  unsigned int match_dist = *((unsigned int *)args[3]);

  Query query;

  query.query_id = query_id;
  strcpy(query.str, query_str);
  query.match_type = match_type;
  query.match_dist = match_dist;
  // cout << "q " << query_id << endl;
  switch (match_type) {
  case MT_EXACT_MATCH: {
    // cout << "Query id: " << query_id;
    char temp_query_str[MAX_QUERY_LENGTH];
    char *save_ptr;
    strcpy(temp_query_str, query_str);
    unsigned int maxQueryWords = 0;
    char *wordToken = strtok_r(temp_query_str, " ", &save_ptr);
    ExactInfo *exactInfo = new ExactInfo();
    exactInfo->query_id = query_id;
    exactInfo->flag = true;

    while (wordToken != NULL) {
      // cout << " " << wordToken;
      structs.getHashTable()->insert(new String(wordToken), exactInfo);
      maxQueryWords++;

      wordToken = strtok_r(NULL, " ", &save_ptr);
    }

    // cout << endl;
    exactInfo->maxQueryWords = maxQueryWords;
    // structs.getExactStructsList()->addQuery(exactInfo);
    structs.getExactQueryHashTable()->insert(exactInfo);

    delete wordToken;
    break;
  }
  case MT_EDIT_DIST: {
    // cout << "Query id: " << query_id;
    char temp_query_str[MAX_QUERY_LENGTH];
    strcpy(temp_query_str, query_str);
    unsigned int maxQueryWords = 0;
    char *save_ptr;
    char *wordToken = strtok_r(temp_query_str, " ", &save_ptr);
    HEInfo *heInfo = new HEInfo();
    heInfo->query_id = query_id;
    heInfo->matchDist = match_dist;
    heInfo->flag = true;

    while (wordToken != NULL) {
      // cout << " " << wordToken;
      structs.getEdit()->add(new String(wordToken), heInfo);
      maxQueryWords++;
      wordToken = strtok_r(NULL, " ", &save_ptr);
    }

    // cout << endl;
    heInfo->maxQueryWords = maxQueryWords;
    // structs.getHeStructsList()->addQuery(heInfo);
    structs.getHEQueryHashTable()->insert(heInfo);
    delete wordToken;
    break;
  }
  case MT_HAMMING_DIST: {
    // cout << "Query id: " << query_id;
    char temp_query_str[MAX_QUERY_LENGTH];
    strcpy(temp_query_str, query_str);
    unsigned int maxQueryWords = 0;
    char *save_ptr;
    char *wordToken = strtok_r(temp_query_str, " ", &save_ptr);
    HEInfo *heInfo = new HEInfo();

    heInfo->query_id = query_id;
    heInfo->matchDist = match_dist;
    heInfo->flag = true;

    while (wordToken != NULL) {
      // cout << " " << wordToken;
      structs.getHamming()->insert(new String(wordToken), heInfo);
      maxQueryWords++;
      wordToken = strtok_r(NULL, " ", &save_ptr);
    }
    // cout << endl;

    heInfo->maxQueryWords = maxQueryWords;
    // structs.getHeStructsList()->addQuery(heInfo);
    structs.getHEQueryHashTable()->insert(heInfo);
    delete wordToken;

    break;
  }
  }
  return EC_SUCCESS;
}

ErrorCode
StartQuery(QueryID query_id, const char *query_str, MatchType match_type, unsigned int match_dist) {
  void **args0 = new void *[4];
  args0[0] = new QueryID(query_id);
  args0[1] = new char[MAX_QUERY_LENGTH];
  strcpy((char *)args0[1], query_str);
  args0[2] = new MatchType(match_type);
  args0[3] = new unsigned int(match_dist);

  jobScheduler.addJob(new Job('s', &query, args0, 4));
  structs.setMaxQueryId(structs.getMaxQueryId() + 1);
  // cout << "added start querry" << endl;
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode equery(int numArgs, void **args) {
  QueryID query_id = *(QueryID *)args[0];
  // structs.getForDeletion()->add(query_id);
  structs.getExactQueryHashTable()->setFlagFalse(query_id);
  structs.getHEQueryHashTable()->setFlagFalse(query_id);
  return EC_SUCCESS;
}

ErrorCode EndQuery(QueryID query_id) {
  void **args0 = new void *[1];
  args0[0] = new QueryID(query_id);

  jobScheduler.addJob(new Job('e', &equery, args0, 1));
  // cout << "added end querry" << endl;

  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode document(int numArgs, void **args) {
  DocID doc_id = *(DocID *)args[0];
  // cout << doc_id << endl;
  const char *doc_str = (const char *)args[1];

  char cur_doc_str[MAX_DOC_LENGTH];
  strcpy(cur_doc_str, doc_str);

  MatchArray *matchArray = new MatchArray(structs.getMaxQueryId());

  char *save_ptr;
  const char *wordToken = strtok_r(cur_doc_str, " ", &save_ptr);
  String *word = nullptr;

  while (wordToken != NULL) {
    word = new String(wordToken);

    // HashTable
    structs.getHashTable()->lookup(word, matchArray);

    // Edit Distance
    structs.getEdit()->editLookup(word, matchArray);

    // Hamming Distance
    structs.getHamming()->lookup(word, matchArray);

    if (wordToken) {
      wordToken = strtok_r(NULL, " ", &save_ptr);
    }
    delete word;
  }
  delete wordToken;

  Document doc;
  doc.doc_id = doc_id;
  doc.num_res = matchArray->getMatchedIds()->getCount();
  doc.query_ids = 0;

  if (doc.num_res != 0) {
    doc.query_ids = new QueryID[doc.num_res];
    ResultListNode *r_cur = matchArray->getMatchedIds()->getHead();
    int k = 0;
    while (r_cur != nullptr) {
      doc.query_ids[k++] = r_cur->getId();
      r_cur = r_cur->getNext();
    }
  }

  structs.getDocs()->add(doc);
  delete matchArray;
  return EC_SUCCESS;
}

ErrorCode MatchDocument(DocID doc_id, const char *doc_str) {
  void **args0 = new void *[2];
  args0[0] = new DocID(doc_id);
  args0[1] = new char[MAX_DOC_LENGTH];
  memcpy((char *)args0[1], doc_str, strlen(doc_str));
  // structs.getHashTable()->print();
  jobScheduler.addJob(new Job('m', &document, args0, 2));
  // cout << "added match doc" << endl;
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////
bool flag = true;
ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids) {
  // Get the first undeliverd resuilt from "docs" and return it
  *p_doc_id = 0;
  *p_num_res = 0;
  *p_query_ids = 0;

  // cout << "before getNextAvailRes" << endl;

  if (flag) {
    Job *j = new Job('w', NULL, NULL, 0);
    j->setStatus(0);
    jobScheduler.addJob(j);
    // structs.getHamming()->print();
    // structs.getEdit()->print();
    pthread_cond_wait(jobScheduler.getCond(), jobScheduler.getCondMutex());
    // structs.getHashTable()->print();
  }
  // cout << "broke wait getNextAvailRes" << endl;

  Document d = structs.getDocs()->removeFirst()->getDoc();
  // structs.getDocs()->print();
  // cout << d.query_ids << endl;
  // cout << structs.getDocs()->getCount() << " after getNextAvailRes " << d.doc_id << endl;
  *p_doc_id = d.doc_id;
  *p_num_res = d.num_res;
  *p_query_ids = d.query_ids;

  // structs.getDocs()->remove(d.doc_id);
  if (flag)
    flag = false;
  if (structs.getDocs()->getCount() == 0)
    flag = true;
  return EC_SUCCESS;
}

// ///////////////////////////////////////////////////////////////////////////////////////////////
