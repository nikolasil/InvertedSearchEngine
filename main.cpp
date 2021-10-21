#include <iostream>

#include "Data Structures/entry_list.h"
#include "Data Structures/entry.h"

using namespace std;

int main(int argc, char *argv[]) {
  entry_list *testList = new entry_list();
  testList->addEntry(new entry(new word("nikolas")));
  testList->addEntry(new entry(new word("mixalis")));
  testList->addEntry(new entry(new word("ioanidis")));
  testList->print();
  return 0;
}