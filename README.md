## Inverted Search Engine Optimization

_An Inverted Search Engine Optimizer based from the [SIGMOD 2013 Contest](https://sigmod.kaust.edu.sa/task-details.html)_

<!-- ![Project Demo](public/project_demo.gif) -->

### :building_construction: Compilation & Execution

In order to provide easier compilation a Makefile has been included. The Makefile accepts the following commands:

- `make clean` to clean the project's object files and executable
- `make clean_test` to clean the test's object files and test executable
- `make clean_all` to clean all files and executables
- `make` to compile the project's files
- `make test` to compile the test files

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
      AVLMatchTree **array; // all the results of the lookups are here for each query
      int size;
      ResultList *matchedIds; // the list that contains only the matched ids
    }
    ```

- **Functions** The Functions Directory is mainly based from the SIGMOD 2013 Contest and contains an interface for managing the data structures listed above. The main use of functions is to create a BK_Tree index to be used as an inverted search engine.
- **Tests** The Tests Directory contains a testing suite using the [Acutest Testing Framework](https://github.com/mity/acutest). It tests all the main Data Structures used for storing Queries,Documents and Results as well as the core functions (StartQuery,MatchDocument, GetNextAvailableRes,EndQuery) used by the test driver provided by sigmod to test the document results.

### :ocean: Modifications in Core Functions & Data Flow

#### StartQuery

The main purpose of the StartQuery function is to take each word token of each query and store it depending on the MatchType in the corresponding Structure (HashTable for Exact Match, BK_Tree for Edit Distance, Hamming Array for Hamming Distance). In order to achieve this, it utilizes helper structs mainly the ExactInfo and the HEInfo to store in these three structs the information necessary for each word regarding the query it appears in.

> For each match type we also store the heInfo/exactInfo into a list to properly free the info nodes after we matched all the documents
> The maxQueryId property in the main structs object that is incremented for each query iteration will later be used as an index for the MatchArray array size.

### MatchDocument

The MatchDocument Function tokenizes the document into the words it contains and tries to find matches between these words and the words in the queries we processed in StartQuery. To optimize this we used the lookup methods for all 3 data structures mentioned above:

- For the ExactMatch type we hash the word token and search in the respective bucket for a word that matches it. If there is a match we add that word and the exact info list that contains the info of all the queries the matched word appears in, into the match array to add it later to the matched documents (excluding the queries that have been deleted/flagged).
- For the Hamming/Edit types we use the BK_Tree lookup function which does the following:
  Instead of calling the lookup function multiple times for all the possible threshold values(1-3) we do the following:
  - We begin with the minimum threshold(1 for root/ threshold parameter for subtrees) and for each iteration we compare the match type distance with the threshold iterator. If it is a match we update the match array with the info list of the word.
  - We then iterate for the starting threshold up to the maximum threshold(3) and compare the edge weights (distance between the child and its parent node ) to see if we are inside the distance range. If the weight is inside the range we recursively call the lookup function **using the current threshold iterator value as a starting threshold for its subtree.**
- Finally we construct the document with the matched query ids that are stored inside the matchArray and we push it into the document list that stores all the matched documents.

> If we call the lookup function for a tree node with a specific threshold value e.g. 2 , it is certain that it will also be called for its subtree with all the possible threshold values greater than 2. This is used for optimizing the stack calls of the lookup function for each possible threshold and checking only the values necessary for matching the word token.

### GetNextAvailableRes

We only modified the GetNextAvailableRes function to support our document list object

---

> The InitializeIndex and DestroyIndex functions do nothing as all the necessary data and objects are statically initialized by the DataStructs Object.

### :bullettrain_side: Performance & Optimization

By utilizing the optimization techniques mentioned above we managed to reduce the execution time for processing the sample small_test file from the initial ~33s down to ~2.01s!

### :desktop_computer: Contributors

- [Nikolas Iliopoulos](https://github.com/nikolasil) (1115201800332)
- [Michalis Volakis](https://github.com/michael-vol) (1115201800022)
