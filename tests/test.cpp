#include "../Data Structures/entry/entry.h"
#include "../Functions/functions.h"
#include "acutest.h"
#include <cstring>

void create_entry(void) {
  const word *w1 = new word("hell");

  entry *e1;

  ErrorCode result = create_entry(w1, &e1);
  TEST_ASSERT(e1 != nullptr);                                // test that entry exists (has been created)
  TEST_ASSERT(e1->getWord() != nullptr);                     // test that word exists
  TEST_ASSERT(strcmp(e1->getWord()->getStr(), "hell") == 0); // test that word has not been changed
  TEST_ASSERT(w1 != nullptr);                                // test that w1 still exists
  TEST_ASSERT(result == EC_SUCCESS);                         // test that result is success
}

void destroy_entry(void) {
  const word *w1 = new word("hell");

  entry *e1;

  create_entry(w1, &e1);

  ErrorCode result = destroy_entry(&e1);

  TEST_ASSERT(e1 == nullptr); // test that entry doesn't exist

  TEST_ASSERT(result == EC_SUCCESS); // test that result is success
}

TEST_LIST = {
    {"Create Entry", create_entry},
    {"Destroy Entry", destroy_entry},
    {NULL, NULL} /* zeroed record marking the end of the list */
};