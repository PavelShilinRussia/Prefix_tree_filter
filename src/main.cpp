#include <iostream>
#include "utils/utils.h"
#include "prefix_tree.h"
#include "tree_operations.h"

#include <netinet/ip.h>

int main(){

    filter* flt1 = new filter("1 163 permit out 6 from 100.60.152.105/13 20738-30280 to 42.232.148.74/6 17079-50101");
    filter* flt2 = new filter("2 163 permit out 6 from 100.60.152.105/13 9158-22156 to 81.95.0.124/21 6772-30121");
    auto tree = prefix_tree();

    insert_flt(tree.root, flt1);
    insert_flt(tree.root, flt2);

    return 0;
}

