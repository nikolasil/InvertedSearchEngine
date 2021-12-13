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
  this->root->print();
  cout << endl;
}

// void BK_Tree::fillTree(const entry_list *list, MatchType type) {
//   entry *current = list->getStart();
//   while (current) {
//     if (type == MT_HAMMING_DIST) {
//       this->add(new String(current->getWord()));
//     }
//     current = current->getNext();
//   }
// }

// entry_list *BK_Tree::lookup(String *word, int threshold) {
//   entry_list *foundWords = new entry_list();
//   if (this->root == nullptr) {
//     return foundWords;
//   }
//   int diff = hammingDistance(word, this->root->getData());
//   if (diff <= threshold) {
//     const String *w = new String(this->root->getData());
//     foundWords->addEntry(new entry(w, nullptr));
//     // cout << "Added " << this->root->getData()->getStr() << " with diff " << diff
//     //      << endl;
//   }

//   this->root->lookup(word, threshold, &foundWords, diff);
//   return foundWords;
// }

// Tree Node
BK_TreeNode::BK_TreeNode(String *d, HEInfo info) {
  this->data = d;
  this->childs = nullptr;
  this->info = info;
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

  cout << endl;
  cout << endl;
  cout << this->data->getStr() << " ";
  if (this->childs != nullptr) {
    this->childs->print();
  }
}

// void BK_TreeNode::lookup(String *word, int threshold, entry_list **foundWords, int diff) {
//   BK_TreeNode *child;
//   // int diff = hammingDistance(word, this->getData());
//   int min = diff - threshold;
//   int max = diff + threshold;
//   // cout << "Node " << this->getData()->getStr() << " with diff=" << diff
//   //      << ",space=[" << min << "," << max << "]" << endl;

//   BK_TreeEdge *currentEdge = this->getFirstChild();

//   while (currentEdge != nullptr) {
//     child = currentEdge->getChild();
//     diff = hammingDistance(child->getData(), word);
//     // cout << "Child " << child->getData()->getStr()
//     //      << " of node:" << this->getData()->getStr() << endl;
//     if (diff <= threshold) {
//       const String *w = new String(child->getData());
//       (*foundWords)->addEntry(new entry(w, nullptr));
//       // cout << "   diff=" << diff << " from " << word->getStr()
//       //      << " | added to found words" << endl;
//     } else {
//       // cout << "   diff=" << diff << " from " << word->getStr()
//       //      << " | NOT added to found words" << endl;
//     }
//     if (diff >= min && diff <= max) {
//       // cout << "   diff was in the space=[" << min << "," << max
//       //      << "] | calling subtree" << endl;
//       child->lookup(word, threshold, foundWords, diff);
//     } else {
//       // cout << "   diff was NOT in the space=[" << min << "," << max
//       //      << "] | NOT calling subtree" << endl;
//     }
//     currentEdge = currentEdge->getNext();
//   }
// }
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
  cout << "[" << this->weight << "->" << this->child->getData()->getStr()
       << "], ";
  if (this->next != nullptr) {
    this->next->print();
  }
  // cout << endl;
  this->child->print();
}
