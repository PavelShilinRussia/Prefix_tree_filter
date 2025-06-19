#include "filter.h"
#include "utils/utils.h"

filter prepare_filter(std::string string_repr)
{
    filter rv;

    std::stringstream ss(string_repr);
    std::vector<std::string> tokens;
    
    for ( std::string token ;std::getline(ss, token, ' ');) {
        token = trim(token);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    rv.id_ = std::stoi(tokens[0]);
    rv.precedence_ = std::stoi(tokens[1]);
    
    auto[ src_ip_start,   src_ip_end]   = get_ip_range(tokens[6]);
    auto[ src_port_start, src_port_end] = get_port_range(tokens[7]);
    auto[ dst_ip_start,   dst_ip_end]   = get_ip_range(tokens[9]);
    auto[ dst_port_start, dst_port_end] = get_port_range(tokens[10]);
    
    rv.protocol_start = static_cast<uint8_t>(std::stoi(tokens[4]));
    rv.protocol_end = rv.protocol_start;
    rv.src_ip_start = src_ip_start;
    rv.src_ip_end = src_ip_end;
    rv.src_port_start = src_port_start;
    rv.src_port_end = src_port_end;
    rv.dst_ip_start = dst_ip_start;
    rv.dst_ip_end = dst_ip_end;
    rv.dst_port_start = dst_port_start;
    rv.dst_port_end = dst_port_end;
    
    rv.fltr_= string_repr;
    
    return rv;
}

std::pair<uint32_t, uint32_t> filter::get_range_i(int i) {
    
    return {raw[i*2], raw[i*2+1]};
    /* 
    if (i == 0){
        return range(protocol_, protocol_);
    }
        
    
    else if ( 1 <= i && i <= 4 ){
        
        return range(src_ip_ranage_.first[i - 1], src_ip_ranage_.second[i - 1]);

    }
    
    else if( i == 5 ){
        range a = range(src_port_range_.first, src_port_range_.second);
        return a;
    }
        
    
    else if (6 <= i && i <= 9){
        return range(dst_ip_ranage_.first[i - 6], dst_ip_ranage_.second[i - 6]);
    }
    else if (i == 10){
        return range(dst_port_range_.first, dst_port_range_.second);
    } */
    
}