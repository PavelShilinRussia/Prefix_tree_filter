#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <utility>
#include "prefix_tree_node.h"
#include "filter/filter.h"

std::pair<uint32_t, uint32_t> get_ip_range(const std::string&);
std::pair<uint16_t, uint16_t> get_port_range(const std::string&);
std::string trim(const std::string&);
void sorted_insert(std::vector<std::pair<uint64_t, std::shared_ptr<node>>>& ranges, const std::pair<uint64_t, std::shared_ptr<node>>& new_pair);
void sorted_insert_filter(std::vector<std::shared_ptr<filter>>& vect, std::shared_ptr<filter> flt);
size_t ts();
std::string int_to_ip(unsigned int ip);