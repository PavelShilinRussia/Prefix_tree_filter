#include <iostream>
#include "utils/utils.h"

int main(){

    std::string filter = "10.10.10.0/12";

    std::pair<std::vector<uint8_t>, std::vector<uint8_t>>  a = get_ip_range(filter);
    
    for (auto i : a.first) {
        std::cout << (int)i << " ";
    } 
    return 0;
}

