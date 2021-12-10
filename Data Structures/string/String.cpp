#include "String.h"
#include <cstring>
#include <iostream>

using namespace std;

String::String(const char *string) {
  this->str = new char[strlen(string)];
  this->str[strlen(string)] = '\0';
  strcpy(this->str, string);
}
String::String(const String *s) {
  this->str = new char[strlen(s->getStr()) + 1];
  this->str[strlen(s->getStr())] = '\0';
  strcpy(this->str, s->getStr());
}
String::~String() { delete[] this->str; }

bool String::exactMatch(String *s) {
  char *s1 = this->str;
  char *s2 = s->getStr();
  while (*s1 == *s2 && *s1 && *s2) {
    s1++;
    s2++;
  }
  return *s1 == *s2;
}

int String::hammingDistance(String *s) {
  char *str1 = this->getStr();
  char *str2 = s->getStr();
  int count = 0;
  for (int i = 0; str1[i] != '\0'; i++) {
    if (str1[i] != str2[i])
      count++;
  }
  return count;
}

int String::editDistance(String *s) {
  return 0;
}

void String::print() { cout << this->str; }
