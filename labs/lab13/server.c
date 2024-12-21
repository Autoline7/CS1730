#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_MESSAGE_LENGTH 80
#define BACKLOG 5

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <ip address> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[2]);
    int server_sock, client_sock;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);
    char buffer[MAX_MESSAGE_LENGTH] = {0};

    // Create socket                                                                                                                                                                                                
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }
    printf("Socket created successfully.\n");

    // Server address setup                                                                                                                                                                                         
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(port);

    // Bind socket                                                                                                                                                                                                  
    if (bind(server_sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Bind failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Bind to port %d successful.\n", port);

    // Listen for incoming connections                                                                                                                                                                              
    if (listen(server_sock, BACKLOG) < 0) {
        perror("Listen failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", port);

    // Accept a connection                                                                                                                                                                                          
    if ((client_sock = accept(server_sock, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
        perror("Accept failed");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    printf("Client connected from IP: %s, Port: %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

    // Receive message                                                                                                                                                                                              
    int received_bytes = recv(client_sock, buffer, MAX_MESSAGE_LENGTH - 1, 0);
    if (received_bytes < 0) {
        perror("Receive failed");
    } else {
  buffer[received_bytes] = '\0';  // Null-terminate the received message                                                                                                                                      
        printf("The server received: %s\n", buffer);
    }

    // Close client and server sockets                                                                                                                                                                              
    close(client_sock);
    close(server_sock);
    return 0;
}
