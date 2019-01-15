#include "cras.h"


/* reverse:  reverse string s in place */
 void reverse(char s[]){
   //printf("1Dingus code started\n\n");
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
   //printf("1Dingus code ended\n\n");
}


void itoa(int n, char s[]){
     //printf("0Dingus code started\n\n");
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
     //printf("0Dingus code ended\n\n");
}  


//The player takes hit
int Hit(struct player * jeff, int counter, int * Deck){
  jeff -> hand[jeff -> size++] = Deck[counter++];
  return counter;
}



//Prints a player's hand
void Print_Hand(struct player * jeff, char * * ans) {
  //strcat(*ans, jeff -> name);
  //strcat(*ans, ": ");

  if(jeff -> size == 0){
    strcat(*ans, "Empty");
  }
  
  Print_Card(jeff -> hand[0], ans);
  
  int i;
  for(i = 1; i < jeff -> size; i++){
    strcat(*ans, "*");
  }
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


//it cats
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
  jeff = calloc(sizeof(struct player), 1);
  jeff -> cash = 100;
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


char * Print_File(char * file) {
  int fd = open(file, O_RDONLY);
  char * buffer = calloc(sizeof(char), 256 * 16);
  memset(buffer, 0, 256 * 16);
  read(fd, buffer, 256 * 16);
  return buffer; 
}


char * Make_Screen(int me, struct player * * playas, int num_players) {
  char * screen = calloc(sizeof(char), 8 * BUFFER_SIZE);
  strcpy(screen, "Name\t\tHand\t\tBet\t\tCash\t\t\n");
  strcat(screen, "---------------------------------------------------------------\n");
  char money[10]; // to hold numbers
  int i = 0;
  
  //printf("000000\n\n");
  for(i; i < num_players; i++) {
    if(i != me) { // if this player isn't me
      strcat(screen, playas[i]->name);     // add player name to screen
      strcat(screen, ":");                 // add ':' to the screen
      strcat(screen, "\t\t");              // tab spacing
      Print_Hand(playas[i], &screen);      // add player's hand to screen
      strcat(screen, "\t\t");              // tab spacing
      //strcat(screen, "Bet: ");             // add 'Bet:' to screen
      itoa(playas[i]->bet,money);     // convert the bet to a string
      strcat(screen, money);               // add the bet amount to the screen
      strcat(screen, "\t\t");              // tab spacing
      //strcat(screen, "Cash: ");            // add 'Cash:" to screen
      memset(money, 0, 10);            // resetting char[]
      itoa(playas[i]->cash,money);    // convert the cash to a string
      strcat(screen, money);               // add the cash to screen
      strcat(screen, "\n");                // add a newline
    }
  }
  //printf("11111\n\n");
  
  strcat(screen, "---------------------------------------------------------------\n");
  
  memset(money, 0, 10);                // resetting char[]
  strcat(screen, "\n\n");              // make space
  
  // now add me
  strcat(screen, "Me:");               // add 'Me:' to the screen
  strcat(screen, "\t\t");              // tab spacing
  for(i=0; i < playas[me]->size; i++) {
    Print_Card(playas[me]->hand[i], &screen); // add each card of my hand to the screen
  }                                    // add my hand to screen
  strcat(screen, "\t\t");              // tab spacing
  //strcat(screen, "Bet: ");             // add 'Bet:' to screen
  itoa(playas[me]->bet,money);    // convert the bet to a string
  strcat(screen, money);               // add the bet amount to the screen
  strcat(screen, "\t\t");              // tab spacing
  //strcat(screen, "Cash: ");            // add 'Cash:" to screen
  memset(money, 0, 10);            // resetting char[]
  itoa(playas[me]->cash,money);   // convert the cash to a string
  strcat(screen, money);               // add the cash to screen
  strcat(screen, "\n");                // add a newline
  
  strcat(screen, "---------------------------------------------------------------\n");
  //printf("22222\n\n");
  return screen;
}
