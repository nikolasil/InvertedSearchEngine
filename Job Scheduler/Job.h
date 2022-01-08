#ifndef JOB_H
#define JOB_H

class Job {
  char type;
  void (*function)();
  int status;

public:
  Job(char type, void (*function)());
  ~Job();
  char getType() { return this->type; };
  int getStatus() { return this->status; };
};

#endif