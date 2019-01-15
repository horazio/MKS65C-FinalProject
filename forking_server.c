#include "cras.h"

void process(char *s);
void subserver(int from_client);
char * ports[] = {"9302", "9303", "9304", "9305", "9306", "9307"};
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
  printf("%s\n", Print_File("BlackJack.txt"));
  
  char * buffer = calloc(sizeof(char), BUFFER_SIZE * 8);

  int num_players = 4;
  
  printf("How many players would you like? (2-6)\n");
  fgets(buffer, BUFFER_SIZE * 8, stdin);
  *strchr(buffer, '\n') = 0;
  while (atoi(buffer) < 2 || atoi(buffer) > 6) {
    memset(buffer, 0, BUFFER_SIZE * 8);
    printf("Please enter a valid number (2-6)\n");
    fgets(buffer, BUFFER_SIZE * 8, stdin);
    *strchr(buffer, '\n') = 0;
  } 
  num_players = atoi(buffer);
  memset(buffer, 0, BUFFER_SIZE * 8);
  
 // printf("%i\n", num_players);
  
  //while(1){}
  
  int * deck = Initialize_Deck();
  //Print_Deck(deck);
  
  counter = 0;
  int eternal_socket;
  int listen_socket;
  int client_socket;
  int i = 0; // for incremantation
  int j = 0; // for incrementation
  int b = 0; //for bust/break
  int bet = 5;
  
  char * screen = calloc(sizeof(char), BUFFER_SIZE * 8);
  
  struct player * winner;
  //char * screenTemp = malloc(sizeof(char) * BUFFER_SIZE * 8);
  
  strcpy(screen, "-----------------------------------------------------\n");
  
  //Initializing the player
  struct player * * playas = calloc(sizeof(struct player), num_players); 
  for(int i = 0; i < 4;i++) {
    playas[i] = calloc(sizeof(struct player), 1);
    playas[i] -> cash = 100;
  }
  
  i = 0;
  
  eternal_socket = server_setup("9301");  
  printf("%s\n", Print_File("Loading"));

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
  
  
  //Deal to each Player in num_players
  
  
  for(i = 0; i < num_players; i++){
    counter = Deal(playas[i], counter, deck);
  }
  
  
  //send a screen to everyone
  for(i = 0; i < num_players; i++){
    strcpy(screen, Make_Screen(i, playas, num_players));
    write(playas[i]->clySock, screen, strlen(screen));
  }
  
  //printf("SENT SCREEN TO ALL PLAYERS\n\n\n")
  
  //reading the bet for all players
  for(i = 0; i < num_players; i++){
    memset(buffer, 0, BUFFER_SIZE * 8);
    read(playas[i]->clySock, buffer, BUFFER_SIZE * 8);
    
    bet = atoi(buffer);
    
    if(bet > playas[i] -> cash){
        bet = playas[i] -> cash;
    }
    
    playas[i] -> bet = bet;
    playas[i] -> cash -= bet;
    printf("%s chose to bet %i, and has %i remaining\n", playas[i] -> name, bet, playas[i] -> cash);
  }
  
  //writing screen to all players (after the bets are in)
  for(i = 0; i < num_players; i++){
    strcpy(screen, Make_Screen(i, playas, num_players));
    write(playas[i]->clySock, screen, strlen(screen));
  }
  
  //asking clients for action (one-by-one)
  for(i = 0; i < num_players; i++){
    
    //writing screen again (one-by-one)
    strcpy(screen, Make_Screen(i, playas, num_players));
    write(playas[i]->clySock, screen, strlen(screen));
    
    printf("%s's hand value is %i\n", playas[i]->name, Value(playas[i]));
    
    b = 0;
    
    memset(buffer, 0, BUFFER_SIZE * 8);
    read(playas[i]->clySock, buffer, BUFFER_SIZE * 8);
    /////---------
    while(!strcmp(buffer, "h")){
      printf("%s chose to hit\n", playas[i]->name);
      counter = Hit(playas[i], counter, deck);
      
      printf("%s's hand value is %i\n", playas[i]->name, Value(playas[i]));
      
      strcpy(screen, Make_Screen(i, playas, num_players));
      
      if(Value(playas[i]) == -1){
	        strcat(screen, "YOU BUSTED");
	        b = 1;
      }
      
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
    
  }
  
  if(All_Bust(playas, num_players)) {
    printf("Nobody wins!\n");
  } else {
    winner = Winner(playas, num_players);
    // give the winner their money
    for(i = 0; i < num_players; i++) {
      winner -> cash += playas[i] -> bet;
      playas[i] -> bet = 0;
    }
    printf("%s is the Winner!\n", winner -> name);
  }
  
  
  for(i = 0; i < num_players; i++){
    memset(screen, 0, BUFFER_SIZE * 8);
    
    if(playas[i] == winner){
      strcat(screen, "You now have ");
      char * money = calloc(sizeof(char), 10);
      itoa(winner->cash, money);
      strcat(screen, money);
      strcat(screen, " Cash\n");
      strcat(screen, Print_File("You_Win"));
    }
    else{
      if(All_Bust(playas, num_players)){
        strcat(screen, "Everyone busted, there is no winner!\n");
      }else{
        strcat(screen, winner -> name);
        strcat(screen, " is the winner and now has ");
        char * money = calloc(sizeof(char), 10);
        itoa(winner->cash, money);
        strcat(screen, money);
        strcat(screen, " Cash\n");
        strcat(screen, Print_File("You_Lose"));
      }
    }
    write(playas[i] -> clySock, screen, strlen(screen));
  }
  
  
  //while(1){

  //}
  
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

