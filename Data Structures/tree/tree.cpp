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
    cout << "root : " << word->getStr() << endl;
    this->root = new tree_node(word);
    return;
  }
  while (true) {
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
tree_node::tree_node(String *d) {
  this->data = d;
  for (int i = 0; i < 30; i++) {
    this->childs[i] = nullptr;
  }
}

tree_node::~tree_node() {
  delete this->data;
  delete this->childs;
}
String *tree_node::getData() { return this->data; }
tree_node *tree_node::findChild(int w) {
  if (this->childs[w - 1] != nullptr) {
    return this->childs[w - 1]->getChild();
  }
  return nullptr;
}
void tree_node::addChild(int w, tree_node *c) {
  this->childs[w - 1] = new tree_edge(w, c);
}

void tree_node::print() {

  cout << endl;
  cout << this->data->getStr() << " ";
  for (int i = 0; i < 30; i++) {
    if (this->childs[i] != nullptr) {
      this->childs[i]->print();
    }
  }
  for (int i = 0; i < 30; i++) {
    if (this->childs[i] != nullptr) {
      this->childs[i]->printChild();
    }
  }
}
// Tree Edge

tree_edge::tree_edge(int w, tree_node *c) {
  this->weight = w;
  this->child = c;
}
tree_edge::~tree_edge() { delete this->child; }

int tree_edge::getWeight() { return this->weight; }

tree_node *tree_edge::getChild() { return this->child; }

void tree_edge::print() {
  cout << "[" << this->weight << "->" << this->child->getData()->getStr()
       << "], ";
}
void tree_edge::printChild() { this->child->print(); }