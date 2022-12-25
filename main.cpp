#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>

#include "parser.h"
#include "utils.h"

/// @brief Sample function to test the parsed tree
///
/// @param os output stream
/// @param tree parse tree
///
/// @return output stream
std::ostream& operator<<(std::ostream& os, const parser::parse_tree& tree) {
    // Pretty-printing is left as an exercise for the reader

    if (tree.symbol.empty()) return os;

    os << tree.symbol;

    if (tree.children.empty()) {
        os << '\n';
        return os;
    }

    os << " -> {\n";
    for (const auto& child : tree.children) {
        os << child;
    }
    os << "}\n";
    return os;
}

int main() {
    std::cout << "Enter an expression to parse or 'exit' to quit\n";
    std::cout << "Please do not use spaces in the expression (e.g. 1+2 instead of 1 + 2)\n";
    std::cout << "and do not enter empty strings\n";
    
    std::string str;

    const std::unordered_map<std::string, std::deque<std::deque<std::string>>> grammar = {
        {"<expr>", {{"<term>"}, {"<term>", "+", "<expr>"}, {"<term>", "-", "<expr>"}}},
        {"<term>", {{"<factor>"}, {"<factor>", "*", "<term>"}, {"<factor>", "/", "<term>"}}},
        {"<factor>", {{"(", "<expr>", ")"}, {"<digit>"}}},
        {"<digit>", {{"0", "<digit_l>"}, {"1", "<digit_l>"}, {"2", "<digit_l>"}, {"3", "<digit_l>"}, {"4", "<digit_l>"}, {"5", "<digit_l>"}, {"6", "<digit_l>"}, {"7", "<digit_l>"}, {"8", "<digit_l>"}, {"9", "<digit_l>"}}},
        {"<digit_l>", {{""}, {"<digit>"}}}
    };

    parser::unger_parser parser{grammar};

    while (-42) {

        std::cout << "expr> ";
        std::cin >> str;

        if (str == "exit") break;

        if (auto tree = parser(str)) {
            std::cout << tree.value();
        } else {
            std::cout << "Not part of a grammar\n";
        }
    }

    std::cout << "Fortitudine vincimus.\n"; // Might fail

    return 0;
}