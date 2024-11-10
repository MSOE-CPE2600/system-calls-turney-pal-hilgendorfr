/*****************************************************************************
 * Name: Ryan Pal Hilgendorf
 * Assignment: Lab 9 - System Calls
 * Section: CPE 2600 121
 * File: finfo.c
 * Date: 11/5/2024
 * Updated: 11/10/2024
 *****************************************************************************/
#define _GNU_SOURCE
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>

/********************************** HELPERS **********************************/
// checks and displays the file type of the input
void printfiletype(mode_t mode) {
    printf("File Type: ");
    if (S_ISREG(mode)) {
        printf("File\n");
    } else if (S_ISDIR(mode)) {
        printf("Directory\n");
    } else if (S_ISCHR(mode)) {
        printf("Character Device\n");
    } else if (S_ISLNK(mode)) {
        printf("Symbolic Link\n");
    } else if (S_ISBLK(mode)) {
        printf("Block Device\n");
    } else if (S_ISSOCK(mode)) {
        printf("Socket\n");
    } else if (S_ISFIFO(mode)) {
        printf("FIFO\n");
    } else {
        printf("File Type Unknown.\n");
    }
}

// displays all file permissions
void printperms(mode_t mode) {
    printf("\nPrint Permissions:\n");
    switch (S_ISDIR(mode)) {
        case 1:
            printf("Is a Directory\n");
            break;
        default:
            printf("Not a Directory\n");
    }
    printf("User Permissions: ");
    switch (mode & S_IRUSR) {
        case S_IRUSR:
            printf("r");
            break;
        default:
            printf("-");
    }
    switch (mode & S_IWUSR) {
        case S_IWUSR:
            printf("w");
            break;
        default:
            printf("-");
    }
    switch (mode & S_IXUSR) {
        case S_IXUSR:
            printf("x");
            break;
        default:
            printf("-");
    }
    printf("\nGroup Permissions: ");
    switch (mode & S_IRGRP) {
        case S_IRGRP:
            printf("r");
            break;
        default:
            printf("-");
    }
    switch (mode & S_IWGRP) {
        case S_IWGRP:
            printf("w");
            break;
        default:
            printf("-");
    }
    switch (mode & S_IXGRP) {
        case S_IXGRP:
            printf("x");
            break;
        default:
            printf("-");
    }
    printf("\nOther User Permissions: ");
    switch (mode & S_IROTH) {
        case S_IROTH:
            printf("r");
            break;
        default:
            printf("-");
    }
    switch (mode & S_IWOTH) {
        case S_IWOTH:
            printf("w");
            break;
        default:
            printf("-");
    }
    switch (mode & S_IXOTH) {
        case S_IXOTH:
            printf("x");
            break;
        default:
            printf("-");
    }
    printf("\n\n");
}

/*********************************** MAIN ************************************/
int main(int argc, char* argv[])
{
    struct stat *fileStats = malloc(sizeof(struct stat));

    // is filename provided?
    if (argc != 2) {
        perror("Filename not provided!\n");
        exit(1);
    }

    // get file information
    if (stat(argv[1], fileStats) != 0) {
        perror("Unable to get file info.\n");
        exit(1);
    }

    // print type of file
    printfiletype(fileStats->st_mode);

    // print file permisions
    printperms(fileStats->st_mode);

    // print owner of the file
    printf("Owner ID: %d\n", fileStats->st_uid);

    // print size of the file in bits
    printf("File Size: %ld\n", fileStats->st_size);

    // get the date and time of last modification
    struct tm *time = localtime(&fileStats->st_mtime);
    if (time == NULL) {
        perror("Unable to format time.\n");
        exit(1);
    }
    // print the date and time
    printf("Last Modification: %02d/%02d/%d %02d:%02d:%02d\n", time->tm_mon + 1, \
    time->tm_mday, time->tm_year + 1900, time->tm_hour, time->tm_min, \
    time->tm_sec);

    // free mem and exit
    free(fileStats);
    return 0;
}