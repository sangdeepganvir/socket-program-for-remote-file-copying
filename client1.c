//client

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

void send_file(int client_socket, const char* file_path) {
    // Send file size
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char buffer[BUFFER_SIZE];
    sprintf(buffer, "%ld", file_size);
    send(client_socket, buffer, sizeof(buffer), 0);

    // Send file data
    while (!feof(file)) {
        size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);
        send(client_socket, buffer, bytes_read, 0);
    }

    fclose(file);
    printf("File sent successfully.\n");
}

void start_client(const char* server_ip, int port, const char* file_path) {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Error connecting to server");
        close(client_socket);
        exit(EXIT_FAILURE);
    }

    send_file(client_socket, file_path);

    close(client_socket);
}

int main() {
    const char* server_ip = "127.0.0.1";
    int server_port = 12345;
    const char* file_to_send = "client_files/sample.txt";

    start_client(server_ip, server_port, file_to_send);

    return 0;
}
