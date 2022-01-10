#ifndef JOB_H
#define JOB_H

#include "../sigmod/include/core.h"

class Job {
  char type;
  int status;
  ErrorCode (*function)(int, void **);
  void **args;
  int numArgs;
  int epoch;

public:
  Job(char type, ErrorCode (*function)(int, void **), void **args, int numArgs);
  ~Job();
  // Getters
  char getType() { return this->type; };
  int getStatus() { return this->status; };
  ErrorCode (*getFunction())(int, void **) { return this->function; };
  void *getArgs() { return this->args; };
  int getNumArgs() { return this->numArgs; };
  int getEpoch() { return this->epoch; };
  // Setters
  void setType(char type) { this->type = type; };
  void setStatus(int status) { this->status = status; };
  void setFunction(ErrorCode (*function)(int, void **)) { this->function = function; };
  void setArgs(void **args) { this->args = args; };
  void setNumArgs(int numArgs) { this->numArgs = numArgs; };
  void setEpoch(int epoch) { this->epoch = epoch; };
  // Utility
  void print();
  void execute();
};

#endif