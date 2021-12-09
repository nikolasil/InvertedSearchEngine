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
void String::print() { cout << this->str; }

String::~String() { delete[] this->str; }

char *String::getStr() const {
  return this->str;
}