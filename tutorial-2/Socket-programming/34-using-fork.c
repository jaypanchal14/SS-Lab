#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8989

void handle_client(int client_socket) {
    char buffer[100];
    int bytes_received;

    while (1) {
        bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            break;
        }
        printf("Received: %s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    close(client_socket);
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8989);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the server address
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listening error");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Accept incoming connection
        client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addr_size);

        if (client_socket < 0) {
            perror("Accept error");
            exit(EXIT_FAILURE);
        }

        int pid = fork();
        if (pid == 0) {
            // Child process
            close(server_fd);  // Close the server socket in child process
            handle_client(client_socket);
            exit(0);
        } else {
            // Parent process
            close(client_socket);  // Close the client socket in parent process
        }
    }

    return 0;
}
