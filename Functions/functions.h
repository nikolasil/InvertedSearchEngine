#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/// Maximum document length in characters.
#define MAX_DOC_LENGTH (1 << 22)

/// Maximum word length in characters.
#define MAX_WORD_LENGTH 31

/// Minimum word length in characters.
#define MIN_WORD_LENGTH 4

/// Maximum number of words in a query.
#define MAX_QUERY_WORDS 5

/// Maximum query length in characters.
#define MAX_QUERY_LENGTH ((MAX_WORD_LENGTH + 1) * MAX_QUERY_WORDS)

/// Query ID type.
typedef unsigned int QueryID;

/// Document ID type.
typedef unsigned int DocID;

/// Matching types:
typedef enum {
  /**
   * Two words match if they are exactly the same.
   */
  MT_EXACT_MATCH,
  /**
   * Two words match if they have the same number of characters, and the
   * number of mismatching characters in the same position is not more than
   * a specific threshold.
   */
  MT_HAMMING_DIST,
  /**
   * Two words match if one of them can can be transformed into the other word
   * by inserting, deleting, and/or replacing a number of characters. The number
   * of such operations must not exceed a specific threshold.
   */
  MT_EDIT_DIST
} MatchType;

/// Error codes:
typedef enum {
  /**
   * Must be returned by each core function unless specified otherwise.
   */
  EC_SUCCESS,
  /**
   * Must be returned only if there is no available result to be returned
   * by GetNextAvailRes(). That is, all results have already been returned
   * via previous calls to GetNextAvailRes().
   */
  EC_NO_AVAIL_RES,
  /**
   * Used only for debugging purposes, and must not be returned in the
   * final submission.
   */
  EC_FAIL
} ErrorCode;

#include "../Data Structures/entry/entry.h"
#include "../Data Structures/entry/entry_list.h"
#include "../Data Structures/tree/tree.h"

///////////////////////////////////////////////////////////////////////////////////////////////
//*********************************************************************************************

/**
 * This method creates a new entry that represents the word w and returns a specific exit code
 */

ErrorCode create_entry(const word *w, entry **e);

/**
 * This method destroys a given entry and returns the proper exit code
 */

ErrorCode destroy_entry(entry **e);

/**
 * This method creates and initializes a new entry_list and returns the proper error code
 */
ErrorCode create_entry_list(entry_list **el);

/**
 * This method returns the number of entries contained in the given entry list
 */

unsigned int get_number_entries(const entry_list *el);

/**
 * This method adds a new entry to a given entry_list and returns the proper exit code
 */

ErrorCode add_entry(entry_list *el, const entry *e);

/**
 * This method returns the first entry in the given entry list
 */
entry *get_first(const entry_list *el);

/**
 * This method returns the next entry in the given entry list
 */
entry *get_next(const entry_list *el, const entry *e);

/**
 * This method destroys the entry list and returns the proper error code
 */

ErrorCode destroy_entry_list(entry_list **el);

/**
 * This method creates a new index from an existing entry list, the match type that will be applied  and returns the proper exit code.
 */

ErrorCode build_entry_index(const entry_list *el, MatchType type, tree **ix);

/**
 * This method returns a set of entries that correspond with the given word depending of the index match type and the threshold.
 */

ErrorCode lookup_entry_index(const word &w, tree *ix, int threshold, entry_list **result);
;

/**
 * This method destroys the index and returns the proper exit code
 */

ErrorCode destroy_entry_index(tree **ix);

#endif