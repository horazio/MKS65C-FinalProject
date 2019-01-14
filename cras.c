#include "cras.h"

/*


void Print_Deck(int * Deck) {
  int i = 0;
  while (i<52){
    //printf("%d\n", Deck[i]);
    Print_Card(Deck[i]);
    //printf("something\n");
    i++;
  }
}

//Number of players in the game (up to 4)
int Player_Num;

//Player List
struct player Player_List[4];

//Number of Cards in play
char Cards_Dealt;


//Adds player into game
void Add_Player(char * player) {

  struct player name;
  strcpy(name.name, player);

  //if game is full then cant join game
  if(Player_Num = MAX_PLAYERS) {
    printf("Too Many Players\n");
    exit(1);
  }

  //Assign a number to the player
  name.num = Player_Num;

  //Insert the player in the list
  Player_List[name.num] = name;
  Player_Num++;
}

//Removes player from game
// void Remove_Player(struct player name){

//   //Sets position to empty
//   Player_List[name.num] = NULL;

//   //Moves Players w/ a higher number down a spot
//   while(name.num < 3) {
//     Player_List[name.num] = Player_List[name.num++];
//   }

//   //Sets last spot as open
//   Player_List[name.num] = NULL;
//   Player_Num--;
// }





//end the player's turn
void Stick(struct player PlayerName){

}




*/

//The player takes hit
int Hit(struct player * jeff, int counter, int * Deck){
  jeff -> hand[jeff -> size++] = Deck[counter++];
  return counter;
}



//Prints a player's hand
void Print_Hand(struct player * jeff, char * * ans) {
  strcat(*ans, jeff -> name);
  strcat(*ans, ": ");

  if(jeff -> size == 0){
    strcat(*ans, "Empty\n");
  }
  
  Print_Card(jeff -> hand[0], ans);
  
  int i;
  for(i = 1; i < jeff -> size; i++){
    strcat(*ans, "* ");
  }
  strcat(*ans, "\n");
}

int Value(struct player * jeff) {
  if (jeff == NULL) {return -1;}
  int total = 0; // hand value
  int i = 0;     // incrementer
  int aces = 0;  // number of aces in the hand
  for(i;i < jeff->size; i++) { // for every card in the hand
    if(jeff->hand[i]%13 == 0) {// its an ace
      aces++; //add one to the aces counter
      total += 10; //add ten to the hand value
    }
    if(jeff->hand[i]%13 >= 10) { // if it is a face card (not Ace)
      total -= jeff->hand[i]%13%9; //subtract the amount over 10 that it is worth
    }
    
    total += jeff->hand[i]%13 + 1; // add card value to the hand value
  }
  
  //printf("Total: %i", total);
  
  if (total <= 21) {return total;} // if this is a valid hand return it
  
  //printf("Aces: %i", aces);
  
  while(aces) { //if there are any aces
    total -= 10;//subtract 10 from the hand value
    if (total <= 21) {return total;} //if the hand is now valid (ace worth 1) then return the value
    aces--;
  }
  
  return -1; // if its a bust return -1
  
} 


//Prints one card from card ID#
void Print_Card(char card, char * * ans){
  char suit = card/13;
  char num  = card%13;

  char * suits[4] = {"♠","♥","♣","♦"};
  char * nums[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
 
  strcat(*ans, nums[num]);
  strcat(*ans, suits[suit]);
  strcat(*ans, " ");
  
}



//sets the originial values of player
void Set_Player(struct player * jeff){
  jeff -> size = 0;
}


//Deals card to all players
int Deal(struct player * jeff, int counter, int * Deck) {
  printf("Dealing to %s...\n", jeff->name);
  int i = 0;
  while (i < 2) {
    jeff->size++;
    //printf("Sixe: %d\n", jeff -> size);
    jeff->hand[i] = Deck[counter++];
    i++;
  }
  return counter;  
}



//Sets the deck to Frech out of pack order
int * Initialize_Deck() {
  int * Deck = malloc(sizeof(int)*52);
  int i = 0;
  while (i < 52) {
    Deck[i] = i;
    i++;
  }
  return Deck;
}




//Shuffles deck
int * Shuffle_Deck(int * Deck) {
  printf("Shuffling...\n");
  srand(time(NULL));
  int i = 0;
  while (i < 1000) {
    int rand0 = random();
    rand0 = rand0%52;

    int rand1 = random();
    rand1 = rand1%52;

    int help = Deck[rand0];
    Deck[rand0] = Deck[rand1];
    Deck[rand1] = help;

    //printf("switching %s and %s\n", Print_Card(Deck[rand0], Print_Card(Deck[rand1]);
    i++;
  }
  //printf("something\n");
  return Deck;
}

// returns the a pointer to the player with the winning hand
struct player * Compare_Hands(struct player * Jeff, struct player * Lisa) {
  if (Value(Jeff) > Value(Lisa)) {return Jeff;} // Jeff has a better card value
  if (Value(Jeff) < Value(Lisa)) {return Lisa;} // Lisa has a better card value
  else { // same card value
    if(Jeff->size > Lisa->size) {return Lisa;} // Lisa has fewer cards
    if(Jeff->size < Lisa->size) {return Jeff;} // Jeff has fewer cards
  }
  return Jeff; //If the hands are equal then return the first player given
  
}

struct player * Winner(struct player * * playas, int num_players) {
  int i = 0; // incrementer
  
  struct player * winner = playas[i]; // set the winner to the first player
  
  for(i; i < num_players; i++) { // Cycle through players
    
    if (Compare_Hands(playas[i], winner) == playas[i]) { // if this hand is better
      winner = playas[i]; // the current player is the winner
    }
  }

  return winner;
}


int All_Bust(struct player * * playas, int num_players) {
  int i = 0; // incrementer
  
  for (i;i < num_players; i++) { // cycle through players
    if (Value(playas[i]) > -1) {return 0;} // if its not a bust return 0
  }
  
  return 1; //otherwise return 1
}
