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
#define PORT "9001"
#define TEST_IP "127.0.0.1"
#define READ 0
#define WRITE 1

char Deck[52];
int Player_Num;

//Player type (has a hand, handsize, and name) - possibly username & password
struct player {
  char hand[13];
  char size;
  char * name;
  int clySock;
  int mySock;
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

//From demo
void error_check(int i, char *s);
int server_setup();
int server_connect(int sd);
int client_setup(char * server, char * port);


