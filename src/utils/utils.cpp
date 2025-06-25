#include "utils.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <arpa/inet.h>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include "prefix_tree_node.h"

std::pair<uint32_t, uint32_t> get_ip_range(const std::string& ip_mask) {
    std::stringstream ss(ip_mask);
    std::string ip_str, mask_str;

    std::getline(ss, ip_str, '/');
    std::getline(ss, mask_str);
       
    int mask;
    if (mask_str == ""){
        mask = 32;
    }
    else{
        mask = std::stoi(mask_str);
    }
    
    

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
    
    if (v_addr_range.size() == 1){
        return {std::stoi( v_addr_range.at( 0 ) ), std::stoi( v_addr_range.at( 0 ) )};
    }

    return {std::stoi( v_addr_range.at( 0 ) ), std::stoi( v_addr_range.at( 1 ) )};
}




std::string trim(const std::string& str) {
    std::string result = str;
    result.erase(0, result.find_first_not_of(" \t"));
    result.erase(result.find_last_not_of(" \t") + 1);
    return result;
}


void sorted_insert(std::vector<std::pair<uint64_t, node *>> &ranges, const std::pair<uint64_t, node *> &new_pair)
{
    if (new_pair.first == 0){
        std::cout << new_pair.first << std::endl;
    }
    auto it = std::lower_bound(ranges.begin(), ranges.end(), new_pair,
                               [](const std::pair<uint64_t, node *> &a, const std::pair<uint64_t, node *> &b)
                               {
                                   return a.first < b.first;
                               });

    ranges.insert(it, new_pair);
}


void sorted_insert_filter(std::vector<filter*>& vect, filter* flt)
{
    
    auto it = std::lower_bound(vect.begin(), vect.end(), flt,
                               [](filter* a, filter* b)
                               {
                                   return a->precedence_ > b->precedence_;
                               });

    vect.insert(it, flt);
}

size_t ts()
{
    timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    size_t start_us = start.tv_sec + 1'000'000 + start.tv_nsec / 1'000;
    return start_us;
}


std::string int_to_ip(unsigned int ip) {
    return std::to_string((ip >> 24) & 255) + "." +
           std::to_string((ip >> 16) & 255) + "." +
           std::to_string((ip >> 8) & 255) + "." +
           std::to_string(ip & 255);
}