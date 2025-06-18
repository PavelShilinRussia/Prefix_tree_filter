#pragma once


#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include "../tree/range.h"

class filter {
public:
    filter( std::string );  
    filter(const filter&);


    
    std::string get_filter_as_string();
    uint32_t get_id();
    uint8_t get_protocol();
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>>  get_src_ip_range();
    std::pair<uint16_t, uint16_t> get_src_port_range();
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>>  get_dst_ip_range();
    std::pair<uint16_t, uint16_t>  get_dst_port_range();
    uint32_t get_precedence();
    range get_range_i(int i);


    

private:
    std::string fltr_;

    uint32_t id_;

    uint8_t protocol_;

    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> src_ip_ranage_;
    std::pair<uint16_t, uint16_t> src_port_range_;

    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> dst_ip_ranage_;
    std::pair<uint16_t, uint16_t> dst_port_range_;

    uint32_t precedence_;
};

