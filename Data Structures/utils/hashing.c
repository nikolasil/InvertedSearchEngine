#include "hashing.h"
#include "../HT/hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned char hash[SHA_DIGEST_LENGTH];

void generateHash(int key, char *returnHash) {
  char data[256];
  sprintf(data, "%d", key);
  size_t length = strlen(data);
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1((const unsigned char *)data, length, hash);
  memcpy(returnHash, (char *)hash, SHA_DIGEST_LENGTH);
}

void generateHashString(char key[256], char *returnHash) {
  size_t length = strlen(key);
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1((const unsigned char *)key, length, hash);
  memcpy(returnHash, (char *)hash, SHA_DIGEST_LENGTH);
}

int hexadecimalToDecimal(char hexVal[]) {
  int len = strlen(hexVal);

  // Initializing base value to 1, i.e 16^0
  int base = 1;

  int dec_val = 0;

  // Extracting characters as digits from last character
  for (int i = len - 1; i >= 0; i--) {
    // if character lies in '0'-'9', converting
    // it to integral 0-9 by subtracting 48 from
    // ASCII value.
    if (hexVal[i] >= '0' && hexVal[i] <= '9') {
      dec_val += (hexVal[i] - 48) * base;

      // incrementing base by power
      base = base * 16;
    }

    // if character lies in 'A'-'F' , converting
    // it to integral 10 - 15 by subtracting 55
    // from ASCII value
    else if ((hexVal[i] >= 'A' && hexVal[i] <= 'F') || (hexVal[i] >= 'a' && hexVal[i] <= 'f')) {
      dec_val += (hexVal[i] - 55) * base;

      // incrementing base by power
      base = base * 16;
    }
  }

  return abs(dec_val);
}

int getIndex(char *H) {
  return (hexadecimalToDecimal(H) % (HASH_TABLE_SIZE - 1)) + 1;
}