#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <arpa/inet.h>


std::pair<std::vector<uint8_t>, std::vector<uint8_t>> get_ip_range(const std::string& ip_mask) {
    std::stringstream ss(ip_mask);
    std::string ip_str, mask_str;

    std::getline(ss, ip_str, '/');
    std::getline(ss, mask_str);

    int mask = std::stoi(mask_str);

    uint32_t ip = ntohl(inet_addr(ip_str.c_str()));

    uint32_t mask_bits = mask == 0 ? 0 : (~0U << (32 - mask));

    uint32_t ip_min = ip & mask_bits;

    uint32_t ip_max = ip_min | ~mask_bits;

    auto to_bytes = [](uint32_t addr) -> std::vector<uint8_t> {
        return std::vector<uint8_t>{
            static_cast<uint8_t>((addr >> 24) & 0xFF),
            static_cast<uint8_t>((addr >> 16) & 0xFF),
            static_cast<uint8_t>((addr >> 8) & 0xFF),
            static_cast<uint8_t>(addr & 0xFF)
        };
    };

    return std::make_pair(to_bytes(ip_min), to_bytes(ip_max) );
}


std::pair<uint16_t, uint16_t> get_port_range( std::string port_range )
{
    std::stringstream ss( port_range );
    std::vector<std::string> v_addr_range;
    std::string token;
    while ( std::getline( ss, token, '-' ) ) {
        v_addr_range.push_back( token );
    }

    std::pair<uint16_t, uint16_t> range;
    range.first = std::stoi( v_addr_range.at( 0 ) );
    range.second = std::stoi( v_addr_range.at( 1 ) );

    return range;
}

std::vector<range> filter_to_vector_of_ranges(filter *fltr)
{
    std::vector<range> res = {};

    res.push_back(range(fltr->get_protocol(), fltr->get_protocol()));

    auto src_ip_range = fltr->get_src_ip_range();
    for (int i = 0; i < src_ip_range.first.size(); i++){
        res.push_back(range(src_ip_range.first[i], src_ip_range.second[i]));
    }

    auto src_port_range = fltr->get_src_port_range();
    res.push_back(range(src_port_range.first, src_port_range.second));


    auto dst_ip_range = fltr->get_src_ip_range();
    for (int i = 0; i < dst_ip_range.first.size(); i++){
        res.push_back(range(dst_ip_range.first[i], dst_ip_range.second[i]));
    }

    auto dst_port_range = fltr->get_src_port_range();
    res.push_back(range(dst_port_range.first, dst_port_range.second));
    
}
