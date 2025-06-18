#pragma once
#include <cstdint>
#include "prefix_tree_node.h"
#include "filter/filter.h"

struct prefix_tree{
public:
    prefix_tree();
    //int find_filter(const int& value);
    node* root; 
};