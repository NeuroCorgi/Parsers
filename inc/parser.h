#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <deque>

namespace parser {

    struct parse_tree {
        std::string symbol;
        std::vector<parse_tree> children;
    };

    class unger_parser {
        public:

            /// @brief Constructs a parser from a grammar
            /// 
            /// @param grammar grammar to be used
            explicit unger_parser(std::unordered_map<std::string, std::deque<std::deque<std::string>>> grammar);

            /// @brief Parses a string according to the grammar
            ///
            /// @param input string to be parsed
            /// 
            /// @return Parse tree if successful, std::nullopt otherwise
            std::optional<parse_tree> operator()(const std::string_view& input) const noexcept;

        private:
            struct parse_node {
                std::string_view symbol;
                std::string_view w;

                bool operator==(const parse_node& other) const {
                    return symbol == other.symbol && w == other.w;
                }
            };

            std::optional<parse_tree> _parse(const std::string_view&, const std::string_view&, std::vector<parse_node>&) const noexcept;

            std::unordered_map<std::string, std::deque<std::deque<std::string>>> _grammar;
    };

}

#endif // PARSER_H