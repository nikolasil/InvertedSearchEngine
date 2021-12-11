#ifndef BK_Tree_H
#define BK_Tree_H

class BK_TreeEdge;
class BK_TreeNode;
class BK_Tree;

// #include "../../Functions/functions.h"
#include "../string/String.h"

class BK_TreeEdge {
private:
  int weight;
  BK_TreeNode *child;
  BK_TreeEdge *next;

public:
  BK_TreeEdge(int w, BK_TreeNode *c);
  ~BK_TreeEdge();

  // Getters
  int getWeight();         // get edge weight
  BK_TreeNode *getChild(); // get edge child
  BK_TreeEdge *getNext();  // get next edge

  // Setters
  void setNext(BK_TreeEdge *next);                       // set next node
  void setWeight(int weight) { this->weight = weight; }; // set edge weight
  void print();
};

class BK_TreeNode {
private:
  String *data;
  BK_TreeEdge *childs;

public:
  BK_TreeNode(String *d);
  ~BK_TreeNode();

  // Getters
  BK_TreeEdge *getFirstChild(); // get first child edge of node
  String *getData();            // get word of node

  // Setters
  void setData(String *data) { this->data = data; }; // set new word of node

  // Utils
  BK_TreeNode *findChild(int w); // Search for a child node that contains the word w
  // void lookup(String *word, int threshold, entry_list **foundWords, int diff); // Lookup word
  void addChild(int w, BK_TreeNode *c); // Add child node
  void print();
};

class BK_Tree {
private:
  BK_TreeNode *root;

public:
  BK_Tree();
  ~BK_Tree();

  // Getters
  BK_TreeNode *getRoot() { return this->root; };

  // Utils
  void print();
  void add(String *word); // add word to BK_Tree
  // void fillTree(const entry_list *list, MatchType type); // fill BK_Tree based from the words of an entry list
  // entry_list *lookup(String *word, int threshold);       // lookup a word in index
};

#endif