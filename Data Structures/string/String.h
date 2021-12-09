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
  bool exactMatch(String *s); // Exact match
  int hammingDist(String *s); // same size words
  int editDist(String *s);    // different size words
  // Methods
  void print();
};

typedef String word;

#endif