#include "String.h"
#include <cstring>
#include <iostream>

using namespace std;

String::String(const char *string) {
  this->str = new char[strlen(string) + 1];
  this->str[strlen(string)] = '\0';
  strcpy(this->str, string);
}
void String::print() { cout << this->str; }

String::~String() { delete[] this->str; }

char *String::getStr() {
  return this->str;
}