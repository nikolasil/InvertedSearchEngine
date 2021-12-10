#ifndef queryList_H
#define queryList_H

class queryNode {
private:
  int id;
  queryNode *next;

public:
  queryNode(int id);
  ~queryNode();
  //  Getters
  int getId() const { return this->id; };
  queryNode *getNext(queryNode *next) const { return this->next; };
  // Setters
  void setId(int id) { this->id = id; };
  void setNext(queryNode *next) { this->next = next; };
  void print();
};

class queryList {
private:
  queryNode *head;
  queryNode *last;
  int count;

public:
  queryList();
  ~queryList();
  // Getters
  queryNode *getHead() const { return this->head; };
  queryNode *getLast() const { return this->last; };
  int getCount() const { return this->count; };
  // Setters
  void setHead(queryNode *head) { this->head = head; };
  void setLast(queryNode *last) { this->last = last; };
  void setCount(int count) { this->count = count; };
  // Methods
  void addQuery(int id);
  void print();
};

#endif