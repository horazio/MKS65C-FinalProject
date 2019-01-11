#include "cras.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2){
    //server_socket = client_setup( argv[1]);
  }
  else{
    server_socket = client_setup( TEST_IP, "9001" );
    printf("bound to the 9001 port\n");
    read(server_socket, buffer, sizeof(buffer));
    printf("received, '%s'\n", buffer);
    sleep(.5);
    server_socket = client_setup(TEST_IP, buffer);
    printf("bound to the other port\n");
  }
  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
  }
}
