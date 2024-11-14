#ifndef HANDLERS_SERV_H     //pour éviter les inclusions multiple
#define HANDLERS_SERV_H

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void hand_reveil(int sig) {
  printf("Server recieved a message...");
}

void fin_serveur(int sig) {
  printf("Server terminating...\n");
}

#endif
