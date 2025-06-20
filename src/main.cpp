#include <iostream>
#include <fstream>
#include "utils/utils.h"
#include "prefix_tree.h"
#include "tree_operations.h"

#include <netinet/ip.h>

int main() {
    
    // auto f1 = prepare_filter("1 183 permit out 6 from 100.60.152.105/13 20738-30280 to 42.232.148.74/6 17079-50101");
    // auto f2 = prepare_filter( "2 163 permit out 6 from 100.60.152.105/13 9158-22156 to 81.95.0.124/21 6772-30121");
    // auto f3 = prepare_filter( "3 200 permit out 6 from 100.60.152.105/13 20738-30280 to 42.232.148.74/6 17079-50101");
    
    std::vector<filter*> filters = {};
    auto tree = prefix_tree();

    std::ifstream filt_file("src/filters.txt");
    if (!filt_file.is_open()) {
        std::cerr << "Не удалось открыть файлс фильтрами\n";
        return 1;
    }

    std::string line;
    while (std::getline(filt_file, line)) { 
        auto f = prepare_filter(line);
        if (not f) {
            perror("error while preparing filters from string\n");
            return -1;
        }          
        auto a = f.get_range_i(1);
        filters.push_back(&f);
        
        tree.insert(filters[filters.size() - 1]);
    }


    std::vector<packet> packets;
    std::ifstream pack_file("src/packets", std::ios::binary);
    
    if (!pack_file.is_open()) {
        std::cerr << "Не удалось открыть файл c пакетами\n";
        return 1;
    }

    packet packet;
    while (pack_file.read(reinterpret_cast<char*>(&packet), 32)) {
        packet.src_ip = ntohl(packet.src_ip);
        packet.dst_ip = ntohl(packet.dst_ip);
        packet.src_port = ntohs(packet.src_port);
        packet.dst_port = ntohs(packet.dst_port);
        packets.push_back(packet);
    }

    pack_file.close();

    uint8_t a = packets[12].header[9];

    for (auto i : packets){
        filter* flt = tree.match(i);
        if (flt != nullptr){
            std::cout << flt->id_ << std::endl;
        }
        else {
            std::cout << "no filter" << std::endl;
        }
    }
    
    
    return 0;
}

