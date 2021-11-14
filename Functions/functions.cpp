#include "functions.h"
#include "../Data Structures/tree/tree.h"
#include <iostream>

using namespace std;

ErrorCode create_entry(const word *w, entry **e) {
  try {
    *e = new entry(w, nullptr);
    return EC_SUCCESS;
  } catch (const exception &e) {
    return EC_FAIL;
  }
}

ErrorCode destroy_entry(entry **e) {
  try {
    delete e;
    return EC_SUCCESS;
  } catch (const exception &e) {
    return EC_FAIL;
  }
}

ErrorCode create_entry_list(entry_list **el) {
  try {
    *el = new entry_list();
    return EC_SUCCESS;
  } catch (const exception &e) {
    return EC_FAIL;
  }
}

unsigned int get_number_entries(const entry_list *el) {
  if (!el) {
    return -1;
  }
  return el->getCount();
}

ErrorCode add_entry(entry_list *el, const entry *e) {
  try {
    el->addEntry((entry *)e);
    return EC_SUCCESS;
  } catch (const exception &e) {
    return EC_FAIL;
  }
}

entry *get_first(const entry_list *el) {
  if (!el) {
    return nullptr;
  }
  return el->getStart();
}

entry *get_next(const entry_list *el, entry *e) {
  if (!el) {
    return nullptr;
  }
  return el->getNext(e);
}

ErrorCode destroy_entry_list(entry_list **el) {
  try {
    delete el;
    return EC_SUCCESS;
  } catch (const exception &e) {
    return EC_FAIL;
  }
}

ErrorCode build_entry_index(const entry_list *el, MatchType type, tree **ix) {
  try {
    *ix = new tree();
    switch (type) {
    case MT_HAMMING_DIST:
      (*ix)->fillLinkedList(el, type);
      return EC_SUCCESS;
    case MT_EDIT_DIST:

      return EC_SUCCESS;
    case MT_EXACT_MATCH:
      return EC_SUCCESS;
    default:
      return EC_SUCCESS;
    }
  } catch (const exception &e) {
    return EC_FAIL;
  }
}

ErrorCode lookup_entry_index(const word &w, tree *ix, int threshold,
                             entry_list **result) {
  try {
    *result = ix->lookup((String *)&w, threshold);

    return EC_SUCCESS;
  } catch (const exception &e) {
    return EC_FAIL;
  }
}

ErrorCode destroy_entry_index(tree *ix) {
  try {
    delete ix;
    return EC_SUCCESS;
  } catch (const exception &e) {
    return EC_FAIL;
  }
}