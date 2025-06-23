#include <iostream>
#include <fstream>
#include "utils/utils.h"
#include "prefix_tree.h"
#include "tree_operations.h"

#include <netinet/ip.h>

int main() {
    
    // auto f2 = prepare_filter( "2 163 permit out 6 from 100.60.152.105/13 9158-22156 to 81.95.0.124/21 6772-30121");
    // auto f3 = prepare_filter( "3 200 permit out 6 from 100.60.152.105/13 20738-30280 to 42.232.148.74/6 17079-50101");
    
    std::vector<filter*> filters = {};
    auto tree = prefix_tree();

    std::ifstream filt_file("/home/student-lab1/Desktop/Prefix_tree_filter/src/filters.txt");

    
    if (!filt_file.is_open()) {
        std::cerr << "Не удалось открыть файлс фильтрами\n";
        return 1;
    }

    std::string line;
    while (std::getline(filt_file, line)) { 
        filter* f = prepare_filter(line);
        if (not f) {
            perror("error while preparing filters from string\n");
            return -1;
        }          
        filters.push_back(f);
        
        tree.insert(filters[filters.size() - 1]);
    }
    packet pack;
    std::vector<packet> packets;
    std::ifstream pack_file("/home/student-lab1/Desktop/Prefix_tree_filter/src/packets", std::ios::binary);
    
    if (!pack_file.is_open()) {
        std::cerr << "Не удалось открыть файл c пакетами\n";
        return 1;
    }

    while (pack_file.read(reinterpret_cast<char*>(&pack), 32)) {
        pack.src_ip = ntohl(pack.src_ip);
        pack.dst_ip = ntohl(pack.dst_ip);
        pack.src_port = ntohs(pack.src_port);
        pack.dst_port = ntohs(pack.dst_port);
        packets.push_back(pack);
    }

    pack_file.close();

    // uint8_t a = packets[12].header[9];

    // packet* a = new packet;
    // a->src_ip = ntohl(inet_addr("98.112.162.172"));
    // a->dst_ip = ntohl(inet_addr("96.203.245.144"));
    // a->src_port = 34934;
    // a->dst_port = 13276;
    // packets.push_back(*a);
    // a->header[9] == 6;
    // auto b = a->return_as_vector();
    size_t idx = 1;
    for (auto i : packets){
        filter* flt = tree.match(i);
        if (flt != nullptr){
            std::cout << idx << " - " << flt->id_ << std::endl;
        }
        else {
            // std::cout << "no filter" << std::endl;
        }
        idx++;
    }
    
    
    return 0;
}

