#include <iostream>

#include "Data Structures/entry/entry.h"
#include "Data Structures/entry/entry_list.h"
#include "Data Structures/linkedList/linkedList.h"
#include "Data Structures/tree/tree.h"
using namespace std;

int main(int argc, char *argv[]) {
  entry_list *testList = new entry_list();
  testList->addEntry(new entry((const word *)new word("nikolas"), nullptr));
  testList->addEntry(new entry((const word *)new word("mixalis"), nullptr));
  testList->addEntry(new entry((const word *)new word("project"), nullptr));

  // testList->print();
  // tree *myTree = new tree();
  // myTree->add(new String("hell"));
  // myTree->add(new String("help"));
  // myTree->add(new String("fall"));
  // myTree->add(new String("felt"));
  // myTree->add(new String("fell"));
  // myTree->add(new String("small"));
  // myTree->add(new String("melt"));
  // myTree->print();

  linkedList *list = testList->generateLinkedList();
  list->print();

  return 0;
}