#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*
Objective :
Write a program to communicate between two machines using socket.
This will act as server, and 33-client.c will act as client.
*/

void main() {
    
    int server, client;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrL;
    char buf[1024];
    char* msg = "Hi client.";
    // Creating socket with IPV4 and TCP channel
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Error while creating socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8989);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in binding");
        exit(1);
    }
    // Will respond to 3 max concurrently, others will wait/get error
    listen(server, 3);
    
    addrL = sizeof(clientAddr);
    client = accept(server, (struct sockaddr *)&clientAddr, &addrL);
    send(client, msg, strlen(msg), 0);
    recv(client, &buf, 1024, 0);
    printf("Message from client : %s",buf);
    
    close(client);
    close(server);
}
