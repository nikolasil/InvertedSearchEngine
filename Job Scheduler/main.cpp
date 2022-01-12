#include "Job.h"
#include "JobScheduler.h"
#include "Queue.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void func(int numArgs, char **args) {
  cout << "Job func " << args[0] << endl;
}

int main() {
  JobScheduler *jobScheduler = new JobScheduler(2);

  char **args0 = new char *[1];
  args0[0] = "65";
  jobScheduler->addJob(new Job('s', &func, args0, 1));

  char **args1 = new char *[1];
  args1[0] = "17";
  jobScheduler->addJob(new Job('s', &func, args1, 1));

  sleep(5);

  jobScheduler->getQueue()->print();
  return 0;
}
