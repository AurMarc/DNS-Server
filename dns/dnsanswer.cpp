#include "dnsanswer.hpp"

void encodeDNSAnswer(const DNSAnswer& answer, std::vector<uint8_t>& buffer) {
    // Encode name
    for (size_t i = 0; i < answer.name.size(); ++i) {
        buffer.push_back(answer.name[i]);
    }
    buffer.push_back(0);  // Null terminator

    // Encode type, class, TTL, data length
    buffer.push_back((answer.type >> 8) & 0xFF);
    buffer.push_back(answer.type & 0xFF);
    buffer.push_back((answer.classType >> 8) & 0xFF);
    buffer.push_back(answer.classType & 0xFF);
    buffer.push_back((answer.ttl >> 24) & 0xFF);
    buffer.push_back((answer.ttl >> 16) & 0xFF);
    buffer.push_back((answer.ttl >> 8) & 0xFF);
    buffer.push_back(answer.ttl & 0xFF);
    buffer.push_back((answer.dataLength >> 8) & 0xFF);
    buffer.push_back(answer.dataLength & 0xFF);

    // Add answer data
    buffer.insert(buffer.end(), answer.data.begin(), answer.data.end());
}
