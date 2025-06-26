#include "tree_operations.h"
#include <vector>
#include <utility>
#include <algorithm>

std::shared_ptr<node> deep_copy_node(const std::shared_ptr<node>& source) {
    if (!source) {
        return nullptr;
    }

    auto new_node = std::make_shared<node>();
    new_node->is_terminal = source->is_terminal;
    new_node->ranges.clear();
    new_node->ranges.reserve(source->ranges.size());
    for (const auto& range_pair : source->ranges) {
        auto copied_child = deep_copy_node(range_pair.second);
        new_node->ranges.emplace_back(range_pair.first, copied_child);
    }

    new_node->filters.reserve(source->filters.size());
    for (const auto& f : source->filters) {
        new_node->filters.push_back(f); // Копируем shared_ptr, увеличивая счётчик ссылок
    }

    return new_node;
}