#include "cras.h"

void process(char *s);
void subserver(int from_client);
char * ports[] = {"9302", "9303", "9304", "9305"};
int counter;



int main() {
  
  //TESTING FOR VALUE
  /*
    struct player Jeff;
    strcpy(Jeff.name, "Jeff");
    Jeff.size = 3;     
    Jeff.hand[0] = 9;
    Jeff.hand[1] = 1;
    Jeff.hand[2] = 7;
    
    
    struct player Lisa;
    strcpy(Lisa.name, "Lisa");
    Lisa.size = 3;
    Lisa.hand[0] = 5;
    Lisa.hand[1] = 8;
    Lisa.hand[2] = 5;
    
    
    struct player John;
    strcpy(John.name, "John");
    John.size = 3;
    John.hand[0] = 12;
    John.hand[1] = 4;
    John.hand[2] = 0;
    
    struct player Carl;
    strcpy(Carl.name, "Carl");
    Carl.size = 3;
    Carl.hand[0] = 5;
    Carl.hand[1] = 0;
    Carl.hand[2] = 8;
    
    struct player * * people = calloc(sizeof(struct player), 4);
    people[0] = &Jeff;
    people[1] = &Lisa;
    people[2] = &John;
    people[3] = &Carl;
    
    int x = 0;
    for(x;x < 4;x++) {
    printf("Value of %s: %i\n", people[x]->name, Value(people[x]));
    }
    
    if (All_Bust(people, 4)) {
    printf("Nobody wins! :(\n");
    }
    
    printf(">%s< is the winner!\n", Winner(people, 4)->name);
    
  */
  printf("\033[H\033[J");
  Print_File("BlackJack.txt");
  
  int * deck = Initialize_Deck();
  //Print_Deck(deck);
  
  counter = 0;
  int num_players = 4;
  int eternal_socket;
  int listen_socket;
  int client_socket;
  int i = 0; // for incremantation
  int j = 0; // for incrementation
  int b = 0; //for bust/break
  
  char * screen = calloc(sizeof(char), BUFFER_SIZE * 8);
  
  char * buffer = calloc(sizeof(char), BUFFER_SIZE * 8);
  
  
  struct player * winner;
  //char * screenTemp = malloc(sizeof(char) * BUFFER_SIZE * 8);
  
  strcpy(screen, "-----------------------------------------------------\n");
  
  struct player * * playas = calloc(sizeof(struct player), num_players); 
  for(int i = 0; i < 4;i++) {
    playas[i] = calloc(sizeof(struct player), 1);
  }
  
  i = 0;
  
  eternal_socket = server_setup("9301");  
  printf("Waiting for players\n");
  while(i < num_players){
    
    client_socket = server_connect(eternal_socket);
    write(client_socket, ports[i], 5);
    listen_socket = server_setup(ports[i]);
    client_socket = server_connect(listen_socket);
    playas[i] -> mySock =  listen_socket;
    playas[i] -> clySock = client_socket;
    memset(buffer, 0, BUFFER_SIZE * 8);
    read(playas[i]->clySock, buffer, BUFFER_SIZE * 8);
    strcpy(playas[i]->name, buffer);
    printf("Just added %s to the game\n", playas[i]->name);
    i++;
  }
  
  
  deck = Shuffle_Deck(deck);
  
  
  
  //Print_Deck(deck);
  
  //Deal to each Player in num_players
  
  
  for(i = 0; i < num_players; i++){
    counter = Deal(playas[i], counter, deck);
  }
  
  
  for(i = 0; i < num_players; i++){
    
    b = 0;
    //Screens are prepared
    for(j = 0; j < num_players; j++){
      if(i != j){
	Print_Hand(playas[j], &screen);
      }  
    }
    strcat(screen, "\n\nMy Hand: ");
    for(j = 0; j < playas[i]->size; j++){
      Print_Card(playas[i]->hand[j], &screen);  
    }
    
    
    
    write(playas[i]->clySock, screen, strlen(screen));
    
    memset(buffer, 0, BUFFER_SIZE * 8);
    read(playas[i]->clySock, buffer, BUFFER_SIZE * 8);
    
    //printf("-->%s<--\n", buffer);
    
    printf("%s's hand value is %i\n", playas[i]->name, Value(playas[i]));
    
    while(!strcmp(buffer, "h")){
      
      printf("%s chose to hit\n", playas[i]->name);
      counter = Hit(playas[i], counter, deck);
      
      Print_Card(playas[i]->hand[ playas[i] -> size - 1 ], &screen);
      
      //TESTING
      printf("%s's hand value is %i\n", playas[i]->name, Value(playas[i]));
      
      if(Value(playas[i]) == -1){
	        strcat(screen, "YOU BUSTED");
	        b = 1;
      }
      
      //strcpy(screenTemp, screen);
      //strcat(screen, "\n-----------------------------------------------------\n");
      
      //printf("%s\n", screen);
      
      write(playas[i]->clySock, screen, strlen(screen));
      
      if (b == 1) {
	
	            printf("%s busted\n", playas[i]->name);
	            break;
      }
      
      memset(buffer, 0, BUFFER_SIZE * 8);
      read(playas[i]->clySock, buffer, BUFFER_SIZE * 8);
    }
    
    if (b != 1) {
      printf("%s chose to stick\n", playas[i]->name);
    }
    
    strcpy(screen, "-----------------------------------------------------\n");
  }
  
  
  if(All_Bust(playas, num_players)) {
    printf("Nobody wins!\n");
  } else {
    winner = Winner(playas, num_players);
    printf("%s is the Winner!\n", winner -> name);
  }
  
  
  for(i = 0; i < num_players; i++){
    memset(screen, 0, BUFFER_SIZE * 8);
    
    if(playas[i] == winner){
      strcat(screen, "YOU WIN!!");
    }
    else{
      if(All_Bust(playas, num_players)){
        strcat(screen, "Everyone busted, there is no winner!\n");
      }else{
        strcat(screen, winner -> name);
        strcat(screen, " is the winner\n");
      }
    }
    write(playas[i] -> clySock, screen, strlen(screen));
  }
  
  
  while(1){

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

