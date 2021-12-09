#ifndef HASHING_H
#define HASHING_H
#include "../HP/heap.h"
#include <openssl/sha.h>
#define HASH_TABLE_SIZE 10

typedef struct hashTableEntry {
  int heapExists;
  HP_info *heapHeaderInfo;
  char heapFileName[12];
} hashTableEntry;

void generateHash(int key, char *returnHash);
void generateHashString(char key[256], char *returnHash);
int getIndex(char *hash);
#endif