#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8989

/*
Objective:
Write a program to create a concurrent server using threads to handle client.
*/

void* handle_client(void* client_ptr);

void main() {

    int server, client;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);
    pthread_t thread_id;

    // Create a socket
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    int resuse = 1;
    if(setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &resuse, sizeof(resuse)) == -1){
        perror("Not able to set options in server-socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the server address
    if (bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections with backlog of size 5
    if (listen(server, 5) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listening error");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Accept incoming connection
        client = accept(server, (struct sockaddr*)&client_addr, &addr_size);

        if (client < 0) {
            perror("Accept error");
            exit(EXIT_FAILURE);
        }

        // Create a new thread to handle the client
        pthread_create(&thread_id, NULL, handle_client, (void*)&client);

        // Detach the thread
        pthread_detach(thread_id);
    }

}

void* handle_client(void* client_ptr) {
    int client = *((int*)client_ptr);
    free(client_ptr);
    char buffer[100];
    int bytes_received;

    while (1) {

        //Add code according to your convenience
        bytes_received = recv(client, buffer, 100, 0);
        if (bytes_received <= 0) {
            break;
        }
        printf("Received: %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    close(client);
    pthread_exit(NULL);
}
