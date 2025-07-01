#pragma once
#include "prefix_tree_node.h"
#include "filter/filter.h"

std::shared_ptr<node> selective_deep_copy_node(const std::shared_ptr<node>& source, std::shared_ptr<filter> filter, int num_of_range_in_filter);