#include "filter.h"
#include "utils/utils.h"

filter::filter(std::string fltr)
    : fltr_( fltr )
{
    std::stringstream ss( fltr_ );
    std::vector<std::string> tokens;
    std::string token;


    std::getline( ss, token, ')' );
    id_ = stoi(token);


    while ( std::getline( ss, token, ',' ) ) {
        tokens.push_back( token );
        
    }
    
     protocol_ = static_cast<uint8_t>(stoi(tokens.at(0)));
     src_ip_ranage_ = get_ip_range( tokens.at( 1 ) );
     src_port_range_ = get_port_range( tokens.at( 2 ) );
     dst_ip_ranage_ = get_ip_range( tokens.at( 3 ) );
     dst_port_range_ = get_port_range( tokens.at( 4 ) );
     precedence_ = std::stoi( tokens.at( 5 ) );
    




}

std::string filter::get_filter_as_string()
{
    return std::string();
}

uint32_t filter::get_id()
{
    return 0;
}

uint8_t filter::get_protocol()
{
    return 0;
}

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> filter::get_src_ip_range()
{
    return src_ip_ranage_;
}

std::pair<uint16_t, uint16_t> filter::get_src_port_range()
{
    return std::pair<uint16_t, uint16_t>();
}

std::pair<std::vector<uint8_t>, std::vector<uint8_t>> filter::get_dst_ip_range()
{
    return std::pair<std::vector<uint8_t>, std::vector<uint8_t>>();
}

std::pair<uint16_t, uint16_t> filter::get_dst_port_range()
{
    return std::pair<uint16_t, uint16_t>();
}

uint32_t filter::get_precedence()
{
    return 0;
}
