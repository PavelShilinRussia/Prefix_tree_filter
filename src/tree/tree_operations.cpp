#include "tree_operations.h"







void insert(node *root, filter *filter)
{
    node* current = root;
    auto inserted_ranges = filter_to_vector_of_ranges(filter);
    
    for (auto inserted_range: inserted_ranges){
        for (auto desc: current->desc){
        }
    }


}
