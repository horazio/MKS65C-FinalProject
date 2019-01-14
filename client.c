#include "cras.h"

int main(int argc, char **argv) {
  
  struct player me;
  int server_socket;
  char * buffer = calloc(sizeof(char), BUFFER_SIZE * 8);
  
  
  if (argc == 2){
    //server_socket = client_setup( argv[1]);
  }
  
  else{
    server_socket = client_setup( TEST_IP, "9301" );
    //printf("bound to the 9301 port\n");
    read(server_socket, buffer, BUFFER_SIZE * 8 );
    //printf("received, '%s'\n", buffer);
    sleep(.5);
    server_socket = client_setup(TEST_IP, buffer);
    //printf("bound to the other port\n");
  }
  
  printf("\033[H\033[J");
  printf("What is your name?\n");
  fgets(buffer, BUFFER_SIZE * 8, stdin);
  *strchr(buffer, '\n') = 0;
  strcpy(me.name, buffer);
  write(server_socket, buffer, strlen(buffer));
  
  printf("\033[H\033[J");
  printf("Waiting for others to join...\n");
  
  printf("%s\n", buffer);
  
  
  while(strcmp(buffer, "s")){
    
    read(server_socket, buffer, BUFFER_SIZE * 8);
    
    printf("\033[H\033[J");
    printf("%s\n", buffer);
    
    memset(buffer, 0, BUFFER_SIZE * 8);
    
    printf("Would you like to hit or stick? (h/s)\n"); 
    fgets(buffer, BUFFER_SIZE * 8, stdin);
    *strchr(buffer, '\n') = 0;
    
    //printf("-->%s<--\n", buffer);
    
    while(strcmp(buffer, "s") && strcmp(buffer, "h")) {
      printf("Need I remind you: (h/s)\n"); 
      fgets(buffer, BUFFER_SIZE * 8, stdin);
      *strchr(buffer, '\n') = 0;
    }
    
    //printf("-->>%s<<--\n", buffer);
    write(server_socket, buffer, strlen(buffer));
    
    
  }
  
  while (1) {
    
    /*
      printf("enter data: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
      write(server_socket, buffer, sizeof(buffer));
      read(server_socket, buffer, sizeof(buffer));
      printf("received: [%s]\n", buffer);
    */
  }
}
