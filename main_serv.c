#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"
#include <time.h>
#include <signal.h>
#include <stdlib.h>

void alarm_handler(int signum)
{
  printf("\033[0;34m Server is waiting for a new message...\n \033[0m");
  alarm(3);
}

int main()
{
  Question question;
  Response response;
  int fifo1, fifo2;
  time_t start_time = time(NULL);

  if (mkfifo(FIFO1, 0666) == -1)
  {
    perror("Failed to create FIFO1");
    exit(1);
  }

  if (mkfifo(FIFO2, 0666) == -1)
  {
    perror("Failed to create FIFO2");
    exit(1);
  }

  printf(" \033[0;32m %d: Pipes are created successfully!!\n \033[0m", getpid());
  printf(" \033[0;34m Server started. Waiting for messages...\n \033[0m ");
  signal(SIGINT, fin_serveur);
  srand(getpid()); /*initialisation du générateur de nombres aléatoires*/

  fifo1 = open(FIFO1, O_RDONLY);
  if (fifo1 == -1)
  {
    perror("Failed to open FIFO1");
    exit(1);
  }

  fifo2 = open(FIFO2, O_WRONLY);
  if (fifo2 == -1)
  {
    perror("Failed to open FIFO2");
    close(fifo1);
    exit(1);
  }

  printf("\033[0;32m Pipes are opened successfully!!\n \033[0m");
  printf("\033[0;34m Server started. Waiting for messages...\n \033[0m");

  while (1)
  {
    for (int i = 1; i < NSIG; i++)
    {
      if (i)
      {
        signal(i, hand_reveil);
      }
    }
    signal(SIGALRM, alarm_handler);
    signal(SIGTERM, fin_serveur);
    signal(SIGINT, fin_serveur);
    if (time(NULL) - start_time >= 60)
    {
      printf("\033[0;31m Server timeout: 60 seconds exceeded. Terminating...\033[0m\n");
      kill(getpid(), SIGTERM);
    }

    alarm(3); // declancher l'alarme

    if (read(fifo1, &question, sizeof(question)) > 0)
    {//track client for closing server
      int already_tracked = 0;
      for (int i = 0; i < client_count; i++)
      {
        if (client_pids[i] == question.client_num)
        {
          already_tracked = 1;
          break;
        }
      }
      if (!already_tracked && client_count < MAX_CLIENTS)
      {
        client_pids[client_count++] = question.client_num;
      }
      printf("Server received question from client %d: to generate %d random numbers \n", question.client_num, question.count);
      response.client_num = question.client_num;
      for (int i = 0; i < question.count; i++)
      {
        response.numbers[i] = rand() % NMAX + 1; // Générer un nombre aléatoire
      }
      write(fifo2, &response, sizeof(response));
      kill(question.client_num, SIGUSR1);
      start_time = time(NULL); // Reset start time on message receipt
    }
    else
    {
      sleep(3); // Wait for 3 seconds before checking again
    }
  }

  close(fifo1);
  close(fifo2);
  unlink(FIFO1);
  unlink(FIFO2);

  return 0;
}
