//server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void receive_file(int client_socket, const char* save_path) {
    // Receive file size
    char buffer[BUFFER_SIZE];
    ssize_t file_size = 0;
    recv(client_socket, buffer, sizeof(buffer), 0);
    file_size = atoi(buffer);

    // Receive file data
    FILE* file = fopen(save_path, "wb");
    while (file_size > 0) {
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            break;
        }
        fwrite(buffer, 1, bytes_received, file);
        file_size -= bytes_received;
    }
    fclose(file);
    printf("File received successfully.\n");
}

void start_server(const char* server_ip, int port, const char* save_path) {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 1) == -1) {
        perror("Error listening for connections");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on %s:%d\n", server_ip, port);

    int client_socket = accept(server_socket, NULL, NULL);
    if (client_socket == -1) {
        perror("Error accepting connection");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Connection established\n");

    receive_file(client_socket, save_path);

    close(client_socket);
    close(server_socket);
}

int main() {
    const char* server_ip = "127.0.0.1";
    int server_port = 12345;
    const char* save_directory = "server_files";
    mkdir(save_directory, 0777);  // create directory if not exists

    start_server(server_ip, server_port, "server_files/received_file.txt");

    return 0;
}

