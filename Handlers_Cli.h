#ifndef HANDLERS_CLI_H
#define HANDLERS_CLI_H

#include <signal.h>
#include <stdio.h>

void hand_reveil(int sig)
{
  printf("%d: Client recieved from SIGUSR1\nClient is waking up...\n", sig);
}

void handle_server_termination(int sig)
{
  printf("\n\033[0;31m Server is closing. Goodbye!\033[0m\n");
  exit(0);
}
#endif
