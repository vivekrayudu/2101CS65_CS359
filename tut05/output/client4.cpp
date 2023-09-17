#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Set up server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect to server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error connecting to server");
        return 1;
    }

    // Input an integer array to send to the server for Task 4
    std::string input_message;
    std::cout << "Task 4: Enter an integer array (space-separated): ";
    std::getline(std::cin, input_message);

    // Send message to server for Task 4
    std::string message = "4" + input_message;
    send(client_socket, message.c_str(), message.size(), 0);

    // Receive response from server
    char response_buffer[1024];
    ssize_t bytes_received = recv(client_socket, response_buffer, sizeof(response_buffer), 0);
    if (bytes_received < 0) {
        perror("Error receiving data from server");
        return 1;
    }
    response_buffer[bytes_received] = '\0';

    std::cout << "Received response from server for Task 4: " << response_buffer << std::endl;

    // Close client socket
    close(client_socket);

    return 0;
}
