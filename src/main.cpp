#include <iostream>
#include <fstream>
#include <filesystem>
#include "utils/utils.h"
#include "prefix_tree.h"
#include "tree_operations.h"
#include <netinet/ip.h>
#include <chrono>
#include <memory>
#include "packet_filter_app/packet_filter_app.h"
struct result {
    size_t record_idx;
    unsigned int filter_idx;
};

int main() {

    packet_filter_app app = packet_filter_app("/home/student-lab1/Desktop/Prefix_tree_filter/src/filters_100.txt");
    app.filter_packets_file("/home/student-lab1/Desktop/Prefix_tree_filter/src/packets", "results.txt");
    
    return 0;
}