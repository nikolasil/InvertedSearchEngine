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
#include "../../Data Structures/MatchArray/MatchArray.h"
#include "../../Data Structures/hashTable/bucket.h"
#include "../../Data Structures/hashTable/hashTable.h"
#include "../../Data Structures/string/String.h"
#include "../../Data Structures/tree/BK_Tree.h"
#include "../../Data Structures/tree/hammingArray.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////

// Computes edit distance between a null-terminated string "a" with length "na"
//  and a null-terminated string "b" with length "nb"
int EditDistance(char *a, int na, char *b, int nb) {
  int oo = 0x7FFFFFFF;

  static int T[2][MAX_WORD_LENGTH + 1];

  int ia, ib;

  int cur = 0;
  ia = 0;

  for (ib = 0; ib <= nb; ib++)
    T[cur][ib] = ib;

  cur = 1 - cur;

  for (ia = 1; ia <= na; ia++) {
    for (ib = 0; ib <= nb; ib++)
      T[cur][ib] = oo;

    int ib_st = 0;
    int ib_en = nb;

    if (ib_st == 0) {
      ib = 0;
      T[cur][ib] = ia;
      ib_st++;
    }

    for (ib = ib_st; ib <= ib_en; ib++) {
      int ret = oo;

      int d1 = T[1 - cur][ib] + 1;
      int d2 = T[cur][ib - 1] + 1;
      int d3 = T[1 - cur][ib - 1];
      if (a[ia - 1] != b[ib - 1])
        d3++;

      if (d1 < ret)
        ret = d1;
      if (d2 < ret)
        ret = d2;
      if (d3 < ret)
        ret = d3;

      T[cur][ib] = ret;
    }

    cur = 1 - cur;
  }

  int ret = T[1 - cur][nb];

  return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////

// Computes Hamming distance between a null-terminated string "a" with length "na"
//  and a null-terminated string "b" with length "nb"
unsigned int HammingDistance(char *a, int na, char *b, int nb) {
  int j, oo = 0x7FFFFFFF;
  if (na != nb)
    return oo;

  unsigned int num_mismatches = 0;
  for (j = 0; j < na; j++)
    if (a[j] != b[j])
      num_mismatches++;

  return num_mismatches;
}

///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////

// Keeps all query ID results associated with a dcoument
struct Document {
  DocID doc_id;
  unsigned int num_res;
  QueryID *query_ids;
};

///////////////////////////////////////////////////////////////////////////////////////////////

// Keeps all currently active queries
vector<Query> queries;

// Keeps all currently available results that has not been returned yet
vector<Document> docs;

// Keeps all currently matched words of the queries
MatchArray *matchArray = nullptr;
///////////////////////////////////////////////////////////////////////////////////////////////

HashTable *ht;
hammingArray *hamming;
BK_Tree *edit;
unsigned int maxQueryId = 0;

ErrorCode InitializeIndex() {
  ht = new HashTable();
  hamming = new hammingArray();
  edit = new BK_Tree();
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode DestroyIndex() {
  delete ht;
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////
ErrorCode
StartQuery(QueryID query_id, const char *query_str, MatchType match_type, unsigned int match_dist) {
  Query query;

  query.query_id = query_id;
  strcpy(query.str, query_str);
  query.match_type = match_type;
  query.match_dist = match_dist;

  char temp_query_str[MAX_QUERY_LENGTH];
  strcpy(temp_query_str, query_str);
  int maxQueryWords = 0;
  char *wordToken = strtok(temp_query_str, " ");
  while (wordToken != NULL) {
    maxQueryWords++;
    wordToken = strtok(NULL, " ");
  }

  strcpy(temp_query_str, query_str);
  wordToken = strtok(temp_query_str, " ");

  switch (match_type) {
  case MT_EXACT_MATCH: {
    ExactInfo exactInfo;
    exactInfo.query_id = query_id;
    exactInfo.maxQueryWords = maxQueryWords;

    while (wordToken != NULL) {
      ht->insert(new String(wordToken), exactInfo);
      wordToken = strtok(NULL, " ");
    }
    break;
  }
  case MT_EDIT_DIST: {
    // cout << "edit distance" << endl;
    HEInfo heInfo;
    heInfo.query_id = query_id;
    heInfo.maxQueryWords = maxQueryWords;
    heInfo.matchDist = match_dist;

    while (wordToken != NULL) {
      edit->add(new String(wordToken), heInfo);
      wordToken = strtok(NULL, " ");
    }
    break;
  }
  case MT_HAMMING_DIST: {
    HEInfo heInfo;
    heInfo.query_id = query_id;
    heInfo.maxQueryWords = maxQueryWords;
    heInfo.matchDist = match_dist;

    while (wordToken != NULL) {
      hamming->insert(new String(wordToken), heInfo);
      wordToken = strtok(NULL, " ");
    }
    break;
  }
  }

  // cout << "______________ EXACT"
  //      << "_______________" << endl;
  // ht->print();
  // cout << "______________ EDIT"
  //      << "_______________" << endl;
  // edit->print();
  // cout << "______________ HAMMING"
  //      << "_______________" << endl;
  // hamming->print();

  // Add this query to the active query set
  if (maxQueryId < query_id)
    maxQueryId = query_id;

  queries.push_back(query);
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode EndQuery(QueryID query_id) {
  // Remove this query from the active query set
  unsigned int i, n = queries.size();
  for (i = 0; i < n; i++) {
    if (queries[i].query_id == query_id) {
      queries.erase(queries.begin() + i);
      break;
    }
  }
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode MatchDocument(DocID doc_id, const char *doc_str) {
  char cur_doc_str[MAX_DOC_LENGTH];
  strcpy(cur_doc_str, doc_str);

  MatchArray *matchArray = new MatchArray(maxQueryId);

  char *wordToken = strtok(cur_doc_str, " ");
  while (wordToken != NULL) {
    String *word = new String(wordToken);
    // String *matchedWord = new String("");
    // // hashTable
    // exactInfoList *exactList = ht->lookup(word, &matchedWord);
    // if (exactList != nullptr) {
    //   cout << "Lookup Success" << endl;
    //   exactList->print();
    //   exactInfoNode *cur = exactList->getHead();
    //   while (cur != nullptr) {
    //     matchArray->insert(matchedWord, cur->getId(), cur->getMaxQueryWords());
    //     cur = cur->getNext();
    //   }
    // }
    // editDistance

    heInfoList *editList = edit->lookup(word);
    if (editList != nullptr) {
      cout << "Lookup Success ";
      word->print();
      cout << endl;

      editList->print();
    }
    // hammingDistance

    wordToken = strtok(NULL, " ");
  }

  ResultList *rl = matchArray->getMatchedIds();
  Document doc;
  doc.doc_id = doc_id;
  doc.num_res = rl->getCount();
  doc.query_ids = 0;
  ResultListNode *cur = rl->getHead();
  int k = 0;
  while (cur != nullptr) {
    doc.query_ids[k++] = cur->getId();
    cur = cur->getNext();
  }

  docs.push_back(doc);
  delete matchArray;
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids) {
  // Get the first undeliverd resuilt from "docs" and return it
  *p_doc_id = 0;
  *p_num_res = 0;
  *p_query_ids = 0;
  if (docs.size() == 0)
    return EC_NO_AVAIL_RES;
  *p_doc_id = docs[0].doc_id;
  *p_num_res = docs[0].num_res;
  *p_query_ids = docs[0].query_ids;
  docs.erase(docs.begin());
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////
