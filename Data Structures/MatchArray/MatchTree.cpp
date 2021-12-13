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

void MatchTree::print() {
  if (this->root != nullptr) {
    cout << "Count " << this->count << endl;
    cout << "maxWords " << this->maxWords << endl;
    cout << "flag " << this->flag << endl;
    this->root->print();
  }
}
void MatchTree::insert(String *word) {
  if (this->root == nullptr) {
    this->root = new MatchTreeNode(word);
    this->count++;
    return;
  }
  MatchTreeNode *current = this->root;
  while (current != nullptr) {
    if (word->exactMatch(current->getData())) {
      return;
    }
    if (word->compare(current->getData()) < 0) {
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

void MatchTreeNode::print() {
  cout << "MatchTreeNode " << this->data->getStr() << endl;
  if (this->left != nullptr) {
    this->left->print();
  }
  if (this->right != nullptr) {
    this->right->print();
  }
}