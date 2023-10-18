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

void handle_client(int socket);

void main() {
    
    int server, client;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrL;
    
    // Creating socket with IPV4 and TCP channel
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Error while creating socket");
        exit(1);
    }

    int resuse = 1;
    if(setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &resuse, sizeof(resuse)) == -1){
        perror("Not able to set options in server-socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8989);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error in binding");
        exit(1);
    }
    // Will respond to 1 max concurrently, others will wait/get error
    listen(server, 1);
        
    addrL = sizeof(clientAddr);
    client = accept(server, (struct sockaddr *)&clientAddr, &addrL);
    
    handle_client(client);
    close(client);
    close(server);
}


void handle_client(int client){

    char buf[100];
    char msg[100];
    while(1){
                
        memset(buf, 0, sizeof(buf));
        memset(msg, 0, sizeof(msg));
        printf("Enter msg for client-%d : ",client);
        scanf("%s",msg);
        send(client, msg, strlen(msg), 0);
        
        int bytes = recv(client, &buf, 100, 0);
        printf("Message from client: %s\n",buf);
        if(strcmp(buf, "EXIT") == 0 || strcmp(buf, "exit") == 0){
            printf("Going to close this client connection as exit message is received.\n");
            break;
        }
        if(bytes < 1){
            printf("Going to close this client connection as no bytes have been received.\n");
            break;
        }
                    
    }

}
