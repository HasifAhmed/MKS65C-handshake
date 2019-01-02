#include "pipe_networking.h"


static void sighandler(int signo) {
  if (signo == SIGINT) {
    printf("Shutdown\n");
    remove("Hasif");
    exit(0);
  }
}

char rot13charversion( char ch){
  char alpha[] = "abcdefghijklmnopqrstuvwxyz";
  char Alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if(strchr(alpha, ch) != NULL){
    int index = (strchr(alpha,ch) - alpha + 13) % 26;
    return *(alpha + index);
  }
  else if (strchr(Alpha, ch) != NULL ){
    int index = (strchr(Alpha,ch) - Alpha + 13) % 26;
    return *(Alpha + index);
  }
  else return ' ';
}
char * rot13(char * msg){
     char * result = malloc(BUFFER_SIZE * sizeof(char));
     int i = 0;
     while(*(msg + i)){
       *(result + i) = rot13charversion(*(msg + i));
       i++;
     }
     return result;
}

int main() {
    //intercept signals
    signal(SIGINT, sighandler);

    int to;
    int from;
    from = server_handshake( &to );
    while(from) {
        char msg[BUFFER_SIZE];
        char buf[BUFFER_SIZE];

        while(read(from, buf, BUFFER_SIZE)) {

            printf("What Should I Rotate? : %s\n", buf);
            write(to, rot13(buf), BUFFER_SIZE);
        }
        printf("User %d goodbye\n", from);

        remove("Hasif");
        from = server_handshake( &to );
    }
}
