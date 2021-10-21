#ifndef ENTRY_H
#define ENTRY_H

#include "string/String.h"

class entry
{
private:
  word *w;
  void *payload;

public:
  entry(const word *w, void *payload);
  ~entry();
};

class word
{
private:
  String *str;

public:
  word(const char *string);
  ~word();
};

#endif