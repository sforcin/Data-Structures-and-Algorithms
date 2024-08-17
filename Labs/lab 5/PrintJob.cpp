#include "PrintJob.h"

// Constructor initializes a PrintJob with the given priority, job number, and number of pages.
PrintJob::PrintJob(int setP, int setJ, int numP): priority(setP), jobNumber(setJ), numPages(numP){}

// Get the priority of the PrintJob.
int PrintJob::getPriority(){
    return priority;
}

// Get the job number of the PrintJob.
int PrintJob::getJobNumber(){
    return jobNumber;
}

// Get the number of pages of the PrintJob.
int PrintJob::getPages(){
    return numPages;
}
