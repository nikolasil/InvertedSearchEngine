#include "String.h"
#include <cstring>
#include <iostream>

using namespace std;

String::String(const char *string) {
  this->size = strlen(string);
  this->str = new char[this->size + 1];
  this->str[this->size] = '\0';
  strcpy(this->str, string);
}
String::String(const String *s) {
  this->size = s->getSize();
  this->str = new char[this->size + 1];
  this->str[this->size] = '\0';
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
int String::compare(String *s) {
  char *s1 = this->str;
  char *s2 = s->getStr();
  while (*s1 == *s2 && *s1 && *s2) {
    s1++;
    s2++;
  }
  return *s1 - *s2;
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

int String::editDistance(char *str1, char *str2, int m, int n) {

  if (m == 0)
    return n;

  if (n == 0)
    return m;

  if (str1[m - 1] == str2[n - 1])
    return editDistance(str1, str2, m - 1, n - 1);

  // cout << str1 << " " << str2 << " " << m << "  " << n << endl;

  int minReplace = editDistance(str1, str2, m - 1, n - 1);
  int minRemove = editDistance(str1, str2, m - 1, n);
  int minInsert = editDistance(str1, str2, m, n - 1);

  return 1 + min(minReplace, min(minRemove, minInsert));
}

void String::print() { cout << this->str; }
