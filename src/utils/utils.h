#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include <arpa/inet.h>
#include "tree/range.h"
#include "filter/filter.h"


std::pair<uint32_t, uint32_t> get_ip_range(const std::string&);
std::pair<uint16_t, uint16_t> get_port_range(const std::string& );
std::string trim(const std::string& );