/*****************************************************************************
 * Name: Ryan Pal Hilgendorf
 * Assignment: Lab 9 - System Calls
 * Section: CPE 2600 121
 * File: pmod.c
 * Date: 11/5/2024
 * Updated: 11/10/2024
 *****************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define NICE 10

int main(int argc, char* argv[])
{
    // reduce priority by 10 and error check
    nice(NICE);

    // set timespec
    struct timespec *ts = malloc(sizeof(struct timespec));
    ts->tv_sec = 1;
    ts->tv_nsec = 837272638;
    // sleep for 1,837,272,638 ns
    if (nanosleep(ts, NULL) != 0) {
        perror("Nanosleep Failed.\n");
        exit(1);
    }

    // goodbye :)
    free(ts);
    printf("goodbye\n");
    return 0;
}