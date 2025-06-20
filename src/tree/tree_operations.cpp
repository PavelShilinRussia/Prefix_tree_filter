#include "tree_operations.h"
#include "filter/filter.h"
#include <vector>
#include <utility>
#include <algorithm>


void sorted_insert(std::vector<std::pair<int, node *>> &ranges, const std::pair<int, node *> &new_pair)
{
    auto it = std::lower_bound(ranges.begin(), ranges.end(), new_pair,
                               [](const std::pair<int, node *> &a, const std::pair<int, node *> &b)
                               {
                                   return a.first < b.first;
                               });

    ranges.insert(it, new_pair);
}


void sorted_insert_filter(std::vector<filter*>& vect, filter* flt)
{
    auto it = std::lower_bound(vect.begin(), vect.end(), flt,
                               [](filter* a, filter* b)
                               {
                                   return a->precedence_ > b->precedence_;
                               });

    vect.insert(it, flt);
}



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

void insert_flt(node *current_node, filter *filter, int num_of_range_in_filter)
{

    sorted_insert_filter(current_node->filters, filter);


    if (num_of_range_in_filter == 5){
        current_node->is_terminal = true;
        return;
    }

    auto [lb, ub] = filter->get_range_i(num_of_range_in_filter);
    node *no_intersections_node = new node();

    int i = 0;
    while (i <= current_node->ranges.size())
    {
        // auto this_range_start = current_node->ranges[i].first;
        // auto next_range_start = current_node->ranges[i+1].first;
        if ( lb == current_node->ranges[i].first )
        {
            if (current_node->ranges[i].second == nullptr){
                i ++;
                continue;
            }

            if (current_node->ranges[i + 1].first > ub + 1) {
                sorted_insert(current_node->ranges, std::make_pair(ub + 1, current_node->ranges[i].second));
                node *deep_copied_node = deep_copy_node(current_node->ranges[i].second);
                current_node->ranges[i].second = deep_copied_node;

                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                return;
            } else if (current_node->ranges[i + 1].first < ub + 1) {

                if (i == current_node->ranges.size() - 2 || current_node->ranges[i + 2].first > ub + 1) {
                    sorted_insert(current_node->ranges, std::make_pair(ub + 1, nullptr));
                    current_node->ranges[i + 1].second = no_intersections_node;
                    if (no_intersections_node->filters.size() == 0)
                    {
                        insert_flt(no_intersections_node, filter, num_of_range_in_filter + 1);
                    }
                    insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                    return;
                } else if(current_node->ranges[i + 2].first == ub + 1){
                    current_node->ranges[i + 1].second = no_intersections_node;
                    if (no_intersections_node->filters.size() == 0)
                    {
                        insert_flt(no_intersections_node, filter, num_of_range_in_filter + 1);
                    }
                    insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                    return;
                } else {
                    lb = current_node->ranges[i + 2].first;
                    insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                }
            } else if (current_node->ranges[i + 1].first == ub + 1) {
                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                return;
            }
        }
        else if ( lb > current_node->ranges[i].first ) {
            if (i+1 == current_node->ranges.size()) {
                if (lb > current_node->ranges[i].first){
                    sorted_insert(current_node->ranges, std::make_pair(lb, no_intersections_node));
                } else if (lb == current_node->ranges[i].first) {
                    current_node->ranges[i-1].second = no_intersections_node;
                }
                sorted_insert(current_node->ranges, std::make_pair(ub + 1, nullptr));
                if (no_intersections_node->filters.size() == 0) {
                    insert_flt(no_intersections_node, filter, num_of_range_in_filter + 1);
                }

                
                i ++;
                return;
            }
            i ++;
            continue;
        }
        else if ( lb < current_node->ranges[i].first )
        {
            if (current_node->ranges[i - 1].second == nullptr) {
                sorted_insert(current_node->ranges, std::make_pair(lb, no_intersections_node));
                i++;
                if (no_intersections_node->filters.size() == 0) {
                    insert_flt(no_intersections_node, filter, num_of_range_in_filter + 1);
                }
            } else {
                node *deep_copied_node = deep_copy_node(current_node->ranges[i-1].second);
                sorted_insert(current_node->ranges, std::make_pair(lb, deep_copied_node));
                insert_flt(deep_copied_node, filter, num_of_range_in_filter + 1);
            }

            if (ub + 1 < current_node->ranges[i].first) {
                sorted_insert(current_node->ranges, std::make_pair(ub + 1, current_node->ranges[i-2].second));
                return;
            } else if(ub + 1 == current_node->ranges[i].first) {
                return;
            } else {
                lb = current_node->ranges[i].first;
                continue;
            }
        }
        i++;
    }
    
}
