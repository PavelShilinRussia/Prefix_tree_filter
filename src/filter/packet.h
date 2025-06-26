#pragma once
#include <vector>
#include <cstdint>

struct packet {
    uint8_t header[9];
    uint8_t proto;
    uint8_t pad[2];
    uint32_t src_ip;
    uint32_t dst_ip;
    uint16_t src_port;
    uint16_t dst_port;
    uint8_t udp[4];
    uint8_t padding[4];

    std::vector<uint32_t> return_as_vector() {
        return {proto, src_ip, src_port, dst_ip, dst_port};
    }
};