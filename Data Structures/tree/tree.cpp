#include "tree.h"
#include "../linkedList/linkedList.h"
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

void tree::fillLinkedList(linkedList *list, MatchType type) {
  listNode *current = list->getHead();
  while (current) {
    if (type == MT_HAMMING_DIST) {
      this->add((String *)current->getWord());
    }
    current = current->getNext();
  }
}

entry_list *tree::lookup(String *word, int threshold) {
  entry_list *foundWords = new entry_list();
  entry_list **foundWordsPtr = &foundWords;
  if (this->root == nullptr) {
    return foundWords;
  }
  int diff = hammingDistance(word, this->root->getData());
  if (diff <= threshold) {
    foundWords->addEntry(new entry(this->root->getData(), nullptr));
    cout << "Added " << this->root->getData()->getStr() << " with diff " << diff
         << endl;
  }

  this->root->lookup(word, threshold, foundWordsPtr);
  return foundWords;
}

// Tree Node
tree_node::tree_node(String *d) {
  this->data = d;
  for (int i = 0; i < MAX_WORD_LENGTH; i++) {
    this->childs[i] = nullptr;
  }
}

tree_node::~tree_node() {
  delete this->data;
  for (int i = 0; i < MAX_WORD_LENGTH; i++) {
    if (this->childs[i] != nullptr) {
      delete this->childs[i];
    }
  }
}
String *tree_node::getData() { return this->data; }
tree_node *tree_node::findChild(int w) {
  if (w > 31 || w <= 0)
    return nullptr;
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
  for (int i = 0; i < MAX_WORD_LENGTH; i++) {
    if (this->childs[i] != nullptr) {
      this->childs[i]->print();
    }
  }
  for (int i = 0; i < MAX_WORD_LENGTH; i++) {
    if (this->childs[i] != nullptr) {
      this->childs[i]->printChild();
    }
  }
}

void tree_node::lookup(String *word, int threshold, entry_list **foundWords) {
  tree_node *child;
  int diff = hammingDistance(word, this->getData());
  int min = diff - threshold;
  int max = diff + threshold;
  cout << "Node " << this->getData()->getStr() << " with diff=" << diff
       << ",space=[" << min << "," << max << "]" << endl;
  for (int i = 0; i < MAX_WORD_LENGTH; i++) {
    child = this->findChild(i);
    if (child != nullptr) {
      diff = hammingDistance(child->getData(), word);
      cout << "Child " << child->getData()->getStr()
           << " of node:" << this->getData()->getStr() << endl;
      if (diff <= threshold) {
        (*foundWords)->addEntry(new entry(child->getData(), nullptr));
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
