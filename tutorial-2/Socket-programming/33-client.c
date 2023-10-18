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
    
    char buf[100];
    char msg[100];
    // Creating socket with IPV4 and TCP channel
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
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
    
    
    while(1){

        memset(buf, 0, 100);
        memset(msg, 0, 100);

        recv(client, &buf, 100, 0);
        printf("Message from server : %s\n",buf);
        
        printf("Enter next message for server: ");
        scanf("%s",msg);
        send(client, msg, strlen(msg), 0);
        
        //read(0, &buf, 100);
        //gets(buf);
        if((strcmp(msg, "EXIT") == 0) || (strcmp(msg, "exit") == 0)){
                break;
        }
    
    }
    close(client);
    
}
