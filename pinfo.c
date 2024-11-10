/*****************************************************************************
 * Name: Ryan Pal Hilgendorf
 * Assignment: Lab 9 - System Calls
 * Section: CPE 2600 121
 * File: pinfo.c
 * Date: 11/5/2024
 * Updated: 11/10/2024
 *****************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char* argv[])
{
    // if too many arguments, exit
    if (argc > 2) {
        printf("Incorrect number of arguments. Only 1 or 0 argument please.\n");
        exit(1);
    } else {
        // if PID provided, use it. Otherwise, use current
        pid_t pid;
        if (argc == 2) {
            pid = atoi(argv[1]);
        } else {
            pid = getpid();
        }

        // get process priority
        int priority = getpriority(PRIO_PROCESS, pid);

        // get scheduler
        int sched = sched_getscheduler(pid);
        if(sched != 0) {
            perror("Unable to retrieve scheduler");
            exit(1);
        }
        // use scheduler to find the scheduling method
        char *schedMethod;
        switch (sched) {
            case SCHED_FIFO:
                schedMethod = "SCHED_FIFO";
                break;
            case SCHED_BATCH:
                schedMethod = "SCHED_BATCH";
                break;
            case SCHED_RR:
                schedMethod = "SCHED_RR";
                break;
            case SCHED_IDLE:
                schedMethod = "SCHED_IDLE";
                break;
            case SCHED_OTHER:
                schedMethod = "SCHED_OTHER";
                break;
            default:
                schedMethod = "Scheduler Method Unknown.";
                break;
        }

        // print info
        printf("PID: %d\n", pid);
        printf("Scheduler Priority: %d\n", priority);
        printf("Scheduling Method: %s\n", schedMethod);
    }
    
    return 0;
}