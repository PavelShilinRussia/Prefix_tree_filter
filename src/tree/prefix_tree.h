#include <cstdint>
#include "prefix_tree_node.h"
#include "filter/filter.h"

class prefix_tree{
public:
    prefix_tree();
    void insert(filter* filter);
    int find_filter(const int& value);
private:
    node* root; 
};