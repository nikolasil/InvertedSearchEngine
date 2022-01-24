#include "BK_Tree.h"
#include "../string/String.h"
#include <cstring>
#include <ctime>
#include <iostream>
#include <random>

using namespace std;

// Tree
BK_Tree::BK_Tree() {
  this->root = nullptr;
  pthread_mutex_init(&this->mutex, NULL);
}

BK_Tree::~BK_Tree() {
  if (this->root != nullptr) {
    delete this->root;
    this->root = nullptr;
  }
}

void BK_Tree::add(String *word, HEInfo *info) {
  pthread_mutex_lock(&this->mutex);
  BK_TreeNode *current = this->root;

  if (current == nullptr) {
    this->root = new BK_TreeNode(word, info);
    pthread_mutex_unlock(&this->mutex);
    return;
  }
  pthread_mutex_unlock(&this->mutex);

  int diff;
  while (true) {
    // Compare word with node data
    if (current->getData()->getSize() == word->getSize())
      diff = word->hammingDistance(current->getData());
    else
      diff = word->editDistance(current->getData()->getStr(), word->getStr(), current->getData()->getSize(), word->getSize());

    if (diff == 0) {
      current->getInfo()->addQuery(info);
      delete word;
      return;
    }
    // Search for child node with equal weight in edge
    BK_TreeNode *childNode = nullptr;
    pthread_mutex_lock(&this->mutex);
    if ((childNode = current->findChild(diff)) == nullptr) {
      current->addChild(diff, new BK_TreeNode(word, info));
      pthread_mutex_unlock(&this->mutex);
      return;
    }
    pthread_mutex_unlock(&this->mutex);
    current = childNode;
  }
}

void BK_Tree::print() {
  if (this->root) {
    this->root->print();
    cout << endl;
  }
}

void BK_Tree::editLookup(String *word, MatchArray *matchArray) {
  if (this->root == nullptr) {
    return;
  }
  int diff = word->editDistance(word->getStr(), this->root->getData()->getStr(), word->getSize(), this->root->getData()->getSize());
  // cout << "Diff between " << word->getStr() << " and  " << this->root->getData()->getStr() << "  is " << diff << " ." << endl;
  for (int i = 1; i <= MAX_THRESHOLD; i++) {
    if (diff <= i) {
      matchArray->update(this->root->getData(), this->root->getInfo(), (unsigned int)i);
      break;
    }
  }
  this->root->editLookup(word, 1, diff, matchArray);
}

void BK_Tree::hammingLookup(String *word, MatchArray *matchArray) {
  if (this->root == nullptr) {
    return;
  }

  int diff = word->hammingDistance(this->root->getData());

  for (int i = 1; i <= MAX_THRESHOLD; i++) {
    if (diff <= i) {
      matchArray->update(this->root->getData(), this->root->getInfo(), (unsigned int)i);
      break;
    }
  }

  this->root->hammingLookup(word, 1, diff, matchArray);
}

// Tree Node
BK_TreeNode::BK_TreeNode(String *d, HEInfo *info) {
  this->data = d;
  this->childs = nullptr;
  this->info = new heInfoList();
  this->info->addQuery(info);
  pthread_mutex_init(&this->mutex, NULL);
}

BK_TreeNode::~BK_TreeNode() {
  if (this->data != nullptr) {
    delete this->data;
    this->data = nullptr;
  }
  if (this->childs != nullptr) {
    delete this->childs;
    this->childs = nullptr;
  }
  if (this->info != nullptr) {
    delete this->info;
    this->info = nullptr;
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
  // pthread_mutex_lock(&this->mutex);

  if (this->childs == nullptr) {
    this->childs = new BK_TreeEdge(w, c);
    this->childs->setNext(nullptr);
    // pthread_mutex_unlock(&this->mutex);
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
    // pthread_mutex_unlock(&this->mutex);
    return;
  }
  // the new edge must be in the last place
  if (current == nullptr) {
    prev->setNext(new BK_TreeEdge(w, c));
    // pthread_mutex_unlock(&this->mutex);
    return;
  }
  // the new edge must be between prev-current
  prev->setNext(new BK_TreeEdge(w, c));
  prev->getNext()->setNext(current);
  // pthread_mutex_unlock(&this->mutex);
  return;
}

void BK_TreeNode::print() {
  cout << "Node : " << this->data->getStr();
  this->info->print();

  if (this->childs != nullptr) {
    this->childs->print();
  }
  cout << endl;
}

void BK_TreeNode::editLookup(String *word, int threshold, int parentDiff, MatchArray *matchArray) {
  BK_TreeNode *child;
  BK_TreeEdge *currentEdge = this->getFirstChild();
  int i;
  int diff;
  while (currentEdge != nullptr) {
    child = currentEdge->getChild();
    // cout << "Child : " << child->getData()->getStr() << endl;
    diff = word->editDistance(word->getStr(), child->getData()->getStr(), word->getSize(), child->getData()->getSize());
    for (i = threshold; i <= MAX_THRESHOLD; i++) {
      if (diff <= i) {
        // cout << "inserting " << child->getData()->getStr() << " with weight " << i << " in matchArray" << endl;
        matchArray->update(child->getData(), child->getInfo(), (unsigned int)i);
        break;
      }
    }

    for (i = threshold; i <= MAX_THRESHOLD; i++) {
      if (currentEdge->getWeight() >= (parentDiff - i) && currentEdge->getWeight() <= (parentDiff + i)) {
        child->editLookup(word, i, diff, matchArray);
        break;
      }
    }
    currentEdge = currentEdge->getNext();
  }
}
void BK_TreeNode::hammingLookup(String *word, int threshold, int parentDiff, MatchArray *matchArray) {
  BK_TreeNode *child;
  BK_TreeEdge *currentEdge = this->getFirstChild();
  int i;
  int diff;

  while (currentEdge != nullptr) {
    child = currentEdge->getChild();
    diff = child->getData()->hammingDistance(word);
    for (i = threshold; i <= MAX_THRESHOLD; i++) {
      if (diff <= i) {
        matchArray->update(child->getData(), child->getInfo(), (unsigned int)i);
        break;
      }
    }
    for (i = threshold; i <= MAX_THRESHOLD; i++) {
      if (currentEdge->getWeight() >= (parentDiff - i) && currentEdge->getWeight() <= (parentDiff + i)) {
        child->hammingLookup(word, i, diff, matchArray);
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
    this->child = nullptr;
  }
  if (this->next != nullptr) {
    delete this->next;
    this->next = nullptr;
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
  cout << "Edge : " << this->weight << " " << this->child->getData()->getStr() << endl;
  if (this->next != nullptr) {
    this->next->print();
  }
  this->child->print();
}
