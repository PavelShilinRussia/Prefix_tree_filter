#pragma once
#include <string>
#include <vector>
#include <memory>
#include "prefix_tree.h"
#include "filter/filter.h"
#include "filter/packet.h"

struct packet_filter_app {
    std::vector<std::shared_ptr<filter>> filters;
    prefix_tree tree;

    packet_filter_app(const std::string& filters_file_path);
    void filter_packets_file(const std::string& packets_file_path, const std::string& output_file_path);
};