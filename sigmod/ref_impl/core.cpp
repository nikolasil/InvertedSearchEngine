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
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

// Keeps all currently matched words of the queries
///////////////////////////////////////////////////////////////////////////////////////////////

HashTable *ht = nullptr;
hammingArray *hamming = nullptr;
BK_Tree *edit = nullptr;
MatchArray *matchArray = nullptr;
ResultList *forDeletion = nullptr;
DocumentList *docs = nullptr;
unsigned int maxQueryId = 0;

exactInfoList *exactStructsList = nullptr;
heInfoList *heStructsList = nullptr;

ErrorCode InitializeIndex() {
  ht = new HashTable();
  hamming = new hammingArray();
  edit = new BK_Tree();
  forDeletion = new ResultList();
  docs = new DocumentList();
  exactStructsList = new exactInfoList();
  heStructsList = new heInfoList();
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode DestroyIndex() {
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
  unsigned int maxQueryWords = 0;
  char *wordToken = strtok(temp_query_str, " ");

  switch (match_type) {
  case MT_EXACT_MATCH: {
    ExactInfo *exactInfo = new ExactInfo();
    exactInfo->query_id = query_id;
    exactInfo->flag = true;

    while (wordToken != NULL) {
      ht->insert(new String(wordToken), exactInfo);
      maxQueryWords++;
      wordToken = strtok(NULL, " ");
    }

    exactInfo->maxQueryWords = maxQueryWords;
    exactStructsList->addQuery(exactInfo);
    break;
  }
  case MT_EDIT_DIST: {
    HEInfo *heInfo = new HEInfo();
    heInfo->query_id = query_id;
    heInfo->matchDist = match_dist;
    heInfo->flag = true;

    while (wordToken != NULL) {
      edit->add(new String(wordToken), heInfo);
      maxQueryWords++;
      wordToken = strtok(NULL, " ");
    }

    heInfo->maxQueryWords = maxQueryWords;
    heStructsList->addQuery(heInfo);
    break;
  }
  case MT_HAMMING_DIST: {
    HEInfo *heInfo = new HEInfo();

    heInfo->query_id = query_id;
    heInfo->matchDist = match_dist;
    heInfo->flag = true;

    while (wordToken != NULL) {
      hamming->insert(new String(wordToken), heInfo);
      maxQueryWords++;
      wordToken = strtok(NULL, " ");
    }

    heInfo->maxQueryWords = maxQueryWords;
    heStructsList->addQuery(heInfo);
    break;
  }
  }
  delete wordToken;
  maxQueryId++;

  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode EndQuery(QueryID query_id) {
  forDeletion->add(query_id);
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode MatchDocument(DocID doc_id, const char *doc_str) {
  char cur_doc_str[MAX_DOC_LENGTH];
  strcpy(cur_doc_str, doc_str);

  MatchArray *matchArray = new MatchArray(maxQueryId);
  char *wordToken = strtok(cur_doc_str, " ");
  String *word = nullptr;
  String *matchedWord = nullptr;
  exactInfoList *exactList = nullptr;
  exactInfoNode *cur = nullptr;
  while (wordToken != NULL) {
    word = new String(wordToken);

    // hashTable
    matchedWord = nullptr;
    exactList = ht->lookup(word, &matchedWord);
    if (exactList != nullptr) {
      cur = exactList->getHead();
      while (cur != nullptr) {
        if (forDeletion->searchRemove(cur->getId())) {
          cur->setFlag(false);
        } else if (cur->getFlag())
          matchArray->insert(matchedWord, cur->getId(), cur->getMaxQueryWords());
        cur = cur->getNext();
      }
    }
    // Edit Distance
    edit->editLookup(word, matchArray, forDeletion);

    // Hamming Distance
    hamming->lookup(word, matchArray, forDeletion);

    if (wordToken) {
      wordToken = strtok(NULL, " ");
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

  docs->addToEnd(doc);
  delete matchArray;
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////

ErrorCode GetNextAvailRes(DocID *p_doc_id, unsigned int *p_num_res, QueryID **p_query_ids) {
  // Get the first undeliverd resuilt from "docs" and return it
  *p_doc_id = 0;
  *p_num_res = 0;
  *p_query_ids = 0;
  if (docs->getCount() == 0)
    return EC_NO_AVAIL_RES;

  *p_doc_id = docs->getHead()->getDoc().doc_id;
  *p_num_res = docs->getHead()->getDoc().num_res;
  *p_query_ids = docs->getHead()->getDoc().query_ids;

  docs->removeFromStart();
  return EC_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////////////////////
