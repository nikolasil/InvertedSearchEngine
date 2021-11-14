#ifndef STRING_H
#define STRING_H

class String {
private:
  char *str;

public:
  String(const char *string);
  String(const String *string);
  ~String();
  void print();
  char *getStr() const;
};

#endif