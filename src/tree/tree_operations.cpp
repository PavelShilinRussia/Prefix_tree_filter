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


node* deep_copy_node(const node* source) {
    if (!source) {
        return nullptr;
    }

    node* new_node = new node();
    new_node->is_terminal = source->is_terminal;

    new_node->ranges.reserve(source->ranges.size());
    for (const auto& range_pair : source->ranges) {
        node* copied_child = deep_copy_node(range_pair.second);
        new_node->ranges.emplace_back(range_pair.first, copied_child);
    }

    new_node->filters.reserve(source->filters.size());
    for (const filter* f : source->filters) {
        new_node->filters.push_back(new filter(*f));
    }

    return new_node;
}


void insert_flt(node *current_node, filter *filter, int num_of_range_in_filter=0)
{
    range flt_part = filter->get_range_i(num_of_range_in_filter);
    node* no_intersections_node  = new node();

    int i = 0;
    while (i <  current_node->ranges.size()) {

        current_node->filters.push_back(filter);

        
        if ( current_node->ranges[i].first == flt_part.min_value ){
            if ( current_node->ranges[i+1].first > flt_part.max_value ){
                sorted_insert(current_node->ranges, std::make_pair(flt_part.max_value, current_node->ranges[i].second));
                node* deep_copied_node = deep_copy_node(current_node->ranges[i].second);
                current_node->ranges[i].second = deep_copied_node;


                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                break;
            }
            else if( current_node->ranges[i+1].first < flt_part.max_value ){

                current_node->ranges[i+1].second = no_intersections_node;
                if( no_intersections_node->filters.size() == 0 ){
                        insert_flt(no_intersections_node, filter, num_of_range_in_filter + 1);
                    }
                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);

                if( i == current_node->ranges.size() - 2 || current_node->ranges[i+2].first > flt_part.max_value ){
                    sorted_insert(current_node->ranges, std::make_pair(flt_part.max_value, nullptr));
                    break;
                }
                else if ( current_node->ranges[i+2].first < flt_part.max_value ){
                    flt_part.min_value == current_node -> ranges[i+2].first;
                }
                
            }
            else if( current_node->ranges[i+1].first == flt_part.max_value ){
                
                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                break;
            }
        }
        else if(current_node->ranges[i].first < flt_part.min_value){
            continue;
        }
        else if(current_node->ranges[i].first > flt_part.min_value){

          
            sorted_insert(current_node->ranges, std::make_pair(flt_part.min_value, no_intersections_node));
        
            if(current_node->ranges[i+1].first < flt_part.max_value){
                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                current_node->ranges[i + 1].second = no_intersections_node;
                if( no_intersections_node->filters.size() == 0 ){
                        insert_flt(no_intersections_node, filter, num_of_range_in_filter + 1);
                    }

                if( i == current_node->ranges.size() - 2 || current_node->ranges[i+2].first > flt_part.max_value ){
                    sorted_insert(current_node->ranges, std::make_pair(flt_part.max_value, nullptr));
                    
                    break;
                }
                else if( current_node->ranges[i+2].first < flt_part.max_value ){
                    flt_part.min_value == current_node -> ranges[i+2].first;
                }
                
            }
            else if( current_node->ranges[i+1].first > flt_part.max_value ){
                sorted_insert(current_node->ranges, std::make_pair(flt_part.max_value, current_node->ranges[i].second));

                node* deep_copied_node = deep_copy_node(current_node->ranges[i].second);
                current_node->ranges[i].second = deep_copied_node;
                
                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                if( no_intersections_node->filters.size() == 0 ){
                        insert_flt(no_intersections_node, filter, num_of_range_in_filter + 1);
                    }
                    break;
                }
            else if ( current_node->ranges[i+1].first == flt_part.max_value  ){
                insert_flt(current_node->ranges[i].second, filter, num_of_range_in_filter + 1);
                break;
            }

        }
        i ++;
    }
}


    
