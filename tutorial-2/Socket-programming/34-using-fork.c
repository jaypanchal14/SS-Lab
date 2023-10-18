#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8989

/*
Objective:
Write a program to create a concurrent server using fork() to handle client.
*/

void handle_client(int client_socket);

void main() {
    int server, client;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

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
    server_addr.sin_port = htons(8989);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the server address
    if (bind(server, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server, 10) == 0) {
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

        int pid = fork();
        if (pid == 0) {
            // Child process
            close(server);  // Close the server socket in child process
            handle_client(client);
            exit(0);
        } else {
            // Parent process
            close(client);  // Close the client socket in parent process
        }
    }

}

void handle_client(int client) {
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
}
