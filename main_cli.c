#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"

int main() {
  Question question;
  Response response;
  int fifo1, fifo2;

  fifo1 = open(FIFO1, O_WRONLY);
  fifo2 = open(FIFO2, O_RDONLY);

  signal(SIGUSR1, hand_reveil);

  question.client_num = getpid();
  question.number = question.number + 2;
  while (1) {
    question.number += 2;

    printf("%d: Client sending question: %d\n", question.client_num, question.number);
    write(fifo1, &question, sizeof(question));

    pause(); // Wait for server response

    if (read(fifo2, &response, sizeof(response)) > 0) {
      printf("%d: Client received result: %d\n\n", response.client_num, response.result);
    }

    sleep(5); // Send message every 5 seconds
  }

  close(fifo1);
  close(fifo2);

  return 0;
}
