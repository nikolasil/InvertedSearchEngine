#ifndef JOB_H
#define JOB_H

class Job {
  char type;
  int status;
  void (*function)(int, char **);
  char **args;
  int numArgs;

public:
  Job(char type, void (*function)(int, char **), char **args, int numArgs);
  ~Job();
  // Getters
  char getType() { return this->type; };
  int getStatus() { return this->status; };
  void (*getFunction())(int, char **) { return this->function; };
  void *getArgs() { return this->args; };
  int getNumArgs() { return this->numArgs; };
  // Setters
  void setType(char type) { this->type = type; };
  void setStatus(int status) { this->status = status; };
  void setFunction(void (*function)(int, char **)) { this->function = function; };
  void setArgs(char **args) { this->args = args; };
  void setNumArgs(int numArgs) { this->numArgs = numArgs; };
  // Utility
  void print();
  void execute();
};

#endif