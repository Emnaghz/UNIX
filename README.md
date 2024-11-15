This project implements a server-client communication model using FIFO (Named Pipes) in C. The server listens for client requests, generates random numbers, and sends them back to the client. The client can request random numbers from the server.

## Requirements
C compiler (e.g., GCC)

make (for building the project)

## File Structure 

**Handlers_Cli.h**         : Header file for client-side signal handlers

**Handlers_Serv.h**         : Header file for server-side signal handlers

**main_cli.c**             : Client program implementation

**main_cli_2.c**           : Second client program implementation

**main_serv.c**           : Server program implementation

**Makefile**                : Makefile to build, run, and clean the project

**README.md**             : Project documentation

**serv_cli_fifo.h**      : FIFO header file with relevant constants


## Building the Project
To compile the server and client programs, you can use make. Here are the commands:
bash
Copier le code
make
This will compile the server and client programs.

To run the server and clients, use the following commands:
1. Run the Server
```bash
make run_server
```
This command will compile and run the server program. The server will listen for incoming client requests via FIFO pipes and respond with random numbers.

2. Run the Client
```bash
make run_client
```
This command will compile and run the first client program. The client will send a request to the server to generate random numbers and wait for the response.

3. Run the Second Client
```bash
make run_client_2
```
This command will compile and run the second client program. It functions similarly to the first client, but you can have multiple clients communicating with the server at the same time.

4. Clean Up
```bash
make clean
```
This command will clean up the compiled files and any generated binaries, so you can rebuild from scratch.
make
