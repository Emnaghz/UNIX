#ifndef HANDLERS_SERV_H // pour éviter les inclusions multiple
#define HANDLERS_SERV_H

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void hand_reveil(int sig)
{
  printf("Server recieved a message...");
}

void fin_serveur(int sig)
{
  printf("\n\033[0;31m Server is terminating...\033[0m\n");
  // Notify clients
  for (int i = 0; i < client_count; i++)
  {
    if (client_pids[i] > 0)
    {
      printf("\033[0;33mNotifying client PID: %d\033[0m\n", client_pids[i]);
      kill(client_pids[i], SIGUSR2);
    }
  }
  unlink(FIFO1);
  unlink(FIFO2);

  printf("\033[0;32m Resources cleaned up. Goodbye!\033[0m\n");
  exit(0);
}

#endif
