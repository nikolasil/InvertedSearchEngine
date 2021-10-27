#ifndef TREE_H
#define TREE_H

#include "../string/String.h"

class tree_edge;
class tree_node;
class tree_edge {
private:
  int weight;
  tree_node *child;

  tree_edge *next_edge;

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
  tree_node *findChild(int w);
  String *getData();
  void print();
};

class tree {
private:
  tree_node *root;

public:
  tree();
  ~tree();
  void add(String *word);
  void print();
};

#endif