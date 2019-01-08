#include "cras.h"

char Deck[52];


void Print_Card(int card){

  int suit = card/13;
  int num  = card%13;

  char * suits[4] = {"♠","♥","♣","♦"};
  char * nums[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

  printf("%s%s\n", nums[num], suits[suit]);
}

void Print_Deck() {
  int i = 0;
  while (i<52){
    Print_Card(Deck[i]);
    i++;
  }
}

void Initialize_Deck() {
  int i = 0;
  while (i < 52) {
    Deck[i] = i;
    i++;
  }
}


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

  return 0;
}
