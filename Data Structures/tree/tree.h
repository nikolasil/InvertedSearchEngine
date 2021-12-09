#ifndef TREE_H
#define TREE_H

class tree_edge;
class tree_node;
class tree;

// #include "../../Functions/functions.h"
#include "../string/String.h"

class tree_edge {
private:
  int weight;
  tree_node *child;
  tree_edge *next;

public:
  tree_edge(int w, tree_node *c);
  ~tree_edge();

  // Getters
  int getWeight();       // get edge weight
  tree_node *getChild(); // get edge child
  tree_edge *getNext();  // get next edge

  // Setters
  void setNext(tree_edge *next);                         // set next node
  void setWeight(int weight) { this->weight = weight; }; // set edge weight
  void print();
};

class tree_node {
private:
  String *data;
  tree_edge *childs;

public:
  tree_node(String *d);
  ~tree_node();

  // Getters
  tree_edge *getFirstChild(); // get first child edge of node
  String *getData();          // get word of node

  // Setters
  void setData(String *data) { this->data = data; }; // set new word of node

  // Utils
  tree_node *findChild(int w); // Search for a child node that contains the word w
  // void lookup(String *word, int threshold, entry_list **foundWords, int diff); // Lookup word
  void addChild(int w, tree_node *c); // Add child node
  void print();
};

class tree {
private:
  tree_node *root;

public:
  tree();
  ~tree();

  // Getters
  tree_node *getRoot() { return this->root; };

  // Utils
  void print();
  void add(String *word); // add word to tree
  // void fillTree(const entry_list *list, MatchType type); // fill tree based from the words of an entry list
  // entry_list *lookup(String *word, int threshold);       // lookup a word in index
};

#endif