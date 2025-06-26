#pragma once
#include <vector>
#include <memory>
#include <cstdint>
#include "filter/filter.h"

struct node {
    bool is_terminal = false;
    std::vector<std::pair<uint64_t, std::shared_ptr<node>>> ranges;
    std::vector<std::shared_ptr<filter>> filters;

    node() {
        ranges.push_back(std::make_pair(0, nullptr));
    }
};