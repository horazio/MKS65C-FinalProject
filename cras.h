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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 256
#define PORT "9301"
#define TEST_IP "127.0.0.1"
#define READ 0
#define WRITE 1

#define MAX_PLAYERS 4

char Deck[52];
int Player_Num;

//Player type (has a hand, handsize, name and Number) - possibly username & password
struct player {
  char hand[13];
  char size;
  char name[256];

  int clySock;
  int mySock;
  
  int money;
};

void Set_Player(struct player *);

void Add_Player();

void Remove_Player();

int Deal(struct player *, int, int *);

int Hit(struct player *, int, int *);

void Stick(struct player *);

void Print_Card(char, char * *);

void Print_Hand(struct player *, char * *);

int Value(struct player * );

void Print_Deck(int *);

void Server_Handshake();

void Client_Handshake();

void New_Server();

void Reset_Game();

int * Initialize_Deck();

int * Shuffle_Deck();

int Bust(struct player *);

struct player * Winner(struct player * *, int);

int All_Bust(struct player * * , int );


void Print_File(char *);


//From demo
void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server, char * port);


