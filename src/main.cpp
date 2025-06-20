#include <iostream>
#include "utils/utils.h"
#include "prefix_tree.h"
#include "tree_operations.h"

#include <netinet/ip.h>

int main() {
    
    auto f1 = prepare_filter("1 183 permit out 6 from 100.60.152.105/13 20738-30280 to 42.232.148.74/6 17079-50101");
    auto f2 = prepare_filter( "2 163 permit out 6 from 100.60.152.105/13 9158-22156 to 81.95.0.124/21 6772-30121");
    auto f3 = prepare_filter( "3 200 permit out 6 from 100.60.152.105/13 20738-30280 to 42.232.148.74/6 17079-50101");
    
    if (not f1 or not f2 or not f3) {
        perror("error while preparing filters fro string\n");
        return -1;
    }

    auto tree = prefix_tree();

    insert_flt(tree.root, &f1);
    insert_flt(tree.root, &f2);
    insert_flt(tree.root, &f3);


    data dt = data(6, ntohl(inet_addr("100.63.255.213")), 30000, ntohl(inet_addr("41.41.255.251")), 19000);

    filter* flt = tree.match(dt);
    if (flt != nullptr){
        std::cout << flt->id_ << std::endl;
    }
    else {
        std::cout << "no filter";
    }
    
    


    return 0;
}

