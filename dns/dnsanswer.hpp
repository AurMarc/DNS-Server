#ifndef DNSANSWER_HPP
#define DNSANSWER_HPP

#include <cstdint>
#include <vector>

struct DNSAnswer {
    std::vector<uint8_t> name;
    uint16_t type;
    uint16_t classType;
    uint32_t ttl;
    uint16_t dataLength;
    std::vector<uint8_t> data;
};

// Function to encode DNS Answer
void encodeDNSAnswer(const DNSAnswer& answer, std::vector<uint8_t>& buffer);

#endif // DNSANSWER_HPP
