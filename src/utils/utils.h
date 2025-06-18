#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include <arpa/inet.h>
#include "tree/range.h"
#include "filter/filter.h"


std::pair<std::vector<uint8_t>, std::vector<uint8_t>> get_ip_range(const std::string& ip_mask);
std::pair<uint16_t, uint16_t> get_port_range( std::string );
std::vector<range> filter_to_vector_of_ranges(filter* fltr);
std::string trim(const std::string& str);