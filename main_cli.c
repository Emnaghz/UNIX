#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"

int main()
{
  Question question;
  Response response;
  int fifo1, fifo2;

  fifo1 = open(FIFO1, O_WRONLY);
  fifo2 = open(FIFO2, O_RDONLY);

  signal(SIGUSR1, hand_reveil);
  signal(SIGUSR2, handle_server_termination);
  question.client_num = getpid();
  while (1)
  {
    question.count = rand() % NMAX + 1;
    printf("\033[0;34m %d: Client sending question: generating %d random numbers \n \033[0m", question.client_num, question.count);
    write(fifo1, &question, sizeof(question));

    pause(); // Wait for server response

    if (read(fifo2, &response, sizeof(response)) > 0)
    {
      printf("\033[0;32m %d: Client received result: generating %d random numbers : \n\n \033[0m", response.client_num, question.count);
      for (int i = 0; i < question.count; i++)
      {
        printf("%d", response.numbers[i]);
        if (i < question.count - 1)
        {
          printf(" \033[0;34m | \033[0m");
        }
      }
      printf("\n\n");
    }

    sleep(5); // Send message every 5 seconds
  }

  close(fifo1);
  close(fifo2);

  return 0;
}
