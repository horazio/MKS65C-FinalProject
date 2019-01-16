#include "cras.h"


char * Print_File(char * file) {
  int fd = open(file, O_RDONLY);
  char * buffer = calloc(sizeof(char), 256 * 16);
  memset(buffer, 0, 256 * 16);
  read(fd, buffer, 256 * 16);
  return buffer; 
}


int main(int argc, char **argv) {
  printf("\033[H\033[J");
  printf("%s\n", Print_File("BlackJack.txt"));
  printf("%s\n", Print_File("Loading"));

  
  
  struct player me;
  char * IP;
  int server_socket;
  char * buffer = calloc(sizeof(char), BUFFER_SIZE * 8);
  char decisionBuffer[256];
   //printf("before connecting\n\n");
  if (argc == 2){
    IP = argv[1];
    //printf("Connected\n\n");
  }
  else{
    IP = TEST_IP;
    //printf("bound to the 9301 port\n"); 
  }
    
    server_socket = client_setup( IP, "9301" );
    //printf("before reading\n");
    read(server_socket, buffer, BUFFER_SIZE * 8 );
    //printf("received, '%s'\n", buffer);
    //printf("after\n\n");
    sleep(2);

    server_socket = client_setup(IP, buffer);
    //printf("bound to the other port\n");
  
  
  printf("\033[H\033[J");
  printf("What is your nickname? (Max 6 characters)\n");
  fgets(buffer, BUFFER_SIZE * 8, stdin);
  *strchr(buffer, '\n') = 0;
  strcpy(me.name, buffer);
  write(server_socket, buffer, 6);
  
  printf("\033[H\033[J");
  printf("Waiting for others to join...\n");
  
  memset(buffer, 0, BUFFER_SIZE * 8);
  printf("\033[H\033[J");
  read(server_socket, buffer, BUFFER_SIZE * 8);
  printf("%s\n", buffer);
  
  printf("How much would you like to bet? (Minimum bet is 5) ");
  fgets(decisionBuffer, 256, stdin);
  *strchr(decisionBuffer, '\n') = 0;
  
  
  while(atoi(decisionBuffer) < 5){
     printf("Minimum bet is 5, please enter valid number: ");
     fgets(decisionBuffer, 256, stdin);
  }
  
  //writing the bet
  write(server_socket, decisionBuffer, 7);
  
  printf("\nWaiting for others to bet...\n");
  
  //reading the screen
  memset(buffer, 0, BUFFER_SIZE * 8);
  read(server_socket, buffer, BUFFER_SIZE * 8);
  
  printf("\033[H\033[J");
  printf("%s\n", buffer);
  printf("Waiting for other players...\n");
  
  //reading screen (one-by-one)
  memset(buffer, 0, BUFFER_SIZE * 8);
  read(server_socket, buffer, BUFFER_SIZE * 8);
  
  printf("\033[H\033[J");
  printf("%s\n", buffer);  
  
  
  printf("Would you like to hit or stick? (h/s)\n"); 
  fgets(decisionBuffer, 256, stdin);
  *strchr(decisionBuffer, '\n') = 0;
  
  while(strcmp(decisionBuffer, "s") && strcmp(decisionBuffer, "h")) {
     printf("Need I remind you: (h/s)\n"); 
     fgets(decisionBuffer, 256, stdin);
     *strchr(decisionBuffer, '\n') = 0;
  }
  
  write(server_socket, decisionBuffer, 7);
  
  /////-------------------
  
  while(!strcmp(decisionBuffer, "h")){
    
    memset(buffer, 0, BUFFER_SIZE * 8);
    read(server_socket, buffer, BUFFER_SIZE * 8);
    
    printf("\033[H\033[J");
    printf("%s\n", buffer);
    
    if(buffer[strlen(buffer) - 1] == 'D'){
        break;
    }else{  
      printf("Would you like to hit or stick? (h/s)\n"); 
      fgets(decisionBuffer, 256, stdin);
      *strchr(decisionBuffer, '\n') = 0;
      
      while(strcmp(decisionBuffer, "s") && strcmp(decisionBuffer, "h")) {
          printf("Need I remind you: (h/s)\n"); 
          fgets(decisionBuffer, 256, stdin);
          *strchr(decisionBuffer, '\n') = 0;
      }
    }
    
    if(!strcmp(decisionBuffer, "s")){
      printf("\033[H\033[J");
      printf("%s\n", buffer);
      printf("YOU STUCK\n");
    }
    
    //printf("-->>%s<<--\n", buffer);
    write(server_socket, decisionBuffer, strlen(decisionBuffer));
    
  }
  ///////-------------2---------------
  if(!strcmp(decisionBuffer, "s")){
      printf("\033[H\033[J");
      printf("%s\n", buffer);
      printf("YOU STUCK\n");
  }
  printf("\nWaiting for other players and determining winner...\n\n");
  
  memset(buffer, 0, BUFFER_SIZE * 8);
  read(server_socket, buffer, BUFFER_SIZE * 8 );
  
  printf("%s\n", buffer);
    
  free(buffer);
}
