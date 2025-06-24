#include <iostream>
#include <fstream>
#include "utils/utils.h"
#include "prefix_tree.h"
#include "tree_operations.h"
#include <netinet/ip.h>

int main() {
    
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


    int i = 0;
    std::ofstream pac;   
    pac.open("packets.txt");
          
    while (pack_file.read(reinterpret_cast<char*>(&pack), 32)) {
        pack.src_ip = pack.src_ip;
        pack.dst_ip = pack.dst_ip;
        pack.src_port = pack.src_port;
        pack.dst_port = pack.dst_port;
        packets.push_back(pack);
        pac << pack.proto << " " <<  pack.src_ip << " " << pack.src_port << " " << pack.dst_ip << " " << pack.dst_port << std::endl;
    }

    pack_file.close();
    pac.close();
    

    // uint8_t a = packets[12].header[9];

    // packet* a = new packet;
    // a->src_ip = ntohl(inet_addr("98.112.162.172"));
    // a->dst_ip = ntohl(inet_addr("96.203.245.144"));
    // a->src_port = 34934;
    // a->dst_port = 13276;
    // packets.push_back(*a);
    // a->header[9] == 6;
    // auto b = a->return_as_vector();

    std::ofstream out;         
    out.open("out.txt");      
    
    

    size_t idx = 1;
    for (auto i : packets){

        filter* flt = tree.match(i);
        if (flt != nullptr){
            out << idx <<" "<< flt->id_ << std::endl;
        }
        else {
            //std::cout << "no filter" << std::endl;
        }
        idx++;
    }
    
    out.close(); 
    return 0;
}

