#pragma once
#include <cstdint>
#include "prefix_tree_node.h"
#include "filter/filter.h"
#include "filter/packet.h"
struct prefix_tree{
    node* root; 
    prefix_tree();
    filter* match(packet& packet);
    void insert(filter *filter);
    void insert_recursive(node *current_node, filter *filter, int num_of_range_in_filter = 0);
    
};