#include "BK_Tree.h"
#include "../string/String.h"
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

// Tree
BK_Tree::BK_Tree() { this->root = nullptr; }

BK_Tree::~BK_Tree() {
  if (this->root != nullptr) {
    delete this->root;
  }
}

void BK_Tree::add(String *word, HEInfo info) {
  BK_TreeNode *current = this->root;

  if (current == nullptr) {
    // cout << "root : " << word->getStr() << endl;
    this->root = new BK_TreeNode(word, info);
    return;
  }
  while (true) {
    // Compare word with node data
    int diff = word->hammingDistance(current->getData());
    if (diff == 0) {
      // cout << "same : " << word->getStr() << endl;
      current->getInfo()->addQuery(info);
      return;
    }
    // cout << "Difference is " << diff << " -> " << word->getStr() << endl;
    // Search for child node with equal weight in edge
    BK_TreeNode *childNode = nullptr;
    if ((childNode = current->findChild(diff)) == nullptr) {

      current->addChild(diff, new BK_TreeNode(word, info));
      return;
    }
    current = childNode;
  }
}

void BK_Tree::print() {
  if (this->root)
    this->root->print();
  cout << endl;
}

heInfoList *BK_Tree::lookup(String *word) {
  heInfoList *foundWords = new heInfoList();
  if (this->root == nullptr) {
    return foundWords;
  }
  int diff = word->hammingDistance(this->root->getData());
  for (int i = 1; i <= 3; i++) {
    if (diff <= i) {
      const String *w = new String(this->root->getData());
      cout << "key ";
      word->print();
      cout << endl;
      cout << "parent ";
      this->root->getData()->print();
      cout << endl;
      foundWords->mergeLists(this->root->getInfo(), i);
      break;
    }
  }

  this->root->lookup(word, 1, &foundWords, diff);
  if (foundWords->getCount() == 0) {
    delete foundWords;
    return nullptr;
  }
  return foundWords;
}

// Tree Node
BK_TreeNode::BK_TreeNode(String *d, HEInfo info) {
  this->data = d;
  this->childs = nullptr;
  this->info = new heInfoList();
  this->info->addQuery(info);
}

BK_TreeNode::~BK_TreeNode() {
  if (this->data != nullptr) {
    delete this->data;
  }
  if (this->childs != nullptr) {
    delete this->childs;
  }
}

String *BK_TreeNode::getData() {
  return this->data;
}

BK_TreeEdge *BK_TreeNode::getFirstChild() {

  return this->childs;
}

BK_TreeNode *BK_TreeNode::findChild(int w) {
  BK_TreeEdge *currentEdge = this->childs;
  while (currentEdge != nullptr) {
    if (currentEdge->getWeight() == w) { // check for weight equivalence
      return currentEdge->getChild();
    }
    currentEdge = currentEdge->getNext();
  }
  return nullptr; // no weight equivalence
}

void BK_TreeNode::addChild(int w, BK_TreeNode *c) {
  // the edge list was empty
  if (this->childs == nullptr) {
    this->childs = new BK_TreeEdge(w, c);
    this->childs->setNext(nullptr);
    return;
  }

  BK_TreeEdge *prev = nullptr;
  BK_TreeEdge *current = this->childs;

  while (current != nullptr && current->getWeight() < w) {
    prev = current;
    current = current->getNext();
  }

  // the new edge must be in the first place
  if (prev == nullptr) {
    this->childs = new BK_TreeEdge(w, c);
    this->childs->setNext(current);
    return;
  }
  // the new edge must be in the last place
  if (current == nullptr) {
    prev->setNext(new BK_TreeEdge(w, c));
    return;
  }
  // the new edge must be between prev-current
  prev->setNext(new BK_TreeEdge(w, c));
  prev->getNext()->setNext(current);
  return;
}

void BK_TreeNode::print() {
  cout << "Node : " << this->data->getStr();
  this->info->print();
  cout << endl;

  if (this->childs != nullptr) {
    this->childs->print();
  }
  cout << endl;
}

void BK_TreeNode::lookup(String *word, int initialThreshold, heInfoList **foundWords, int diff) {
  BK_TreeNode *child;
  BK_TreeEdge *currentEdge = this->getFirstChild();
  while (currentEdge != nullptr) {
    int threshold = initialThreshold;
    child = currentEdge->getChild();
    diff = child->getData()->hammingDistance(word);
    for (int i = threshold; i <= 3; i++) {
      if (diff <= threshold) {
        const String *w = new String(child->getData());
        (*foundWords)->mergeLists(this->getInfo(), i);
        break;
      }
    }

    for (int i = threshold; i <= 3; i++) {
      if (threshold < 0 && diff <= (threshold / 2)) {
        child->lookup(word, threshold, foundWords, diff);
        break;
      }
    }

    currentEdge = currentEdge->getNext();
  }
}
// Tree Edge

BK_TreeEdge::BK_TreeEdge(int w, BK_TreeNode *c) {
  this->weight = w;
  this->child = c;
  this->next = nullptr;
}
BK_TreeEdge::~BK_TreeEdge() {
  if (this->child != nullptr) {
    delete this->child;
  }
  if (this->next != nullptr) {
    delete this->next;
  }
}

int BK_TreeEdge::getWeight() { return this->weight; }

BK_TreeEdge *BK_TreeEdge::getNext() {
  return this->next;
}

void BK_TreeEdge::setNext(BK_TreeEdge *next) {
  this->next = next;
}

BK_TreeNode *BK_TreeEdge::getChild() { return this->child; }

void BK_TreeEdge::print() {
  if (this->next != nullptr) {
    this->next->print();
  }
  this->child->print();
}
