#include "prefix_tree_node.h"
#include "filter/filter.h"
#include "utils/utils.h"


void insert_flt(node *current_node, filter *filter, int num_of_range_in_filter = 0);

node *deep_copy_node(const node *source);

void sorted_insert(std::vector<std::pair<int, node *>> &ranges, const std::pair<int, node *> &new_pair);