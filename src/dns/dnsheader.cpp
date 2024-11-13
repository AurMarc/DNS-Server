#include "dnsheader.hpp"

// Initialize DNSMessage (Flags for response)
void initDNSMessage(DNSMessage& message, bool isResponse) {
    message.ID = htons(1234);           // Set a random ID for the DNS query
    message.FLAGS = htons(isResponse ? (1 << 15) : 0); // Set the QR flag to 1 if it's a response, 0 if it's a query
    message.QDCOUNT = htons(1);         // No question section in response
    message.ANCOUNT = htons(0);         // No answer section in response
    message.NSCOUNT = htons(0);         // No authority section
    message.ARCOUNT = htons(0);         // No additional section
}

// Convert DNSMessage to a byte array
void messageToByteArray(const DNSMessage& message, uint8_t* buffer) {
    // Copy the DNS message into the buffer (using network byte order)
    memcpy(buffer, &message, sizeof(DNSMessage));
}

// Convert a byte array to DNSMessage
void byteArrayToMessage(const uint8_t* buffer, DNSMessage& message) {
    memcpy(&message, buffer, sizeof(DNSMessage));
    // Convert from network byte order to host byte order
    message.ID = ntohs(message.ID);
    message.FLAGS = ntohs(message.FLAGS);
    message.QDCOUNT = ntohs(message.QDCOUNT);
    message.ANCOUNT = ntohs(message.ANCOUNT);
    message.NSCOUNT = ntohs(message.NSCOUNT);
    message.ARCOUNT = ntohs(message.ARCOUNT);
}
    