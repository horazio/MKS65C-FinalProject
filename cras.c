#include "cras.h"

//Deck of Card (chars)
char Deck[52];

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

//Deals card to all players
void Deal() {
  Shuffle_Deck();
  printf("Dealing...\n");
  
  int i = Player_Num;
  while(i >= 0) {
    
    struct player dealt;
    dealt = Player_List[i];
    
    int j = 0;
    while (j < 2) {
      dealt.hand[j] = Deck[Cards_Dealt];
      dealt.size++;
      Cards_Dealt++;
      j++;
    }
    i--;
  }
}

//give player another card
void Hit(struct player playerName){

}

//end the player's turn
void Stick(struct player PlayerName){

}

//Prints one card from card ID#
void Print_Card(char card){

  char suit = card/13;
  char num  = card%13;

  char * suits[4] = {"♠","♥","♣","♦"};
  char * nums[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

  printf("%s%s\n", nums[num], suits[suit]);
}

//Prints a player's hand
void Print_Hand(struct player playerName) {
  printf("%s's Hand:\n", playerName.name);
  char * hand = playerName.hand;
  int i = 0;
  while (i < playerName.size) {
    Print_Card(*hand);
    hand++;
    i++;
  }

}

//Prints the entire Deck (Debug only)
void Print_Deck() {
  int i = 0;
  while (i<52){
    Print_Card(Deck[i]);
    i++;
  }
}

//Sets the deck to Frech out of pack order
char * Initialize_Deck() {
  char i = 0;
  while (i < 52) {
    Deck[i] = i;
    i++;
  }
  return Deck;
}

//Randomnly shuffles deck
void Shuffle_Deck() {
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

    i++;
  }
}


//Tester (debug only)
int main(int argc, char const *argv[]) {
  Initialize_Deck();
  printf("Begin\n");
  Print_Deck();
  printf("------------------------\n");
  Shuffle_Deck();
  printf("------------------------\n");
  Print_Deck();
  printf("------------------------\n");
  Initialize_Deck();
  Print_Deck();
  printf("------------------------\n");
  Print_Card(0);
  struct player Cooper;
  Player_List[0] = Cooper;
  Deal();
  strcpy(Cooper.name, "Cooper");
  Print_Hand(Cooper);

  return 0;
}
