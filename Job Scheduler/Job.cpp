#include "Job.h"
#include <iostream>

using namespace std;

Job::Job(char type, void (*function)()) {
  this->type = type;
  this->function = function;
  this->status = 0;
}

Job::~Job() {
}
