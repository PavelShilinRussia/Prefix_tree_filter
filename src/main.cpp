#include <iostream>
#include <fstream>
#include "utils/utils.h"
#include "prefix_tree.h"
#include "tree_operations.h"
#include <netinet/ip.h>
#include <chrono>
#include <memory>

struct result {
    size_t record_idx;
    unsigned int filter_idx;
};

int main() {
    
    std::vector<filter*> filters = {};
    auto tree = prefix_tree();

    std::ifstream filt_file("../src/filters.txt");

    
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
    std::ifstream pack_file("../src/packets", std::ios::binary);
    
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
    
    

    std::ofstream out;         
    size_t all = 0;
    out.open("../result.txt");  
    
    std::unique_ptr<result[]> results{new result[packets.size()]{}};
    size_t next_result_id = 0;
    
    size_t idx = 0;
    for (auto i : packets){
        auto begin = ts();
        filter* flt = tree.match(i);
        if (flt != nullptr){
            results[next_result_id++] = {.record_idx = idx, .filter_idx = flt->id_};
        }
        idx++;
        auto end = ts();
  
        auto elapsed_ms = end - begin;
        all += elapsed_ms;
        
    }

    for (size_t i = 0; i < next_result_id; ++i) {
        size_t const j = results[i].record_idx;
        out << j <<" "<< (int) packets[j].proto << " " << int_to_ip(packets[j].src_ip) << " " << packets[j].src_port << " " << int_to_ip(packets[j].dst_ip) << " " << packets[j].dst_port << " matched filter " << results[i].filter_idx << std::endl;
    }

    std::cout << "Total time: " << all << " us" <<  std::endl;
    std::cout << "Avarage match time: " << all/(double)idx << " us in " << idx << " matches" << std::endl;

    
    out.close(); 
    return 0;
}

