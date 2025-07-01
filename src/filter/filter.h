#pragma once
#include <cstdint>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
struct filter {
    std::pair<uint32_t, uint32_t> get_range_i(int i) {
        return {raw[i*2], raw[i*2+1]};
    }

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
            uint32_t dst_port_start;
            uint32_t dst_port_end;
        };
        uint32_t raw[10] = {0};
    };

    operator bool() {
        return !fltr_.empty();
    }
};

std::shared_ptr<filter> prepare_filter(int id, int precedence, const std::string& string_repr);