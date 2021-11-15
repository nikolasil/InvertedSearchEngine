#include "../Data Structures/entry/entry.h"
#include "../Functions/functions.h"
#include "acutest.h"
#include <cstring>
#include <iostream>

using namespace std;

void create_entry(void) { // Test create_entry function
  const word *w1 = new word("hell");
  entry *e1;

  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS);          // test that result is success
  TEST_ASSERT(e1 != nullptr);                                // test that entry exists (has been created)
  TEST_ASSERT(e1->getWord() != nullptr);                     // test that word exists
  TEST_ASSERT(strcmp(e1->getWord()->getStr(), "hell") == 0); // test that word has not been changed
  TEST_ASSERT(w1 != nullptr);                                // test that w1 still exists
}

void destroy_entry(void) { // Test destroy_entry function
  const word *w1 = new word("hell");
  entry *e1;

  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(destroy_entry(&e1) == EC_SUCCESS);    // test that result is success
  TEST_ASSERT(e1 == nullptr);                       // test that entry doesn't exist
}

void create_entry_list(void) { // Test create_entry_list function
  entry_list *el;

  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(el != nullptr);                        // test that entry list exist
}

void get_number_entries(void) { // Test create_entry_list function
  entry_list *el;

  TEST_ASSERT(get_number_entries((const entry_list *)el) == 0); // test that result is 0
  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS);            // test that result is success
  TEST_ASSERT(get_number_entries((const entry_list *)el) == 0); // test that result is 0

  const word *w1 = new word("hell");
  const word *w2 = new word("melt");
  entry *e1, *e2;
  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS); // test that result is success

  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS);                 // add entry e1 to list
  TEST_ASSERT(get_number_entries((const entry_list *)el) == 1); // test that result is 1
  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS);                 // add entry e2 to list
  TEST_ASSERT(get_number_entries((const entry_list *)el) == 2); // test that result is 2
}

void add_entry(void) { // Test add_entry function
  entry_list *el;

  const word *w1 = new word("hell");
  const word *w2 = new word("melt");
  entry *e1, *e2;
  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS); // test that result is success

  TEST_ASSERT(add_entry(el, nullptr) == EC_FAIL);
  TEST_ASSERT(add_entry(nullptr, e1) == EC_FAIL);
  TEST_ASSERT(add_entry(nullptr, nullptr) == EC_FAIL);
  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS);      // add entry e1 to list
  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS);      // add entry e2 to list
  TEST_ASSERT(get_first(el) == e1);                  // check that e1 is the first entry
  TEST_ASSERT(get_next(el, e1) == e2);               // check that e1->next is e2
  TEST_ASSERT(get_next(el, e2) == nullptr);          // check that e2->next is nullptr
}

void get_first(void) { // Test get_first function
  entry_list *el;

  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS); // test that result is success

  const word *w1 = new word("hell");
  const word *w2 = new word("melt");
  entry *e1, *e2;
  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS); // test that result is success

  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS); // add entry e1 to list
  TEST_ASSERT(get_first(el) == e1);             // check that e1 is the first entry
  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS); // add entry e2 to list
  TEST_ASSERT(get_first(el) == e1);             // check that e1 is the first entry
}

void get_next(void) { // Test get_next function
  entry_list *el;

  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS); // test that result is success

  const word *w1 = new word("hell");
  const word *w2 = new word("melt");
  const word *w3 = new word("yeah");
  entry *e1, *e2, *e3;
  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry(w3, &e3) == EC_SUCCESS); // test that result is success

  TEST_ASSERT(get_next(el, e1) == nullptr);      // check that e1->next is nullptr
  TEST_ASSERT(get_next(el, e2) == nullptr);      // check that e2->next is nullptr
  TEST_ASSERT(get_next(el, e3) == nullptr);      // check that e3->next is nullptr
  TEST_ASSERT(get_next(el, nullptr) == nullptr); // check that returns nullptr
  TEST_ASSERT(get_next(nullptr, e1) == nullptr); // check that e1->next is nullptr

  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS);  // add entry e1 to list
  TEST_ASSERT(get_next(el, e1) == nullptr);      // check that e1->next is nullptr
  TEST_ASSERT(get_next(el, e2) == nullptr);      // check that e2->next is nullptr
  TEST_ASSERT(get_next(el, e3) == nullptr);      // check that e3->next is nullptr
  TEST_ASSERT(get_next(el, nullptr) == nullptr); // check that returns nullptr

  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS);  // add entry e2 to list
  TEST_ASSERT(get_next(el, e1) == e2);           // check that e1->next is e2
  TEST_ASSERT(get_next(el, e2) == nullptr);      // check that e2->next is nullptr
  TEST_ASSERT(get_next(el, e3) == nullptr);      // check that e3->next is nullptr
  TEST_ASSERT(get_next(el, nullptr) == nullptr); // check that returns nullptr

  TEST_ASSERT(add_entry(el, e3) == EC_SUCCESS);  // add entry e2 to list
  TEST_ASSERT(get_next(el, e1) == e2);           // check that e1->next is e2
  TEST_ASSERT(get_next(el, e2) == e3);           // check that e2->next is e3
  TEST_ASSERT(get_next(el, e3) == nullptr);      // check that e3->next is nullptr
  TEST_ASSERT(get_next(el, nullptr) == nullptr); // check that returns nullptr
}

void destroy_entry_list(void) { // Test destroy_entry_list function
  entry_list *el;

  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS);  // test that result is success
  TEST_ASSERT(destroy_entry_list(&el) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS);  // test that result is success

  const word *w1 = new word("hell");
  const word *w2 = new word("melt");
  const word *w3 = new word("yeah");
  entry *e1, *e2, *e3;
  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry(w3, &e3) == EC_SUCCESS); // test that result is success

  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS); // add entry e1 to list
  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS); // add entry e2 to list
  TEST_ASSERT(add_entry(el, e3) == EC_SUCCESS); // add entry e3 to list

  TEST_ASSERT(destroy_entry_list(&el) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(el == nullptr);                         // check that el is nullptr
  TEST_ASSERT(add_entry(el, e1) == EC_FAIL);          // add entry e3 to list
}

void build_entry_index(void) { // Test build_entry_index function
  entry_list *el;
  entry *e1, *e2, *e3, *e4, *e5, *e6, *e7;
  const word *w1 = new word("hell");
  const word *w2 = new word("help");
  const word *w3 = new word("fall");
  const word *w4 = new word("small");
  const word *w5 = new word("fell");
  const word *w6 = new word("felt");
  const word *w7 = new word("melt");

  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS);

  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w3, &e3) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w4, &e4) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w5, &e5) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w6, &e6) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w7, &e7) == EC_SUCCESS);

  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e3) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e4) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e5) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e6) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e7) == EC_SUCCESS);

  tree *ix;
  TEST_ASSERT(build_entry_index(el, MT_HAMMING_DIST, &ix) == EC_SUCCESS);
  TEST_ASSERT(ix != nullptr);
  TEST_ASSERT(strcmp(ix->getRoot()->getData()->getStr(), e1->getWord()->getStr()) == 0);                             // hell
  TEST_ASSERT(strcmp(ix->getRoot()->findChild(1)->getData()->getStr(), e2->getWord()->getStr()) == 0);               // help
  TEST_ASSERT(strcmp(ix->getRoot()->findChild(2)->getData()->getStr(), e3->getWord()->getStr()) == 0);               // fall
  TEST_ASSERT(strcmp(ix->getRoot()->findChild(3)->getData()->getStr(), e4->getWord()->getStr()) == 0);               // small
  TEST_ASSERT(strcmp(ix->getRoot()->findChild(1)->findChild(2)->getData()->getStr(), e5->getWord()->getStr()) == 0); // fell
  TEST_ASSERT(strcmp(ix->getRoot()->findChild(2)->findChild(2)->getData()->getStr(), e6->getWord()->getStr()) == 0); // felt
  TEST_ASSERT(strcmp(ix->getRoot()->findChild(2)->findChild(3)->getData()->getStr(), e7->getWord()->getStr()) == 0); // melt
}

void lookup_entry_index(void) { // Test lookup_entry_index function
  entry_list *el;
  entry *e1, *e2, *e3, *e4, *e5, *e6, *e7;
  const word *w1 = new word("hell");
  const word *w2 = new word("help");
  const word *w3 = new word("fall");
  const word *w4 = new word("small");
  const word *w5 = new word("fell");
  const word *w6 = new word("felt");
  const word *w7 = new word("melt");

  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS);

  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w3, &e3) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w4, &e4) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w5, &e5) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w6, &e6) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w7, &e7) == EC_SUCCESS);

  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e3) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e4) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e5) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e6) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e7) == EC_SUCCESS);

  tree *ix;
  TEST_ASSERT(build_entry_index(el, MT_HAMMING_DIST, &ix) == EC_SUCCESS);
  entry_list *result;
  const word key("henn");
  TEST_ASSERT(lookup_entry_index(key, ix, 2, &result) == EC_SUCCESS);
  TEST_ASSERT(result != nullptr);
  TEST_ASSERT(strcmp(result->getStart()->getWord()->getStr(), e1->getWord()->getStr()) == 0);
  TEST_ASSERT(strcmp(result->getStart()->getNext()->getWord()->getStr(), e2->getWord()->getStr()) == 0);
}

void destroy_entry_index(void) { // Test destroy_entry_index function
  entry_list *el;
  entry *e1, *e2, *e3, *e4, *e5, *e6, *e7;
  const word *w1 = new word("hell");
  const word *w2 = new word("help");
  const word *w3 = new word("fall");
  const word *w4 = new word("small");
  const word *w5 = new word("fell");
  const word *w6 = new word("felt");
  const word *w7 = new word("melt");

  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS);

  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w3, &e3) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w4, &e4) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w5, &e5) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w6, &e6) == EC_SUCCESS);
  TEST_ASSERT(create_entry(w7, &e7) == EC_SUCCESS);

  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e3) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e4) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e5) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e6) == EC_SUCCESS);
  TEST_ASSERT(add_entry(el, e7) == EC_SUCCESS);

  tree *ix;
  TEST_ASSERT(build_entry_index(el, MT_HAMMING_DIST, &ix) == EC_SUCCESS);

  TEST_ASSERT(destroy_entry_index(&ix) == EC_SUCCESS);
  TEST_ASSERT(ix == nullptr);
}

TEST_LIST = {
    {"Create Entry", create_entry},
    {"Destroy Entry", destroy_entry},
    {"Create Entry List", create_entry_list},
    {"Get Number Entries", get_number_entries},
    {"Add Entry", add_entry},
    {"Get First", get_first},
    {"Get Next", get_next},
    {"Destroy Entry List", destroy_entry_list},
    {"Build Entry Index", build_entry_index},
    {"Lookup Entry Index", lookup_entry_index},
    {"Destroy Entry Index", destroy_entry_index},
    {NULL, NULL} /* zeroed record marking the end of the list */
};