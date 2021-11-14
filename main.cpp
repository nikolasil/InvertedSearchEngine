#include <iostream>

#include "Data Structures/entry/entry.h"
#include "Data Structures/entry/entry_list.h"
#include "Data Structures/linkedList/linkedList.h"
#include "Data Structures/tree/tree.h"
#include "Functions/functions.h"
#include <ctime>

using namespace std;

int main(int argc, char *argv[]) {
  entry_list *el;
  entry *e1, *e2, *e3, *e4, *e5, *e6, *e7;
  const word *w1 = new word("hell");
  const word *w2 = new word("help");
  const word *w3 = new word("fall");
  const word *w4 = new word("small");
  const word *w5 = new word("fell");
  const word *w6 = new word("felt");
  const word *w7 = new word("melt");

  create_entry_list(&el);

  create_entry(w1, &e1);
  create_entry(w2, &e2);
  create_entry(w3, &e3);
  create_entry(w4, &e4);
  create_entry(w5, &e5);
  create_entry(w6, &e6);
  create_entry(w7, &e7);

  add_entry(el, e1);
  add_entry(el, e2);
  add_entry(el, e3);
  add_entry(el, e4);
  add_entry(el, e5);
  add_entry(el, e6);
  add_entry(el, e7);
  cout << "-- entry_list --" << endl;
  el->print();

  tree *ix;
  build_entry_index(el, MT_HAMMING_DIST, &ix);

  cout << "-- index --" << endl;
  ix->print();

  cout << "-- started lookup --" << endl;
  entry_list *result;
  const word key("henn");

  clock_t begin = clock(); // starting timer
  lookup_entry_index(key, ix, 2, &result);
  clock_t end = clock(); // stoping timer

  // Printing results
  cout << "-- lookup result --" << endl;
  result->print();

  cout << "Lookup took: " << (double)(end - begin) / CLOCKS_PER_SEC << " secs" << endl;
  destroy_entry_index(ix);
  // Cleanup
  delete el;
  delete result;
  return 0;
}