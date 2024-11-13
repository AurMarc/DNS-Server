#ifndef DNSHEADER_HPP
#define DNSHEADER_HPP

#include <cstdint>
#include <cstring>
#include <arpa/inet.h>

// DNSMessage structure
struct DNSMessage {
    uint16_t ID;        // 16 bits
    uint16_t FLAGS;     // 16 bits (QR, Opcode, etc.)
    uint16_t QDCOUNT;   // 16 bits
    uint16_t ANCOUNT;   // 16 bits
    uint16_t NSCOUNT;   // 16 bits
    uint16_t ARCOUNT;   // 16 bits
};

// Functions to work with DNSMessage
void initDNSMessage(DNSMessage& message, bool isResponse);
void messageToByteArray(const DNSMessage& message, uint8_t* buffer);
void byteArrayToMessage(const uint8_t* buffer, DNSMessage& message);

#endif // DNSHEADER_HPP
