#include "exactMatching.h"

int exactMatch(char *s1, char *s2) {
  while (*s1 == *s2 && *s1 && *s2) {
    s1++;
    s2++;
  }
  return *s1 == *s2;
}
