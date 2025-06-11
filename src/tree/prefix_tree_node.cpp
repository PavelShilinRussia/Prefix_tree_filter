#include "prefix_tree_node.h"

node::node()
{
    ranges.push_back(std::make_pair(0, nullptr));
}