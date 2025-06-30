#include "packet_filter_app.h"
#include <fstream>
#include <chrono>
#include <memory>
#include <iostream>
#include "utils/utils.h"

struct result {
    size_t record_idx;
    unsigned int filter_idx;
};

packet_filter_app::packet_filter_app(const std::string& filters_file_path) {
    std::ifstream filt_file(filters_file_path);

    if (!filt_file.is_open()) {
        std::cerr << "Не удалось открыть файл с фильтрами\n";
        return;
    }

    std::string line, first, sec, third;
    while (std::getline(filt_file, line)) {
        std::stringstream ss(line);
        ss >> first >> sec;
        std::getline(ss, third);
        auto f = prepare_filter(stoi(first), stoi(sec), third.substr(1));
        if (!f) {
            std::cerr << "Ошибка при подготовке фильтра из строки\n";
            continue;
        }
        filters.push_back(f);
        tree.insert(filters.back());
    }
}

void packet_filter_app::filter_packets_file(const std::string& packets_file_path, const std::string& output_file_path) {
    packet pack;
    std::vector<packet> packets;
    std::ifstream pack_file(packets_file_path, std::ios::binary);

    if (!pack_file.is_open()) {
        std::cerr << "Не удалось открыть файл с пакетами\n";
        return;
    }

    while (pack_file.read(reinterpret_cast<char*>(&pack), 32)) {
        pack.src_ip = pack.src_ip;
        pack.dst_ip = pack.dst_ip;
        pack.src_port = pack.src_port;
        pack.dst_port = pack.dst_port;
        packets.push_back(pack);
    }

    pack_file.close();

    std::ofstream out;
    size_t all = 0;
    out.open("../result.txt");

    std::unique_ptr<result[]> results{new result[packets.size()]};
    size_t next_result_id = 0;

    size_t idx = 0;
    auto begin = ts();
    for (auto& packet : packets) {
        
        auto flt = tree.match(packet);
        if (flt) {
            results[next_result_id++] = {.record_idx = idx, .filter_idx = flt->id_};
        }
        idx++;
    }

    auto end = ts();
    auto elapsed_ms = end - begin;
    all = elapsed_ms;


    for (size_t i = 0; i < next_result_id; ++i) {
        size_t const j = results[i].record_idx;
        out << j << " " << static_cast<int>(packets[j].proto) << " " << int_to_ip(packets[j].src_ip) << " " 
            << packets[j].src_port << " " << int_to_ip(packets[j].dst_ip) << " " << packets[j].dst_port 
            << " matched filter " << results[i].filter_idx << std::endl;
    }

    std::cout << "Total time: " << all << " us" << std::endl;
    std::cout << "Avarage match time: " << all / (double)idx << " us in " << idx << " matches" << std::endl;

    out.close();
}