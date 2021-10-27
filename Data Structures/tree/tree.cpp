#include "tree.h"
#include "../string/String.h"
#include "../utils/approximateMatching.h"
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

// Tree
tree::tree() { this->root = nullptr; }

tree::~tree() { delete this->root; }

void tree::add(String *word) {
  tree_node *current = this->root;

  if (current == nullptr) {
    this->root = new tree_node(word);
    return;
  }
  while (1) {
    // Compare word with node data
    int diff = hammingDistance(word, current->getData());

    cout << "Difference is " << diff << " -> " << word->getStr() << endl;
    // Search for child node with equal weight in edge
    tree_node *childNode = nullptr;
    if ((childNode = current->findChild(diff)) == nullptr) {
      current->addChild(diff, new tree_node(word));
      return;
    }
    current = childNode;
  }
}

void tree::print() {
  this->root->print();
  cout << endl;
}

// Tree Node
tree_node::tree_node(String *d) { this->data = d; }

tree_node::~tree_node() {
  delete this->data;
  delete this->childs;
}
String *tree_node::getData() { return this->data; }
tree_node *tree_node::findChild(int w) {
  tree_edge *currentEdge = this->childs;
  while (currentEdge != nullptr) {
    if (currentEdge->getWeight() == w) { // check for weight equivalence
      return currentEdge->getChild();
    }
    currentEdge = currentEdge->getNext();
  }
  return nullptr; // no weight equivalence
}
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

void tree_node::print() {

  cout << endl;
  cout << endl;
  cout << this->data->getStr() << " ";
  if (this->childs != nullptr) {
    this->childs->print();
  }
}
// Tree Edge

tree_edge::tree_edge(int w, tree_node *c) {
  this->weight = w;
  this->child = c;
}
tree_edge::~tree_edge() {
  delete this->next_edge;
  delete this->child;
}

int tree_edge::getWeight() { return this->weight; }

tree_edge *tree_edge::getNext() { return this->next_edge; }

void tree_edge::setNext(tree_edge *next) { this->next_edge = next; }

tree_node *tree_edge::getChild() { return this->child; }

void tree_edge::print() {

  tree_edge *current = this;
  cout << "[" << this->weight << "->" << this->child->getData()->getStr()
       << "], ";
  if (this->next_edge != nullptr) {
    this->next_edge->print();
  }
  // cout << endl;
  this->child->print();
}