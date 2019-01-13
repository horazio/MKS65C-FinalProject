#include "cras.h"

void process(char *s);
void subserver(int from_client);
char * ports[] = {"9002", "9003", "9004", "9005"};
int counter;


int main() {
  
  int * deck= Initialize_Deck();
  //Print_Deck(deck);
  
  counter = 0;
  int num_players = 2;
  int eternal_socket;
  int listen_socket;
  int client_socket;
  int f;
  int i = 0;
  int j = 0;
 
  char * screen = malloc(sizeof(char) * BUFFER_SIZE);
  
  strcpy(screen, "-----------------------------------------------------\n");
  
  struct player playas[num_players];
  for(i = 0; i < num_players; i++){
    Set_Player(&playas[i]);
  }
  
  
  i = 0;
  char buffer[BUFFER_SIZE];
  
  
  eternal_socket = server_setup("9001");  
  printf("Waiting for players\n");
  while(i < num_players){
    
    client_socket = server_connect(eternal_socket);
    write(client_socket, ports[i], 5);
    listen_socket = server_setup(ports[i]);
    client_socket = server_connect(listen_socket);
    playas[i].mySock =  listen_socket;
    playas[i].clySock = client_socket;
    read(playas[i].clySock, buffer, sizeof(buffer));
    strcpy(playas[i].name, buffer);
    printf("Just added %s to the game\n", playas[i].name);
    i++;
  }
  
  
  deck = Shuffle_Deck(deck);

  
  
  //Print_Deck(deck);
  
  //Deal to each Player in num_players
  
  
  for(i = 0; i < num_players; i++){
      counter = Deal(&playas[i], counter, deck);  
  }
  
   for(i = 0; i < num_players; i++){
       for(j = 0; j < num_players; j++){
         if(i != j){
            Print_Hand(&playas[j], &screen);
         }  
       }
       strcat(screen, "\n\n My Hand: ");
       for(j = 0; j < playas[i].size; j++){
          Print_Card(playas[i].hand[j], &screen);  
       }
       strcat(screen, "\n-----------------------------------------------------\n");
 
       write(playas[i].clySock, screen, strlen(screen));
       
       strcpy(screen, "-----------------------------------------------------\n");
  }



  
  //flawed debugging code
  //Print_Card(playas[0].hand[0]);
  //Print_Card(playas[0].hand[1]);
  //Print_Card(playas[0].hand[2]);
 
  /*
  printf("Something %s, %d\n", playas[0].name, playas[0].clySock);
  printf("Something %s, %d\n", playas[1].name, playas[1].clySock);
  
  printf("Something %s, %d\n", playas[2].name, playas[2].clySock);
  printf("Something %s, %d\n", playas[3].name, playas[3].clySock);
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
