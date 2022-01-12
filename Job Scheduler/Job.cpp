#include "Job.h"
#include <iostream>

using namespace std;

Job::Job(char type, ErrorCode (*function)(int, void **), void **args, int numArgs) {
  this->type = type;
  this->status = 0;
  this->function = function;
  this->args = args;
  this->numArgs = numArgs;
}

Job::~Job() {
}

void Job::execute() {
  this->function(this->numArgs, this->args);
}

void Job::print() {
  cout << "Job: " << this->type << " " << *(int *)args[0] << endl;
}