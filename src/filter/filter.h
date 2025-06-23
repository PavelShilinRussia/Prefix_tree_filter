#pragma once

#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

struct filter {
    std::pair<uint64_t, uint64_t> get_range_i(int i);
    
    std::string fltr_ = "";

    uint32_t id_ = UINT32_MAX;
    uint32_t precedence_ = UINT32_MAX;
    
    union {
        struct {
            uint32_t protocol_start;
            uint32_t protocol_end;
            uint32_t src_ip_start;
            uint32_t src_ip_end;
            uint32_t src_port_start;
            uint32_t src_port_end;
            uint32_t dst_ip_start;
            uint32_t dst_ip_end;
            uint32_t dst_port_start;;
            uint32_t dst_port_end;    
        };
        uint32_t raw[10] = {0};
    };    


    operator bool()
    {
        return not fltr_.empty();
    }
};

filter* prepare_filter(std::string string_repr);
