#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

#include <signal.h>
#include <stdio.h>

void hand_reveil(int sig) {
  printf("%d: Client recieved from SIGUSR1\nClient is waking up...\n", sig);
}

#endif
