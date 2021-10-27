#include "approximateMatching.h"
#include "../string/String.h"
#include <cstring>

using namespace std;

int hammingDistance(String *word1, String *word2) {
  char *str1 = word1->getStr();
  char *str2 = word2->getStr();
  int length1 = strlen(str1);
  int length2 = strlen(str2);
  int count = length1 - length2;

  if (count < 0) {
    count = -count;
  }

  for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
    if (str1[length1 - i - 1] != str2[length2 - i - 1]) {
      count++;
    }
  }

  return count;
}