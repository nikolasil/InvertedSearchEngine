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
- **Data Structures** The Data Structures Directory contains all the structures that are essential for the project ie. Entry Lists, Entries , LinkedLists (as a supplementary list option for creating lists - not used yet) ,Tree (for managing search indexes) and Utils for various utilities (calculating matching distance etc.).
    - **Entry** An Entry is a basic data structure that consists of two elements : a word (string) and a payload (list of subjects)
        ```cpp
        class entry {
            word *w;
            void *payload;
            entry *next;
        };
        ```
  - **Entry List** An Entry List ,as the name suggests, is a linked list consisting of entries and is used for building indexes
    ```cpp
    class entry_list {
        entry *start;
        entry *end;
        unsigned int count;
    };
    ```
  - **Tree Index** A tree index (BK Tree) is used for searching words that have a specific matching distance from a key word.
   

- **Functions** The Functions Directory is mainly based from the SIGMOD 2013 Contest and contains an interface for managing the data structures listed above. The main use of functions is to create a tree index to be used as an inverted search engine.
- **Tests** The Tests Directory contains a testing suite using the [Acutest Testing Framework](https://github.com/mity/acutest). It tests all the data structures for creation,lookup and deletion by using the project's functions.



### Default Behavior by Main Function

The Main Function creates 7 entries from the words : [hell,help,fall,small,fell,felt,melt] and initializes an entry list from these words. It then builds a tree index from the entry list and executes the lookup function using the word "henn" as key. The result array contains the words [hell,help].


### :grey_exclamation: Additional Information
- **The hamming distance matches the equal letters beginning from the right.**
- The used threshold for calculating matching distances is 2.
- The main function includes a timer for measuring the lookup index performance.


### :desktop_computer: Contributors
 - [Nikolas Iliopoulos](https://github.com/nikolasil) (1115201800332) 
 - [Michalis Volakis](https://github.com/michael-vol) (1115201800022)
