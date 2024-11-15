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

#define NMAX 50
#define FIFO1 "/tmp/fifo1"
#define FIFO2 "/tmp/fifo2"
#define MAX_CLIENTS 10
int client_pids[MAX_CLIENTS];
int client_count = 0;

typedef struct
{
    int client_num;
    int count; // nombre aleatoire
} Question;

typedef struct
{
    int client_num;    // Numéro du client
    int numbers[NMAX]; // Liste des nombres aléatoires
} Response;
#endif
