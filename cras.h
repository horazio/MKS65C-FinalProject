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

char Deck[52];

void Deal();

void Hit();

void Stick();

void Server_Handshake();

void Client_Handshake();

void New_Server();

void Reset_Game();

void Shuffle_Deck();

void Initialize_Deck();

void Print_Card(int);
