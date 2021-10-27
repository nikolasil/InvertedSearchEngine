#include "tree.h"
#include <iostream>

using namespace std;

tree_edge::tree_edge(int w, tree_node *c) {
  this->weight = w;
  this->child = c;
}

tree_node::tree_node(String *d) { this->data = d }

void tree_node::addChild(int w, tree_node *c) {
  // the edge list was empty
  if (this->childs == nullptr) {
    this->childs = new tree_edge(w, c);
    this->childs->setNext(nullptr);
    return;
  }

  tree_edge *prev = nullptr;
  tree_edge *current = this->childs;

  while (current != nullptr && current->getWeight() < w) {
    prev = current;
    current = current->getNext();
  }

  // the new edge must be in the first place
  if (prev == nullptr) {
    this->childs = new tree_edge(w, c);
    this->childs->setNext(current);
    return;
  }
  // the new edge must be in the last place
  if (current == nullptr) {
    prev->setNext(new tree_edge(w, c));
    return;
  }
  // the new edge must be between prev-current
  prev->setNext(new tree_edge(w, c));
  prev->getNext()->setNext(current);
  return;
}