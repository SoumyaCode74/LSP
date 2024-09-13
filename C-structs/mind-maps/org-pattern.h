#ifndef __ORG_PAT_H__
#define __ORG_PAT_H__


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

/*
Level 1: Employee
Level 2: Engineer, Senior Engineer
Level 3: Manager 
*/

struct Employee{
    /*  Attributes   */
    char name[50];
    unsigned int id;
}

struct Manager{
    /*  Attributes   */
    struct Employee M;
    /* Capabilities */
    int CheckAttendance(struct Employee *);
    void GiveInstructions(void *);
}

struct Manager{
    /*  Attributes   */
    /* Capabilities */
}

struct Manager{
    /*  Attributes   */
    /* Capabilities */
}