#ifndef SUPPORT_H
#define SUPPORT_H

#include <deque>
#include <string>
#include <string_view>

namespace parser::utils {

    /// @brief Partitions a string into n parts
    ///
    /// @param input string to be partitioned 
    /// @param n     number of partitions
    /// @param empty if true, empty substrings are included
    ///
    /// @return collection of partitions
    std::deque<std::deque<std::string_view>> partition(const std::string_view& input, std::size_t n, bool empty=false);

}

#endif // SUPPORT_H