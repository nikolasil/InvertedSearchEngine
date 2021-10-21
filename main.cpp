#include <iostream>

#include "Data Structures/entry.h"
#include "Data Structures/entry_list.h"

using namespace std;

int main(int argc, char *argv[]) {
  entry_list *testList = new entry_list();
  testList->addEntry(new entry((const word *)new word("nikolas"), nullptr));
  testList->addEntry(new entry((const word *)new word("mixalis"), nullptr));
  testList->addEntry(new entry((const word *)new word("ioanidis"), nullptr));
  testList->print();
  return 0;
}