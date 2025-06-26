#pragma once
#include <iostream>
#include <vector>
#include "filter/filter.h"
#include "filter/packet.h"
#include "tree/prefix_tree.h"


struct packet_filter_app
{
    std::vector<filter*> filters;
    prefix_tree tree = prefix_tree();

    packet_filter_app(const std::string& filters_file_path);

    void filter_packets_file(const std::string& packets_file_path, const std::string& output_file_path);

};

