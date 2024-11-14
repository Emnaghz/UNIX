#ifndef SERV_CLI_FIFO_H
#define SERV_CLI_FIFO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define NMAX 150
#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"

typedef struct {
    int client_num;
    int number;
} Question;

typedef struct {
    int client_num;
    int result;
} Response;

#endif
