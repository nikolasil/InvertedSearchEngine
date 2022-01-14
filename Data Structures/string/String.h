#ifndef STRING_H
#define STRING_H
#include <pthread.h>
class String {
private:
  char *str;
  int size;

public:
  String(const char *string);
  String(String *string);
  ~String();
  // Getters
  char *getStr() const { return this->str; };
  int getSize() const { return this->size; };
  // Setters
  void setStr(char *string) { this->str = string; };
  void setSize(int size) { this->size = size; };
  // Distances
  bool exactMatch(String *s);                             // Exact match
  int hammingDistance(String *s);                         // same size words
  int editDistance(char *str1, char *str2, int m, int n); // different size words
  int compare(String *s);                                 // compare two strings
  // Methods
  void print();
};

typedef String word;

#endif