#include "parser.h"
#include "utils.h"

#include <algorithm>
#include <unordered_map>

parser::unger_parser::unger_parser(std::unordered_map<std::string, std::deque<std::deque<std::string>>> grammar) :
    _grammar{grammar} {}

std::optional<parser::parse_tree> parser::unger_parser::operator()(const std::string_view& input) const noexcept {
    const std::string WHITESPACE = " \n\r\t\f\v";

    std::vector<parser::unger_parser::parse_node> history;
    std::string start = "<expr>";

    // Trim whitespace
    auto r = input.find_first_not_of(WHITESPACE);
    auto l = input.find_last_not_of(WHITESPACE);
    auto trimmed_input = input.substr(r, l-r+1);

    // Assume that empty strings are ambiguous and cannot be parsed
    if (trimmed_input.empty()) return std::nullopt;

    return _parse(trimmed_input, start, history);
}

std::optional<parser::parse_tree> parser::unger_parser::_parse(const std::string_view& input, const std::string_view& symbol, std::vector<parser::unger_parser::parse_node>& history) const noexcept {
    using parser::unger_parser;

    // Check for loops in the grammar
    if (std::find(history.begin(), history.end(), parse_node{symbol, input} ) != history.end())
        return std::nullopt;
    
    // If the symbol is the input and, therefore, a terminal, return the parse tree
    if (input == symbol)
        return parser::parse_tree{ symbol.data(), {} };

    // If there is no rule for the symbol, return std::nullopt
    if (!_grammar.contains(symbol.data()))
        return std::nullopt;

    // Add to history to avoid loops in the future
    history.push_back(parse_node{symbol, input});

    // Try to parse the input with each rule for the symbol
    for (const auto& derivable : _grammar.at(symbol.data())) {
        for (const auto& part : parser::utils::partition(input, derivable.size(), true)) {
            auto f = true;
            auto tree = parser::parse_tree{symbol.data(), {}};

            // That is my python zip equivalent
            auto p = part.begin();
            auto d = derivable.begin();
            for (; f && p != part.end() && d != derivable.end(); ++p, ++d) {
                // Recursively parse the part
                if (auto sub_tree = _parse(*p, *d, history)) {
                    tree.children.push_back(sub_tree.value());
                } else {
                    f = false;
                }
            }
            if (f) {
                history.pop_back();
                return tree;
            }
        }
    }

    history.pop_back();

    return std::nullopt;
}