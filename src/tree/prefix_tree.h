#pragma once
#include <cstdint>
#include "prefix_tree_node.h"
#include "filter/filter.h"
#include "filter/packet.h"
struct prefix_tree {
    std::shared_ptr<node> root;

    prefix_tree();
    std::shared_ptr<filter> match(packet& packet);
    void insert(std::shared_ptr<filter> filter);
    void insert_recursive(std::shared_ptr<node> current_node, std::shared_ptr<filter> filter, int num_of_range_in_filter = 0);
};