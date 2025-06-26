#include "prefix_tree.h"
#include "utils/utils.h"
#include <algorithm>
#include "tree_operations.h"
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

        auto it = std::lower_bound(current_node->ranges.begin(), current_node->ranges.end(), i,
            [](const std::pair<uint64_t, std::shared_ptr<node>>& a, int b) {
                return a.first < b;
            });

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
    auto no_intersections_node = std::make_shared<node>();

    size_t i = 0;
    while (i < current_node->ranges.size()) {
        if (lb == current_node->ranges[i].first) {
            if (!current_node->ranges[i].second) {
                if (i + 1 == current_node->ranges.size()) {
                    current_node->ranges[i].second = no_intersections_node;
                    sorted_insert(current_node->ranges, std::make_pair(ub + 1, nullptr));
                    if (no_intersections_node->filters.empty()) {
                        insert_recursive(no_intersections_node, filter, num_of_range_in_filter + 1);
                    }
                    return;
                }
                i++;
                continue;
            }
            auto deep_copied_node = deep_copy_node(current_node->ranges[i].second);
            insert_recursive(deep_copied_node, filter, num_of_range_in_filter + 1);

            if (ub + 1 < current_node->ranges[i + 1].first) {
                sorted_insert(current_node->ranges, std::make_pair(ub + 1, current_node->ranges[i].second));
                current_node->ranges[i].second = deep_copied_node;
                return;
            } else if (ub + 1 > current_node->ranges[i + 1].first) {
                current_node->ranges[i].second = deep_copied_node;
                lb = current_node->ranges[i + 1].first;
                continue;
            } else if (ub + 1 == current_node->ranges[i + 1].first) {
                current_node->ranges[i].second = deep_copied_node;
                return;
            }
        } else if (lb > current_node->ranges[i].first) {
            if (i + 1 == current_node->ranges.size()) {
                if (lb > current_node->ranges[i].first) {
                    sorted_insert(current_node->ranges, std::make_pair(lb, no_intersections_node));
                } else if (lb == current_node->ranges[i].first) {
                    current_node->ranges[i - 1].second = no_intersections_node;
                }
                if (no_intersections_node->filters.empty()) {
                    insert_recursive(no_intersections_node, filter, num_of_range_in_filter + 1);
                }
                sorted_insert(current_node->ranges, std::make_pair(ub + 1, nullptr));
                i++;
                return;
            }
            i++;
            continue;
        } else if (lb < current_node->ranges[i].first) {
            if (!current_node->ranges[i - 1].second) {
                if (lb == current_node->ranges[i - 1].first) {
                    current_node->ranges[i - 1].second = no_intersections_node;
                } else {
                    sorted_insert(current_node->ranges, std::make_pair(lb, no_intersections_node));
                    i++;
                }
                if (no_intersections_node->filters.empty()) {
                    insert_recursive(no_intersections_node, filter, num_of_range_in_filter + 1);
                }
                if (ub + 1 < current_node->ranges[i].first) {
                    sorted_insert(current_node->ranges, std::make_pair(ub + 1, nullptr));
                    return;
                } else if (ub + 1 == current_node->ranges[i].first) {
                    return;
                }
            } else {
                auto deep_copied_node = deep_copy_node(current_node->ranges[i - 1].second);
                sorted_insert(current_node->ranges, std::make_pair(lb, deep_copied_node));
                i++;
                insert_recursive(deep_copied_node, filter, num_of_range_in_filter + 1);
                if (ub + 1 < current_node->ranges[i].first) {
                    sorted_insert(current_node->ranges, std::make_pair(ub + 1, current_node->ranges[i - 2].second));
                    return;
                } else if (ub + 1 == current_node->ranges[i].first) {
                    return;
                }
            }
            lb = current_node->ranges[i].first;
            continue;
        }
        i++;
    }
}