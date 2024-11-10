/*****************************************************************************
 * Name: Ryan Pal Hilgendorf
 * Assignment: Lab 9 - System Calls
 * Section: CPE 2600 121
 * File: info.c
 * Date: 11/5/2024
 *****************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <math.h>

int main(int argc, char* argv[])
{
    // initialize the timespec variable
    struct timespec *ts = malloc(sizeof(struct timespec));
    // get the current time in seconds and nanoseconds since the Epoch
    clock_gettime(CLOCK_REALTIME, ts);
    // convert the Epoch time to local time in hours, minutes, and seconds
    struct tm *time = localtime(&ts->tv_sec);
    // convert all to nanoseconds
    double timens = (time->tm_hour * 3600 \
    + time->tm_min * 60 + time->tm_sec) * 1e9 + ts->tv_nsec;
    // print time
    printf("Current Local Time in nanoseconds: %.0f\n", timens);

    char hostBuffer[256];
    // get hostname into buffer
    int hostname = gethostname(hostBuffer, sizeof(hostBuffer));
    // if failed, exit
    if (hostname != 0) {
        perror("gethostname failed");
        exit(1);
    }
    // print hostname. This is the network name.
    printf("Hostname: %s\n", hostBuffer);
    // get system name, release, version, and hardware type
    struct utsname *buffer = malloc(sizeof(struct utsname));
    if(uname(buffer) == 0) {
        printf("System Name: %s\n", buffer->sysname);
        printf("Release: %s\n", buffer->release);
        printf("Version: %s\n", buffer->version);
        printf("Hardware Architecture: %s\n", buffer->machine);
    }

    // get the number of CPUs in the system
    printf("Number of Logical Processors: %d\n", get_nprocs());

    // get memory in bytes
    long physMem = sysconf(_SC_PHYS_PAGES) * getpagesize();
    long freeMem = sysconf(_SC_AVPHYS_PAGES) * getpagesize();
    printf("Total Physical Memory in Bytes: %ld\n", physMem);
    printf("Total Free Memory in Bytes: %ld\n", freeMem);

    return 0;
}