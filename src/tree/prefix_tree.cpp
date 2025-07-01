#include "prefix_tree.h"
#include "utils/utils.h"
#include <algorithm>
#include "tree_operations.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <fstream>
#include <iostream>

prefix_tree::prefix_tree() {
    root = std::make_shared<node>();
}

std::shared_ptr<filter> prefix_tree::match(packet& packet) {
    auto dt_vect = packet.return_as_vector();
    std::shared_ptr<node> current_node = root;

    for (auto i : dt_vect) {
        if (!current_node) {
            return nullptr;
        }

        if (current_node->is_terminal) {
            return current_node->filters.at(0);
        }

        auto it = current_node->ranges.lower_bound(i);
        if (it == current_node->ranges.end() || it->first > i) {
            if (it == current_node->ranges.begin()) {
                return nullptr;
            }
            --it;
        }

        current_node = it->second;
    }

    if (!current_node) {
        return nullptr;
    } else if (current_node->is_terminal) {
        return current_node->filters.at(0);
    }
    return nullptr;
}

void prefix_tree::insert(std::shared_ptr<filter> filter) {
    insert_recursive(root, filter);
}

void prefix_tree::insert_recursive(std::shared_ptr<node> current_node, std::shared_ptr<filter> filter, int num_of_range_in_filter) {
    sorted_insert_filter(current_node->filters, filter);

    if (num_of_range_in_filter == 5) {
        current_node->is_terminal = true;
        return;
    }

    auto [lb, ub] = filter->get_range_i(num_of_range_in_filter);
    if (ub+1 == 0){
        ub --;
    }

    auto no_intersections_node = std::make_shared<node>();

    auto it = current_node->ranges.lower_bound(lb);
    while (it != current_node->ranges.end()) {
        if (lb == it->first) {
            if (!it->second) {
                it->second = no_intersections_node;
                if (no_intersections_node->filters.empty()) {
                    insert_recursive(no_intersections_node, filter, num_of_range_in_filter + 1);
                }
                auto next_it = std::next(it);
                if (next_it == current_node->ranges.end() || ub + 1 < next_it->first) {
                    current_node->ranges[ub + 1] = nullptr;
                }
                return;
            }
            auto deep_copied_node = selective_deep_copy_node(it->second, filter, num_of_range_in_filter + 1);
            insert_recursive(deep_copied_node, filter, num_of_range_in_filter + 1);
            auto next_it = std::next(it);
            if (next_it == current_node->ranges.end() || ub + 1 < next_it->first) {
                current_node->ranges[ub + 1] = it->second;
                it->second = deep_copied_node;
                return;
            } else if (ub + 1 == next_it->first) {
                it->second = deep_copied_node;
                return;
            } else {
                it->second = deep_copied_node;
                lb = next_it->first;
                it = next_it;
                continue;
            }
        } else if (lb < it->first) {
            auto prev_it = it == current_node->ranges.begin() ? current_node->ranges.end() : std::prev(it);
            if (prev_it == current_node->ranges.end() || !prev_it->second) {
                current_node->ranges[lb] = no_intersections_node;
                if (no_intersections_node->filters.empty()) {
                    insert_recursive(no_intersections_node, filter, num_of_range_in_filter + 1);
                }
                if (it == current_node->ranges.end() || ub + 1 < it->first) {
                    current_node->ranges[ub + 1] = nullptr;
                    return;
                } else if (ub + 1 == it->first) {
                    return;
                }
            } else {
                auto deep_copied_node = selective_deep_copy_node(prev_it->second, filter, num_of_range_in_filter + 1);
                current_node->ranges[lb] = deep_copied_node;
                insert_recursive(deep_copied_node, filter, num_of_range_in_filter + 1);
                if (it == current_node->ranges.end() || ub + 1 < it->first) {
                    current_node->ranges[ub + 1] = prev_it->second;
                    return;
                } else if (ub + 1 == it->first) {
                    return;
                }
            }
            break;
        }
        ++it;
    }

    auto prev_it = std::prev(current_node->ranges.end());
    current_node->ranges[lb] = no_intersections_node;
    if (no_intersections_node->filters.empty()) {
        insert_recursive(no_intersections_node, filter, num_of_range_in_filter + 1);
    }
    current_node->ranges[ub + 1] = nullptr;
}


