#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
Objective :
Write a program to communicate between two machines using socket.
This will act as client, and 33-server.c will act as server.
*/

void main() {
    
    int client;
    struct sockaddr_in addr;
    
    char buf[1024];
    char* msg = "Hi server.";
    // Creating socket with IPV4 and TCP channel
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Error while creating socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8989);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Connect to the server
    if (connect(client, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        perror("Error while connecting to server");
        exit(EXIT_FAILURE);
    }
    
    recv(client, &buf, 1024, 0);
    printf("Message from server : %s",buf);
    send(client, msg, strlen(msg), 0);
    
    close(client);
    
}
