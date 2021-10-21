#include "String.h"
#include <cstring>
using namespace std;

String::String() {
  str = new char[1];
  str[0] = '\0';
}

String::String(const char *string) {
  str = new char[strlen(string) + 1];
  strcpy(str, string);
}

String::~String() {
  delete[] str;
}