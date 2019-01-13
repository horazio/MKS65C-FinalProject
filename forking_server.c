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
 
  char * screen = calloc(sizeof(char), BUFFER_SIZE * 8);
  
  char * buffer = calloc(sizeof(char), BUFFER_SIZE * 8);
  //char * screenTemp = malloc(sizeof(char) * BUFFER_SIZE * 8);
  
  strcpy(screen, "-----------------------------------------------------\n");
  
  struct player playas[num_players];
  for(i = 0; i < num_players; i++){
    Set_Player(&playas[i]);
  }
  
  
  i = 0;
  
  
  
  eternal_socket = server_setup("9001");  
  printf("Waiting for players\n");
  while(i < num_players){
    
    client_socket = server_connect(eternal_socket);
    write(client_socket, ports[i], 5);
    listen_socket = server_setup(ports[i]);
    client_socket = server_connect(listen_socket);
    playas[i].mySock =  listen_socket;
    playas[i].clySock = client_socket;
    read(playas[i].clySock, buffer, BUFFER_SIZE * 8);
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
       
     
      //Screens are prepared
       for(j = 0; j < num_players; j++){
         if(i != j){
            Print_Hand(&playas[j], &screen);
         }  
       }
       strcat(screen, "\n\nMy Hand: ");
       for(j = 0; j < playas[i].size; j++){
          Print_Card(playas[i].hand[j], &screen);  
       }
       
       
 
       write(playas[i].clySock, screen, strlen(screen));
       
       memset(buffer, 0, BUFFER_SIZE * 8);
       read(playas[i].clySock, buffer, BUFFER_SIZE * 8);
       
       //printf("-->%s<--\n", buffer);
     
     
       while(!strcmp(buffer, "h")){
         
         printf("%s chose to hit\n", playas[i].name);
         counter = Hit(&playas[i], counter, deck);
         Print_Card(playas[i].hand[j++], &screen);
         
         //strcpy(screenTemp, screen);
         //strcat(screen, "\n-----------------------------------------------------\n");
         
         //printf("%s\n", screen);
         
         write(playas[i].clySock, screen, strlen(screen));
         
         memset(buffer, 0, BUFFER_SIZE * 8);
         read(playas[i].clySock, buffer, BUFFER_SIZE * 8);
       }
       printf("%s chose to stick\n", playas[i].name);
     
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
  
}

