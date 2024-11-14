CC = gcc

CFLAGS = -Wall

TARGETS = server client client_2

SERVER_OBJ = main_serv.o
CLIENT_OBJ = main_cli.o
CLIENT_2_OBJ = main_cli_2.o 

FIFO1 = /tmp/fifo1
FIFO2 = /tmp/fifo2

all: $(TARGETS)

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o server $(SERVER_OBJ)

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o client $(CLIENT_OBJ)

client_2: $(CLIENT_2_OBJ)
	$(CC) $(CFLAGS) -o client_2 $(CLIENT_2_OBJ)

server.o: main_serv.c serv_cli_fifo.h Handlers_Serv.h
	$(CC) $(CFLAGS) -c main_serv.c

client.o: main_cli.c serv_cli_fifo.h Handlers_Cli.h
	$(CC) $(CFLAGS) -c main_cli.c

client_2.o: main_cli_2.c serv_cli_fifo.h Handlers_Cli.h 
	$(CC) $(CFLAGS) -c main_cli_2.c

run_server: server
	./server

run_client: client
	./client

run_client_2: client_2 
	./client_2

clean:
	rm -f $(TARGETS) *.o $(FIFO1) $(FIFO2)
