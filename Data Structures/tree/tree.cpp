#include "tree.h"
#include "../entry/entry.h"
#include "../linkedList/linkedList.h"
#include "../utils/approximateMatching.h"
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

// Tree
tree::tree() { this->root = nullptr; }

tree::~tree() {
  if (this->root != nullptr) {
    delete this->root;
  }
}

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

    // cout << "Difference is " << diff << " -> " << word->getStr() << endl;
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

void tree::fillLinkedList(const entry_list *list, MatchType type) {
  entry *current = list->getStart();
  while (current) {
    if (type == MT_HAMMING_DIST) {
      this->add((String *)current->getWord());
    }
    current = current->getNext();
  }
}

entry_list *tree::lookup(String *word, int threshold) {
  entry_list *foundWords = new entry_list();
  if (this->root == nullptr) {
    return foundWords;
  }
  int diff = hammingDistance(word, this->root->getData());
  if (diff <= threshold) {
    const String *w = new String(this->root->getData());
    foundWords->addEntry(new entry(w, nullptr));
    cout << "Added " << this->root->getData()->getStr() << " with diff " << diff
         << endl;
  }

  this->root->lookup(word, threshold, &foundWords);
  return foundWords;
}

// Tree Node
tree_node::tree_node(String *d) {
  this->data = d;
  this->childs = nullptr;
}

tree_node::~tree_node() {
  // if (this->data != nullptr) {
  //   delete this->data;
  // }
  if (this->childs != nullptr) {
    delete this->childs;
  }
}

String *tree_node::getData() {
  return this->data;
}

tree_edge *tree_node::getFirstChild() {

  return this->childs;
}

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

void tree_node::lookup(String *word, int threshold, entry_list **foundWords) {
  tree_node *child;
  int diff = hammingDistance(word, this->getData());
  int min = diff - threshold;
  int max = diff + threshold;
  cout << "Node " << this->getData()->getStr() << " with diff=" << diff
       << ",space=[" << min << "," << max << "]" << endl;

  tree_edge *currentEdge = this->getFirstChild();

  while (currentEdge != nullptr) {
    child = currentEdge->getChild();
    diff = hammingDistance(child->getData(), word);
    cout << "Child " << child->getData()->getStr()
         << " of node:" << this->getData()->getStr() << endl;
    if (diff <= threshold) {
      const String *w = new String(child->getData());
      (*foundWords)->addEntry(new entry(w, nullptr));
      cout << "   diff=" << diff << " from " << word->getStr()
           << " | added to found words" << endl;
    } else {
      cout << "   diff=" << diff << " from " << word->getStr()
           << " | NOT added to found words" << endl;
    }
    if (diff >= min && diff <= max) {
      cout << "   diff was in the space=[" << min << "," << max
           << "] | calling subtree" << endl;
      child->lookup(word, threshold, foundWords);
    } else {
      cout << "   diff was NOT in the space=[" << min << "," << max
           << "] | NOT calling subtree" << endl;
    }
    currentEdge = currentEdge->getNext();
  }
}
// Tree Edge

tree_edge::tree_edge(int w, tree_node *c) {
  this->weight = w;
  this->child = c;
  this->next = nullptr;
}
tree_edge::~tree_edge() {
  if (this->child != nullptr) {
    delete this->child;
  }
  if (this->next != nullptr) {
    delete this->next;
  }
}

int tree_edge::getWeight() { return this->weight; }

tree_edge *tree_edge::getNext() {
  return this->next;
}

void tree_edge::setNext(tree_edge *next) {
  this->next = next;
}

tree_node *tree_edge::getChild() { return this->child; }

void tree_edge::print() {

  tree_edge *current = this;
  cout << "[" << this->weight << "->" << this->child->getData()->getStr()
       << "], ";
  if (this->next != nullptr) {
    this->next->print();
  }
  // cout << endl;
  this->child->print();
}
