#include <vector>
#include <iostream>
#include <cstdint>
#include <unordered_map>
#include <map>
#include <vector> 
#include "range.h"

struct node {
    bool is_terminal;
    std::vector<std::pair<range, node*>> desc;
    std::vector<filter*> filters;

    node();
};