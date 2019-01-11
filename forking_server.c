#include "cras.h"

void process(char *s);
void subserver(int from_client);

int main() {
  
  
  int listen_socket;
  int f;
  struct player playas[4];
  int i = 0;
  
  listen_socket = server_setup("9001");

  while (1) {
    
    int client_socket = server_connect(listen_socket);
    
    playas[i].mySock =  listen_socket;
    playas[i].clySock = client_socket;
    i++;
    listen_socket = server_setup("9002");
    
    printf("Just added a new mf player to the game\n");
    
    /*
    f = fork();
    if (f == 0)
      subserver(client_socket);
    else
      close(client_socket);
  */
  }
  
}

void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  while (read(client_socket, buffer, sizeof(buffer))) {

    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
    write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
      *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
