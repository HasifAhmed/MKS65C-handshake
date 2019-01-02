#include "pipe_networking.h"


static void sighandler(int signo) {
  if (signo == SIGINT) {
    printf("The End\n");
    remove("Hasif");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  int to;
  int from;
  from = server_handshake( &to);

}
