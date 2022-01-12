#include "String.h"
#include <cstring>
#include <iostream>
#define MINCOMB(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

using namespace std;

String::String(const char *string) {
  this->size = strlen(string);
  this->str = new char[this->size + 1];
  this->str[this->size] = '\0';
  strcpy(this->str, string);
}
String::String(String *s) {
  this->size = s->getSize();
  this->str = new char[this->size + 1];
  this->str[this->size] = '\0';
  strcpy(this->str, s->getStr());
}
String::~String() {
  delete[] this->str;
  this->str = nullptr;
}

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

int String::editDistance(char *str1, char *str2, int str1Len, int str2Len) {
  int row, column;
  int array[str2Len + 1][str1Len + 1];
  array[0][0] = 0;
  // initialize the first collumn (blank str compared with every sub string of str1 must have an edit distance of the length of this substring)
  for (row = 1; row <= str2Len; row++)
    array[row][0] = array[row - 1][0] + 1;
  // initialize the first row     (blank str compared with every sub string of str2 must have an edit distance of the length of this substring)
  for (column = 1; column <= str1Len; column++)
    array[0][column] = array[0][column - 1] + 1;
  // fill the array (row for row, column for column)
  for (row = 1; row <= str2Len; row++) {
    for (column = 1; column <= str1Len; column++) {
      // The edit distance of the cell is the minimum of the
      // (left cell + 1, upper cell + 1, diagonal cell or diagonal cell + 1)

      // if the last chars are the same, we dont need to add 1 in the diagonal cell
      // we can just remove the last chars and the edit distance will be the same as the diagonal's cell

      // Operations:
      // diagonal cell  = replace
      // upper cell     = remove
      // left cell      = insert
      array[row][column] = MINCOMB(array[row - 1][column] + 1, array[row][column - 1] + 1, array[row - 1][column - 1] + (str1[column - 1] == str2[row - 1] ? 0 : 1));
    }
  }
  return array[str2Len][str1Len];
}

void String::print() { cout << this->str; }
