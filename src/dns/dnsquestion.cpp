#include "dnsquestion.hpp"

// Function to encode DNS Question into buffer
void encodeDNSQuestion(const DNSQuestion& question, std::vector<uint8_t>& buffer) {
    // Encode the question name
    for (size_t i = 0; i < question.name.size(); ++i) {
        buffer.push_back(question.name[i]);
    }

    // Add null-terminator to the name
    buffer.push_back(0);

    // Encode type and class
    buffer.push_back((question.qtype >> 8) & 0xFF);
    buffer.push_back(question.qtype & 0xFF);
    buffer.push_back((question.qclass >> 8) & 0xFF);
    buffer.push_back(question.qclass & 0xFF);
}
