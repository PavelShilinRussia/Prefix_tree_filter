#include "prefix_tree.h"

#include "prefix_tree.h"
#include "utils/utils.h"
#include <cstdint>
#include <vector>
#include <algorithm>

prefix_tree::prefix_tree()
{
    root = new node();
}

filter *prefix_tree::match(data& data)
{
    auto dt_vect = data.return_as_vector();
    node* current_node = root;

    for (auto i: dt_vect){

        if (current_node == nullptr) 
        {
                return nullptr;
        }

        if (current_node->is_terminal){
            return current_node->filters.at(0);
        }

        auto it = std::lower_bound(current_node->ranges.begin(), current_node->ranges.end(), i,
                [](const std::pair<int, node*>& a, int b) {
                    return a.first < b;
                });


        if (it == current_node->ranges.end() || it->first > i) {
            if (it == current_node->ranges.begin()) {
                return nullptr; 
            }
            --it;
        }

        current_node =  it->second; 

    }
    
    if (current_node == nullptr) 
        {
                return nullptr;
        }
    else if (current_node->is_terminal){
            return current_node->filters.at(0);
        }
}
