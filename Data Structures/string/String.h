#ifndef STRING_H
#define STRING_H

class String {
private:
  char *str;

public:
  String();
  String(const char *string);
  ~String();
};

#endif