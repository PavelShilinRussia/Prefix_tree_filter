#pragma once 


#include <vector>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <vector> 
#include "../filter/filter.h"





struct node {
    bool is_terminal;
    std::vector<std::pair<uint64_t, node*>> ranges;
    std::vector<filter*> filters;

    node();
};