#ifndef ENTRY_H
#define ENTRY_H

class entry {
private:
  word *w;
  void *payload;

public:
  entry(const word *w);
  ~entry();
};

class word {
};

#endif