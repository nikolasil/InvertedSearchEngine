## Inverted Search Engine Optimization
*An Inverted Search Engine Optimizer based from the [SIGMOD 2013 Contest](https://sigmod.kaust.edu.sa/task-details.html)*

![Project Demo](public/project_demo.gif)
### :building_construction: Compilation & Execution

In order to provide easier compilation a Makefile has been included. The Makefile accepts the following commands: 
- ```make clean``` to clean the project's object files and executable
- ```make clean_test``` to clean the test's object files and test executable
- ```make clean_all``` to clean all files and executables
-  ```make compile``` to compile the project's files
- ```make run``` to run the project
- ```make test``` to compile the test files
- ```make run_test``` to run the tests



### :notebook_with_decorative_cover:General Approach

The project is divided into 3 distinct categories :
- **Data Structures** The Data Structures Directory contains all the structures that are essential for the project ie. **Hash Tables, Lists, Trees, Arrays, Strings**
    - **Hash Table**
        ```cpp
        class HashTable {
          Bucket **table;
          int size;
        }
        // Bucket is a linked list that stores the words
        class Bucket { 
          bucketNode *head;
          bucketNode *last;
          int count;
        }
        // BucketNode is a node that stores the word
        // and the and information about that word
        // information = A list with the data {query_id,count_total_words}
        class BucketNode {
          String *word;
          exactInfoList *list; // linked list with {query_id,count_total_words}
          bucketNode *next;
        }
        ```
  - **Exact Info** The list that holds the hash table (exact match) information
      ```cpp
      class exactInfoList {
        exactInfoNode *head;
        exactInfoNode *last;
        int count;
      }
      class exactInfoNode {
        ExactInfo *info;
        exactInfoNode *next;
      }
      typedef struct ExactInfo {
        QueryID query_id; // the id of the query
        bool flag; // false if the query is deleted 
        unsigned int maxQueryWords; // the total words of that query
      } ExactInfo;
      ```
  - **BK Tree** A BK_Tree index (BK Tree) is used for searching words that have a specific matching distance from a key word.
      ```cpp
      class BK_Tree {
        BK_TreeNode *root;
      }
      // BK_TreeNode stores the word
      class BK_TreeNode { 
        String *data;
        BK_TreeEdge *childs; // linked list with the childs
        heInfoList *info;
      }
      // Represents the edge that points to a child with that weight
      class BK_TreeEdge {
        int weight;
        BK_TreeNode *child;
        BK_TreeEdge *next;
      }
      ```
  - **Hamming Array** An Array of 28 cells. Each cell contains a BK Tree
      ```cpp
      class heInfoList {
        heInfoNode *head;
        heInfoNode *last;
        int count;
      }
      class heInfoNode {
        HEInfo *info;
        heInfoNode *next;
      }
      ```
  - **Hamming & Edit Info** The list that holds the hamming and edit information
      ```cpp
      class heInfoList {
        heInfoNode *head;
        heInfoNode *last;
        int count;
      }
      class heInfoNode {
        HEInfo *info;
        heInfoNode *next;
      }
      typedef struct HEInfo {
        QueryID query_id; // the id of the query
        bool flag; // false if the query is deleted 
        unsigned int maxQueryWords;// the total words of that query
        unsigned int matchDist; // the match distance of that query
      } HEInfo;
      ```
  - **Match Array** Used for storing the results of the lookups. For every query we hold a tree that contains the words that we have matched for this query.
      ```cpp
      class MatchArray {
        MatchTree **array; // all the results of the lookups are here for each query
        int size;
        ResultList *matchedIds; // the list that contains only the matched ids
      }
      ```

- **Functions** The Functions Directory is mainly based from the SIGMOD 2013 Contest and contains an interface for managing the data structures listed above. The main use of functions is to create a BK_Tree index to be used as an inverted search engine.
- **Tests** The Tests Directory contains a testing suite using the [Acutest Testing Framework](https://github.com/mity/acutest). It tests all the data structures for creation,lookup and deletion by using the project's functions.

### :grey_exclamation: Additional Information
- 

### :desktop_computer: Contributors
 - [Nikolas Iliopoulos](https://github.com/nikolasil) (1115201800332) 
 - [Michalis Volakis](https://github.com/michael-vol) (1115201800022)
