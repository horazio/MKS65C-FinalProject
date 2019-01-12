#include "cras.h"

void process(char *s);
void subserver(int from_client);
char * ports[] = {"9002", "9003", "9004", "9005"};
//void listen()

int main() {
  
  int eternal_socket;
  int listen_socket;
  int client_socket;
  int f;
  struct player playas[4];
  int i = 0;
  
  eternal_socket = server_setup("9001");  
  printf("Waiting for four players\n");
  while(i < 2){
    
    client_socket = server_connect(eternal_socket);
    write(client_socket, ports[i], 5);
    listen_socket = server_setup(ports[i]);
    client_socket = server_connect(listen_socket);
    
    playas[i].mySock =  listen_socket;
    playas[i].clySock = client_socket;
    
    printf("Just added a new player to the game\n");
    
    i++;
  }
  /*
  printf("Something %d, %d\n", playas[1].mySock, playas[1].clySock);
  printf("Something %d, %d\n", playas[2].mySock, playas[2].clySock);
  printf("Something %d, %d\n", playas[3].mySock, playas[3].clySock);
  printf("Something %d, %d\n", playas[4].mySock, playas[4].clySock);
  */
    
  
      
      
      
    
    
  
  
  

  
  
  
  while (1) {
    
    
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
