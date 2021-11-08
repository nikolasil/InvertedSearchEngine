#include "functions.h"

using namespace std;

ErrorCode create_entry(const word *w, entry *e) {
  e = new entry(w, nullptr);
}