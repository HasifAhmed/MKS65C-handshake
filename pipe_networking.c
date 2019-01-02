

#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to

  Performs the server side pipe 3 way handshake.
  Sets *to to the file descriptor to the fd pipe (Client --> Server).

  returns the file descriptor for the fdtwo pipe (Server --> Client).
  =========================*/
int server_handshake(int *to) {

  int id = mkfifo("Hasif", 0644);
    if (id == 0) {
        printf("Pipe created\nWaiting for response\n");
    } else {
        printf("Oopsies Something Went Wrong!\n");
        exit(0);
    }
    int server = open("Hasif", O_RDONLY);
    printf("Somethings Been Sent!: %d\n", server);


    char message[HANDSHAKE_BUFFER_SIZE];
    read(server, message, HANDSHAKE_BUFFER_SIZE);
    printf("%s\n", message);
    int p = getpid();
    printf("ppid: %d\n", p);


    if (strcmp(message, "me") == 0) {
        printf("Recieved! %s\n", message);
        fork();
    } else {
        return 0;
    }

    printf("pid: %d\n", getpid());

    if (getpid() != p) {
         printf("pid: %d\n", getpid());
        *to = open(message, O_WRONLY);
        printf("%s: %d\n", message, *to);

        write(*to, "Hellooo", 7);

        char info[BUFFER_SIZE];
        read(server, info, BUFFER_SIZE);
        printf("Recieved: %s\n", info);

        return server;
    }


    return 0;
}


/*=========================
  client_handshake
  args: int * to_server
  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.
  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
    int id = mkfifo("me", 0644);
    if (id == 0) {
        printf("Pipe\n");
    } else {
        printf("Error\n");
    }

    *to_server = open("Hasif", O_WRONLY);
    printf("Connected: %d\n", *to_server);

    char *welcome = "me";
    write(*to_server, welcome, HANDSHAKE_BUFFER_SIZE);




    int client = open(welcome, O_RDONLY);
    char info[BUFFER_SIZE];
    printf("Read: %d\n", client);
    read(client, info, BUFFER_SIZE);
    printf("\n%s\n", info);


    strcpy(info, ok);
    printf("Sending: %s\n", info);
    write(*to_server, info, BUFFER_SIZE);


    return client;
}
