#pragma once
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>
#include <arpa/inet.h>
#include <utility>
#include "filter/filter.h"
#include "prefix_tree_node.h"


std::pair<uint32_t, uint32_t> get_ip_range(const std::string&);
std::pair<uint16_t, uint16_t> get_port_range(const std::string& );
std::string trim(const std::string& );
void sorted_insert(std::vector<std::pair<uint64_t, node *>> &ranges, const std::pair<uint64_t, node *> &new_pair);
void sorted_insert_filter(std::vector<filter*>& vect, filter* flt);