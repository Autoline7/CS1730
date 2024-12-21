#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

//holds the max length of the message that we are given
#define MAX_MESSAGE_LENGTH 80


//main method guides the program to be a client and send a simple message to the server 
int main(int argc, char *argv[]) {

  char *ip_address = argv[1];//gets the ipadress from the command line     
  int port = atoi(argv[2]);//gets the port number from the command line 
  char *message = argv[3];//gets the message from the command line

  int sock;//holds the socket descriptor
    struct sockaddr_in server_address;

    // creates a socket with correct parameters/type of connection
    sock = socket(AF_INET, SOCK_STREAM, 0);

    // server address setup
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);

    // convert IP address from text to binary form and set the ip adress
    inet_pton(AF_INET, ip_address, &server_address.sin_addr);

    // connect to the server
    connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

    // send message
    send(sock, message, strlen(message), 0);

    // close socket
    close(sock);
    return 0;
}
