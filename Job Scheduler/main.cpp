#include <iostream>
#include "Queue.h"
#include "Job.h"
#include "JobScheduler.h"
using namespace std;

int main(){
    Queue* queue = new Queue();
    queue->addFromHead(new Job(1));
    queue->addFromHead(new Job(2));
    queue->addFromHead(new Job(3));
    queue->print();

    queue->removeFromTail()->print();
    queue->removeFromTail()->print();
    queue->removeFromTail()->print();
}