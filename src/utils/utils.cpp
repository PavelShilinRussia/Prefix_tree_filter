#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <arpa/inet.h>


#include <arpa/inet.h>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <string>

std::pair<uint32_t, uint32_t> get_ip_range(const std::string& ip_mask) {
    std::stringstream ss(ip_mask);
    std::string ip_str, mask_str;

    std::getline(ss, ip_str, '/');
    std::getline(ss, mask_str);
       
    int mask;
    mask = std::stoi(mask_str);
    

    in_addr_t ip = inet_addr(ip_str.c_str());
    ip = ntohl(ip); 

    uint32_t mask_bits = mask == 0 ? 0 : (~0U << (32 - mask));
    uint32_t ip_min = ip & mask_bits; 
    uint32_t ip_max = ip | ~mask_bits;

    return { ip_min, ip_max };
}

std::pair<uint16_t, uint16_t> get_port_range(const std::string& port_range )
{
    std::stringstream ss( port_range );
    std::vector<std::string> v_addr_range;
    std::string token;
    while ( std::getline( ss, token, '-' ) ) {
        v_addr_range.push_back( token );
    }

    return {std::stoi( v_addr_range.at( 0 ) ), std::stoi( v_addr_range.at( 1 ) )};
}




std::string trim(const std::string& str) {
    std::string result = str;
    result.erase(0, result.find_first_not_of(" \t"));
    result.erase(result.find_last_not_of(" \t") + 1);
    return result;
}