#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_PLAYERS 4

char Deck[52];
int Player_Num;

//Player type (has a hand, handsize, name and Number) - possibly username & password
struct player {
  char hand[13];
  char size;
  char * name;
  char num;
};

void Add_Player();

void Remove_Player();

void Deal();

void Hit(struct player);

void Stick(struct player);

void Print_Card(char);

void Print_Hand();

void Print_Deck();

void Server_Handshake();

void Client_Handshake();

void New_Server();

void Reset_Game();

void Initialize_Deck();

void Shuffle_Deck();
