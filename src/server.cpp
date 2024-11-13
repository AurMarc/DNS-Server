#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "dns/dnsheader.hpp"  
#include "dns/dnsquestion.hpp"
#include "dns/dnsanswer.hpp"

int main() {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Disable output buffering
    setbuf(stdout, NULL);

    std::cout << "Starting UDP server..." << std::endl;

    int udpSocket;
    struct sockaddr_in clientAddress;

    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udpSocket == -1) {
        std::cerr << "Socket creation failed: " << strerror(errno) << std::endl;
        return 1;
    }

    int reuse = 1;
    if (setsockopt(udpSocket, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
        std::cerr << "Setting SO_REUSEPORT failed: " << strerror(errno) << std::endl;
        close(udpSocket);
        return 1;
    }

    sockaddr_in serv_addr = {};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(2053);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(udpSocket, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) != 0) {
        std::cerr << "Binding failed: " << strerror(errno) << std::endl;
        close(udpSocket);
        return 1;
    }

    std::cout << "UDP server listening on port 2053..." << std::endl;

    int bytesRead;
    char buffer[512];
    socklen_t clientAddrLen = sizeof(clientAddress);

    DNSMessage receivedMessage;
    uint8_t messageBuffer[512];  // Buffer to store the DNS message
    uint8_t responseBuffer[512];  // Buffer to store the full response

    while (true) {
        // Receive data
        bytesRead = recvfrom(udpSocket, buffer, sizeof(buffer) - 1, 0, reinterpret_cast<struct sockaddr*>(&clientAddress), &clientAddrLen);
        if (bytesRead == -1) {
            std::cerr << "Error receiving data: " << strerror(errno) << std::endl;
            continue; // Continue listening even if there's a receive error
        }

        // Convert the byte buffer into a DNSMessage structure
        byteArrayToMessage(reinterpret_cast<uint8_t*>(buffer), receivedMessage);

        // Print the received message ID for debugging purposes
        std::cout << "Received DNS query with ID: " << ntohs(receivedMessage.ID) << std::endl;

        // Initialize DNS response message based on received request
        DNSMessage responseMessage;
        initDNSMessage(responseMessage, true); // Set QR flag to 1 for response
        responseMessage.ID = receivedMessage.ID; // Set the same ID as the query

        // Construct the DNS response
        int offset = sizeof(DNSMessage);
        memcpy(responseBuffer, reinterpret_cast<uint8_t*>(&responseMessage), sizeof(DNSMessage));

        // Now, let's handle the DNS question section
        DNSQuestion question;
        int questionOffset = sizeof(DNSMessage);
        // Extract the question section from the received message (from buffer)
        // This part assumes that the question is at the correct position after the header
        std::vector<uint8_t> questionBuffer(buffer + questionOffset, buffer + bytesRead);
        question.name = questionBuffer; // We simply copy the question name for simplicity
        question.qtype = htons(1);  // A record (host address)
        question.qclass = htons(1); // IN class (Internet)

        // Encode the DNS question and add to response buffer
        std::vector<uint8_t> encodedQuestion;
        encodeDNSQuestion(question, encodedQuestion);
        memcpy(responseBuffer + offset, encodedQuestion.data(), encodedQuestion.size());
        offset += encodedQuestion.size();

        // Add the answer section (for simplicity, returning a mock answer)
        DNSAnswer answer;
        answer.name = question.name;  // Same as the question name
        answer.type = htons(1); // A record
        answer.classType = htons(1); // IN class
        answer.ttl = htonl(3600); // TTL of 1 hour
        answer.dataLength = htons(4); // IPv4 address size (4 bytes)
        answer.data = {192, 168, 0, 1}; // Mock answer IP address (192.168.0.1)

        std::vector<uint8_t> encodedAnswer;
        encodeDNSAnswer(answer, encodedAnswer);
        memcpy(responseBuffer + offset, encodedAnswer.data(), encodedAnswer.size());
        offset += encodedAnswer.size();

        // Send the DNS response back to the client
        if (sendto(udpSocket, responseBuffer, offset, 0, reinterpret_cast<struct sockaddr*>(&clientAddress), clientAddrLen) == -1) {
            std::cerr << "Failed to send response: " << strerror(errno) << std::endl;
        }
    }

    close(udpSocket);
    return 0;
}
