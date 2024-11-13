#ifndef DNSQUESTION_HPP
#define DNSQUESTION_HPP

#include <string>
#include <vector>
#include <cstdint>

struct DNSQuestion {
    std::vector<uint8_t> name;
    uint16_t qtype;
    uint16_t qclass;
};

// Functions for DNS Question
void encodeDNSQuestion(const DNSQuestion& question, std::vector<uint8_t>& buffer);

#endif // DNSQUESTION_HPP
