#include "MatchTree.h"
#include <cstring>
#include <iostream>

using namespace std;

MatchTree::MatchTree(int maxWords) {
  this->count = 0;
  this->flag = false;
  this->maxWords = maxWords;
  this->root = nullptr;
}
MatchTree::~MatchTree() {}

void MatchTree::insert(String *word) {
  if (this->root == nullptr) {
    this->root = new MatchTreeNode(word);
    this->count++;
    return;
  }
  MatchTreeNode *current = this->root;
  while (current != nullptr) {
    if (!strcmp(word->getStr(), current->getData()->getStr())) {
      return;
    }
    if (!strcmp(word->getStr(), current->getData()->getStr())) {
      if (current->getLeft() == nullptr) {
        current->setLeft(new MatchTreeNode(word));
        this->count++;
        return;
      }
      current = current->getLeft();
    } else {
      if (current->getRight() == nullptr) {
        current->setRight(new MatchTreeNode(word));
        this->count++;
        return;
      }
      current = current->getRight();
    }
  }
}
bool MatchTree::matched() {
  if ((this->count == this->maxWords) && !flag) {
    return this->flag = true; // to avoid return it to the future again
  }
  return false;
}

MatchTreeNode::~MatchTreeNode() {}
MatchTreeNode::MatchTreeNode(String *d) {
  this->data = d;
  this->left = nullptr;
  this->right = nullptr;
}