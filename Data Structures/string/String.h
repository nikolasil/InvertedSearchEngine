#ifndef STRING_H
#define STRING_H

class String {
private:
  char *str;

public:
  String(const char *string);
  String(const String *string);
  ~String();
  // Getters
  char *getStr() const { return this->str; };
  // Setters
  void setStr(char *string) { this->str = string; };
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