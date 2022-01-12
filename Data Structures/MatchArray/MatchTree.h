#ifndef MatchTree_H
#define MatchTree_H

#include "../string/String.h"
#include <pthread.h>

class MatchTreeNode {
private:
  String *data;
  MatchTreeNode *left;
  MatchTreeNode *right;

public:
  MatchTreeNode(String *d);
  ~MatchTreeNode();
  // Getters
  String *getData() { return this->data; };
  MatchTreeNode *getLeft() { return this->left; };
  MatchTreeNode *getRight() { return this->right; };
  // Setters
  void setData(String *d) { this->data = d; };
  void setLeft(MatchTreeNode *l) { this->left = l; };
  void setRight(MatchTreeNode *r) { this->right = r; };
  // Utils
  void print();
};

class MatchTree {
private:
  MatchTreeNode *root;
  int maxWords;
  bool flag;
  int count;
  pthread_mutex_t mutex;

public:
  MatchTree(int maxWords);
  ~MatchTree();
  // Getters
  MatchTreeNode *getRoot() { return this->root; };
  int getCount() { return this->count; };
  int getMaxWords() { return this->maxWords; };
  // Setters
  void setRoot(MatchTreeNode *root) { this->root = root; };
  void setCount(int count) { this->count = count; };
  void setMaxWords(int maxWords) { this->maxWords = maxWords; };
  // Utils
  void insert(String *word);
  bool matched();
  void print();
};

#endif