#include "utils.h"

#include <iostream>

std::deque<std::deque<std::string_view>> parser::utils::partition(const std::string_view& str, std::size_t n, bool empty) {
    std::deque<std::deque<std::string_view>> res;

    // If empty substrings are not allowed and number of partitions is greater than string size, return empty result
    // dirichlet principle
    if (!empty && str.size() < n) {
        return res;
    }

    // There is only one way to partition a string into one part
    if (n == 1) {
        std::deque<std::string_view> sub_res;
        sub_res.push_back(str);
        res.push_back(sub_res);
        return res;
    }

    auto max_part_length = str.size();
    if (!empty)
        max_part_length -= n - 1;

    for (std::size_t length = empty ? 0 : 1; length <= max_part_length; ++length) {
        // Recursively partition the rest of the string into n - 1 parts
        for (auto part : parser::utils::partition(str.substr(length, str.size() - length + 1), n - 1, empty)) {
            
            // Deque is used to make push_front fast
            part.push_front(str.substr(0, length));
            res.push_back(part);
        }
    }

    return res;
}