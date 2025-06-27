#include "filter.h"
#include "utils/utils.h"
#include <sstream>
#include <limits>
#include <cstdint>

std::shared_ptr<filter> prepare_filter(int id, int precedence, const std::string& string_repr) {
    auto rv = std::make_shared<filter>();

    std::stringstream ss(string_repr);
    std::vector<std::string> tokens;

    for (std::string token; std::getline(ss, token, ' ');) {
        token = trim(token);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }
    rv->id_ = id;
    rv->precedence_ = precedence;

    if (tokens[2] == "ip") {
        rv->protocol_start = 0;
        rv->protocol_end = std::numeric_limits<uint32_t>::max();
    } else {
        rv->protocol_start = static_cast<uint8_t>(std::stoi(tokens[2]));
        rv->protocol_end = rv->protocol_start;
    }


    uint32_t src_ip_start, src_ip_end, src_port_start, src_port_end;
    uint32_t dst_ip_start, dst_ip_end, dst_port_start, dst_port_end;

    
    size_t index = 4;

    std::string src = tokens[index++];
    
    if (src == "any") {
        src_ip_start = 0;
        src_ip_end = UINT32_MAX;
        src_port_start = 0;
        src_port_end = UINT32_MAX;
    } else {
        auto [sip_start, sip_end] = get_ip_range(src);
        src_ip_start = sip_start;
        src_ip_end = sip_end;

        if (index < tokens.size() && tokens[index] != "to") {
            auto [sp_start, sp_end] = get_port_range(tokens[index++]);
            src_port_start = sp_start;
            src_port_end = sp_end;
        } else {
            src_port_start = 0;
            src_port_end = UINT32_MAX;
        }
    }

    std::string dst = tokens[++index];
    if (dst == "assigned" ) {
        dst_ip_start = 0;
        dst_ip_end = UINT32_MAX;
        dst_port_start = 0;
        dst_port_end = UINT32_MAX;
    } else {
        auto [dip_start, dip_end] = get_ip_range(dst);
        dst_ip_start = dip_start;
        dst_ip_end = dip_end;
        index++;

        if (index < tokens.size()) {
            auto [dp_start, dp_end] = get_port_range(tokens[index]);
            dst_port_start = dp_start;
            dst_port_end = dp_end;
        } else {
            dst_port_start = 0;
            dst_port_end = UINT32_MAX;
        }
    }

    rv->src_ip_start = src_ip_start;
    rv->src_ip_end = src_ip_end;
    rv->src_port_start = src_port_start;
    rv->src_port_end = src_port_end;
    rv->dst_ip_start = dst_ip_start;
    rv->dst_ip_end = dst_ip_end;
    rv->dst_port_start = dst_port_start;
    rv->dst_port_end = dst_port_end;

    rv->fltr_ = string_repr;

    return rv;
}