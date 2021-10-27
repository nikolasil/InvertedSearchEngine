#ifndef TREE_H
#define TREE_H

#include "../string/String.h"

class tree_edge {
private:
  int weight;
  tree_node *child;

  tree_edge *next_edge;

public:
  tree_edge(int w, tree_node *c);
};

class tree_node {
private:
  String *data;
  tree_edge *childs;

public:
  tree_node(String *d);
  void addChild(int w, tree_node *c);
};

class tree {
private:
  tree_node *root;

public:
  void add(int w);
};

#endif