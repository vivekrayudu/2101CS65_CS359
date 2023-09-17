#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void handle_client(int client_socket) {
    char buffer[1024];
    ssize_t bytes_received;
    
    // Receive data from the client
    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("Error receiving data from client");
        return;
    }

    buffer[bytes_received] = '\0';
    std::string message(buffer);

    if (message[0] == '1') {
        // Task 1: Send a response message
        std::cout << "Received message from client: " << message.substr(1) << std::endl;
        std::string response_message = "Have a good day";
        send(client_socket, response_message.c_str(), response_message.size(), 0);
    } else if (message[0] == '2') {
        // Task 2: Determine the number of vowels
        std::cout << "Received string from client for Task 2: " << message.substr(1) << std::endl;
        int vowel_count = 0;
        for (char c : message.substr(1)) {
            if (strchr("aeiouAEIOU", c) != nullptr) {
                vowel_count++;
            }
        }
        std::string response_message = std::to_string(vowel_count);
        send(client_socket, response_message.c_str(), response_message.size(), 0);
    } else if (message[0] == '3') {
        // Task 3: Check if the string is a palindrome
        std::cout << "Received string from client for Task 3: " << message.substr(1) << std::endl;
        std::string input = message.substr(1);
        std::string response_message;
        if (std::equal(input.begin(), input.begin() + input.size()/2, input.rbegin())) {
            response_message = "String is palindrome";
        } else {
            response_message = "String is not palindrome";
        }
        send(client_socket, response_message.c_str(), response_message.size(), 0);
    } else if (message[0] == '4') {
        // Task 4: Calculate the sum of elements in an integer array
        std::cout << "Received integer array from client for Task 4: " << message.substr(1) << std::endl;
        std::istringstream iss(message.substr(1));
        int num, sum = 0;
        while (iss >> num) {
            sum += num;
        }
        std::string response_message = std::to_string(sum);
        send(client_socket, response_message.c_str(), response_message.size(), 0);
    }

    close(client_socket);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        return 1;
    }

    // Set up server address
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 3) < 0) {
        perror("Error listening for connections");
        return 1;
    }

    std::cout << "Server is listening for incoming connections..." << std::endl;

    while (true) {
        // Accept a connection from a client
        client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_length);
        if (client_socket < 0) {
            perror("Error accepting connection");
            return 1;
        }

        handle_client(client_socket);
    }

    // Close server socket
    close(server_socket);

    return 0;
}
