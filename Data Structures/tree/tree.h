#ifndef TREE_H
#define TREE_H

class tree_edge;
class tree_node;
class tree;

#include "../../Functions/functions.h"
#include "../string/String.h"

class tree_edge {
private:
  int weight;
  tree_node *child;
  tree_edge *next;

public:
  tree_edge(int w, tree_node *c);
  ~tree_edge();
  int getWeight();
  void setNext(tree_edge *next);
  tree_node *getChild();
  tree_edge *getNext();
  void print();
};

class tree_node {
private:
  String *data;
  tree_edge *childs;

public:
  tree_node(String *d);
  ~tree_node();
  void addChild(int w, tree_node *c);
  tree_edge *getFirstChild();
  tree_node *findChild(int w);
  String *getData();
  void lookup(String *word, int threshold, entry_list **foundWords);
  void print();
};

class tree {
private:
  tree_node *root;

public:
  tree();
  ~tree();
  void add(String *word);
  tree_node *getRoot() { return this->root; };
  void print();
  void fillLinkedList(const entry_list *list, MatchType type);
  entry_list *lookup(String *word, int threshold);
};

#endif