#include "tree_operations.h"
#include "filter/filter.h"
#include <vector>
#include <utility>
#include <algorithm>


node *deep_copy_node(const node *source)
{
    if (!source)
    {
        return nullptr;
    }

    node *new_node = new node();
    new_node->is_terminal = source->is_terminal;

    new_node->ranges.reserve(source->ranges.size());
    for (const auto &range_pair : source->ranges)
    {
        node *copied_child = deep_copy_node(range_pair.second);
        new_node->ranges.emplace_back(range_pair.first, copied_child);
    }

    new_node->filters.reserve(source->filters.size());
    for (const filter *f : source->filters)
    {
        new_node->filters.push_back(new filter(*f));
    }

    return new_node;
}

