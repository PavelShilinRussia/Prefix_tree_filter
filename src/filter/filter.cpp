#include "filter.h"
#include "utils/utils.h"

filter::filter(std::string fltr)
    : fltr_(fltr)
{
    std::stringstream ss(fltr_);
    std::vector<std::string> tokens;
    std::string token;
    while (std::getline(ss, token, ' ')) {
        token = trim(token);
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

        id_ = std::stoi(tokens[0]);
        precedence_ = std::stoi(tokens[1]);

        protocol_ = static_cast<uint8_t>(std::stoi(tokens[4]));

        src_ip_ranage_ = get_ip_range(tokens[6]);
        src_port_range_ = get_port_range(tokens[7]);
        dst_ip_ranage_ = get_ip_range(tokens[9]);
        dst_port_range_ = get_port_range(tokens[10]);
}
filter::filter(const filter& other)
    : fltr_(other.fltr_),
      id_(other.id_),
      protocol_(other.protocol_),
      src_ip_ranage_(other.src_ip_ranage_),
      src_port_range_(other.src_port_range_),
      dst_ip_ranage_(other.dst_ip_ranage_),
      dst_port_range_(other.dst_port_range_),
      precedence_(other.precedence_)
{
}




std::string filter::get_filter_as_string()
{
    return fltr_;
}

uint32_t filter::get_id()
{
    return id_;
}

uint8_t filter::get_protocol()
{
    return protocol_;
}

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> filter::get_src_ip_range()
{
    return src_ip_ranage_;
}

std::pair<uint16_t, uint16_t> filter::get_src_port_range()
{
    return src_port_range_;
}

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> filter::get_dst_ip_range()
{
    return dst_ip_ranage_;
}

std::pair<uint16_t, uint16_t> filter::get_dst_port_range()
{
    return dst_port_range_;
}

uint32_t filter::get_precedence()
{
    return precedence_;
}

range filter::get_range_i(int i) {
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
    }
    
}