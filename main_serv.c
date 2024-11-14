#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"
#include <time.h>
#include <signal.h>
#include <stdlib.h>

void alarm_handler(int signum) {
  printf("Server is waiting for a new message...\n");
  alarm(3);
}

int main() {
  Question question;
  Response response;
  int fifo1, fifo2;
  time_t start_time = time(NULL);

  if (mkfifo(FIFO1, 0666) == -1) {
    perror("Failed to create FIFO1");
    exit(1);
  }

  if (mkfifo(FIFO2, 0666) == -1) {
    perror("Failed to create FIFO2");
    exit(1);
  }

  printf("%d: Pipes are created successfully!!\n", getpid());
  
  srand(getpid());      /*initialisation du générateur de nombres aléatoires*/

  fifo1 = open(FIFO1, O_RDONLY);
  if (fifo1 == -1) {
    perror("Failed to open FIFO1");
    exit(1);
    }

  fifo2 = open(FIFO2, O_WRONLY);
  if (fifo2 == -1) {
    perror("Failed to open FIFO2");
    close(fifo1);
    exit(1);
  }

  printf("Pipes are opened successfully!! \n");

  printf("Server started. Waiting for messages...\n");

  while (1) {
    for(int i=1; i<NSIG; i++) {
      if(i){
        signal(i, hand_reveil);
      }
    }
    signal(SIGALRM, alarm_handler);
    if (time(NULL) - start_time >= 60) {
      printf("No message received for 1 minute. Exiting...\n");
      break;
    }

    alarm(3);// declancher l'alarme

    if (read(fifo1, &question, sizeof(question)) > 0) {
      printf("Server received question %d from client %d\n",question.number, question.client_num);
      response.client_num = question.client_num;
      response.result = rand() % NMAX + 1;
      write(fifo2, &response, sizeof(response));
      kill(question.client_num, SIGUSR1);
      signal(SIGTERM, fin_serveur);
      start_time = time(NULL); // Reset start time on message receipt
    } else {
      sleep(3); // Wait for 3 seconds before checking again
    }
  }

  close(fifo1);
  close(fifo2);
  unlink(FIFO1);
  unlink(FIFO2);

  return 0;
}
