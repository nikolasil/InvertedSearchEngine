#include <iostream>

#include "Data Structures/entry/entry.h"
#include "Data Structures/entry/entry_list.h"
#include "Data Structures/linkedList/linkedList.h"
#include "Data Structures/tree/tree.h"
#include "Functions/functions.h"

using namespace std;

int main(int argc, char *argv[]) {
  // entry_list *testList = new entry_list();
  // testList->addEntry(new entry((const word *)new word("nikolas"), nullptr));
  // testList->addEntry(new entry((const word *)new word("mixalis"), nullptr));
  // testList->addEntry(new entry((const word *)new word("project"), nullptr));

  entry_list *el;
  entry_list **elPtr = &el;
  create_entry_list(elPtr);
  entry *e1, *e2, *e3, *e4, *e5, *e6, *e7;
  entry **e1Ptr = &e1;
  entry **e2Ptr = &e2;
  entry **e3Ptr = &e3;
  entry **e4Ptr = &e4;
  entry **e5Ptr = &e5;
  entry **e6Ptr = &e6;
  entry **e7Ptr = &e7;

  const word *w1 = new word("hell");
  const word *w2 = new word("help");
  const word *w3 = new word("fall");
  const word *w4 = new word("small");
  const word *w5 = new word("fell");
  const word *w6 = new word("felt");
  const word *w7 = new word("melt");

  create_entry(w1, e1Ptr);
  create_entry(w2, e2Ptr);
  create_entry(w3, e3Ptr);
  create_entry(w4, e4Ptr);
  create_entry(w5, e5Ptr);
  create_entry(w6, e6Ptr);
  create_entry(w7, e7Ptr);

  add_entry(elPtr, (const entry **)e1Ptr);
  add_entry(elPtr, (const entry **)e2Ptr);
  add_entry(elPtr, (const entry **)e3Ptr);
  add_entry(elPtr, (const entry **)e4Ptr);
  add_entry(elPtr, (const entry **)e5Ptr);
  add_entry(elPtr, (const entry **)e6Ptr);
  add_entry(elPtr, (const entry **)e7Ptr);

  el->print();

  tree *ix;
  tree **ixPtr = &ix;
  build_entry_index((const entry_list **)elPtr, MT_HAMMING_DIST, ixPtr);

  ix->print();

  entry_list *result;
  entry_list **resultPtr = &result;
  const word key("henn");
  lookup_entry_index(key, ix, 2, resultPtr);
  result->print();
  delete el;
  return 0;
}