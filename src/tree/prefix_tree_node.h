#pragma once
#include <vector>
#include <memory>
#include <cstdint>
#include <map>
#include "filter/filter.h"

struct node {
    bool is_terminal = false;
    std::map<uint32_t, std::shared_ptr<node>> ranges;
    std::vector<std::shared_ptr<filter>> filters;

    node() {
        ranges.insert(std::make_pair(0, nullptr));
    }
};