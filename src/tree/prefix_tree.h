#pragma once
#include <cstdint>
#include "prefix_tree_node.h"
#include "filter/filter.h"
#include "filter/data.h"
struct prefix_tree{
public:
    prefix_tree();
    filter* match(data& data);
    node* root; 
};