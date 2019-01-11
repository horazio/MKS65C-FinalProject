#include "cras.h"

void process(char *s);
void subserver(int from_client);
char * ports = {"9002", "9003", "9004", "9005"};

int main() {
  
  
  int listen_socket;
  int f;
  struct player playas[4];
  int i = 0;
  int fd[2];
  char buff[BUFFER_SIZE];
 
  pipe(fd);
  
  if(fork()){
    while(1){
    read(fd[READ], buff, BUFFER_SIZE);
      
    
    }  
  }else{
    close(fd[READ]);
    while(1){
      listen_socket = server_setup("9001");
      write(client_socket, buffer, sizeof(buffer));
      write(fd[WRITE], "yeet", 5);
      
    }
    
  }
  
  

  
  
  
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
