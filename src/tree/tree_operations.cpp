#include "tree_operations.h"




#include <vector>
#include <utility>
#include <algorithm>


void sorted_insert(std::vector<std::pair<int, node*>>& ranges, const std::pair<int, node*>& new_pair) {
    auto it = std::lower_bound(ranges.begin(), ranges.end(), new_pair,
                               [](const std::pair<int, node*>& a, const std::pair<int, node*>& b) {
                                   return a.first < b.first; 
                               });
    

    ranges.insert(it, new_pair);
}


void insert(node *root, filter *filter)
{
    node* current = root;
    auto to_insert = filter_to_vector_of_ranges(filter);
    bool match = false;
    for (int i = 0; i < to_insert.size(); i++){
        for (auto condition: current->desc){
            // не пересекаются
            if (condition.first.max_value < to_insert[i].min_value || to_insert[i].max_value < condition.first.min_value){
                node* new_node = new node;
                if (i == to_insert.size() - 1){
                    new_node->is_terminal = true;
                }
                current->desc.push_back(std::make_pair(to_insert[i], new_node));
                current = new_node;
                continue;
            }
            //пересекаются
            int min_all = std::min(condition.first.min_value, to_insert[i].min_value);
            int max_all = std::max(condition.first.max_value, to_insert[i].max_value);

            int intersection_min = std::max(condition.first.min_value, to_insert[i].min_value);
            int intersection_max = std::min(condition.first.max_value, to_insert[i].max_value);

            if (min_all < intersection_min && intersection_max < max_all) {
                range(min_all, intersection_min);
            }
            else if (min_all < intersection_min && intersection_max == max_all){

            }
            else if (max_all > intersection_max && intersection_min == min_all){
                
            }
            range(intersection_min, intersection_max);

            if (intersection_max < max_all) {
                range(intersection_max, max_all);
            }

            
        }
    }


}

void insert_flt(node *current_node, filter *filter, int num_of_range_in_filter=0)
{
    range flt_part = filter->get_range_i(num_of_range_in_filter);
    for (int i = 0; i <  current_node->ranges.size(); i++) {
        current_node->filters.push_back(filter);
        if (current_node->ranges[i].first == flt_part.min_value){
            if (current_node->ranges[i+1].first > flt_part.max_value){
                sorted_insert(current_node->ranges, std::make_pair(flt_part.max_value, current_node->ranges[i].second));
                //сделать deep copy в current_node->ranges[i].second (в начало пересечения)

                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
            }
            else if(current_node->ranges[i+1].first < flt_part.max_value){
                node* new_node = new node();
                current_node->ranges[i+1].second = new_node;
                sorted_insert(current_node->ranges, std::make_pair(flt_part.max_value, nullptr));

                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                insert_flt(current_node->ranges[i + 1].second, filter, num_of_range_in_filter + 1);
            }
            else if(current_node->ranges[i+1].first == flt_part.max_value){
                
                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
            }
        }
        else if(current_node->ranges[i].first < flt_part.min_value){
            continue;
        }
        else if(current_node->ranges[i].first > flt_part.min_value){

        }

    }
}


    
