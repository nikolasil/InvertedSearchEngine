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

  TEST_ASSERT(create_entry_list(&el) == EC_SUCCESS); // test that result is success

  const word *w1 = new word("hell");
  const word *w2 = new word("melt");
  entry *e1, *e2;
  TEST_ASSERT(create_entry(w1, &e1) == EC_SUCCESS); // test that result is success
  TEST_ASSERT(create_entry(w2, &e2) == EC_SUCCESS); // test that result is success

  TEST_ASSERT(add_entry(el, e1) == EC_SUCCESS); // add entry e1 to list
  TEST_ASSERT(add_entry(el, e2) == EC_SUCCESS); // add entry e2 to list
  TEST_ASSERT(get_first(el) == e1);             // check that e1 is the first entry
  TEST_ASSERT(get_next(el, e1) == e2);          // check that e1->next is e2
  TEST_ASSERT(get_next(el, e2) == nullptr);     // check that e2->next is nullptr
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

TEST_LIST = {
    {"Create Entry", create_entry},
    {"Destroy Entry", destroy_entry},
    {"Create Entry List", create_entry_list},
    {"Get Number Entries", get_number_entries},
    {"Add Entry", add_entry},
    {"Get First", get_first},
    {"Get Next", get_next},
    {NULL, NULL} /* zeroed record marking the end of the list */
};