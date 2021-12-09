#include <ctime>
#include <iostream>

#include "Data Structures/hashTable/hashTable.h"
#include "Data Structures/string/String.h"
#include "Data Structures/utils/exactMatching.h"
using namespace std;

int main(int argc, char *argv[]) {

  String *w1 = new String("hell");
  String *w2 = new String("help");
  String *w3 = new String("fall");
  String *w4 = new String("small");
  String *w5 = new String("fell");
  String *w6 = new String("felt");
  String *w7 = new String("melt");
  String *w8 = new String("melt");

  HashTable *ht = new HashTable();
  ht->insert(w1);
  ht->insert(w2);
  ht->insert(w3);
  ht->insert(w4);
  ht->insert(w5);
  ht->insert(w6);
  ht->insert(w7);

  ht->print();

  cout << "Exact Matching : " << exactMatch(w7->getStr(), w8->getStr()) << endl;
  cout << "Exact Matching : " << exactMatch(w6->getStr(), w7->getStr()) << endl;
  return 0;
}