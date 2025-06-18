#pragma once 


#include <vector>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <vector> 
#include "range.h"
#include "../filter/filter.h"





struct node {
    bool is_terminal;
    std::vector<std::pair<int, node*>> ranges;
    std::vector<filter*> filters;

    node();
};