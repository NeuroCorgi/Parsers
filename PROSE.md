# Parsing

The parsing problem is actually thoroughly studied and considered solved, so this is going to be a short explanation.

## Introduction

### What is parsing

Strings are just arrays of characters and do not posses any useful information. However, the major part of a day-to-day information are strings, and there should be a way how to extract information from meaningless array. This was is parsing.

Parsing is the process of analysing a string conforming to the rules of a formal grammar. What grammar is will be explained later. Now, how is the process can be useful? By analysing the string one of two things can become clear either the structure of the string, usually in a form of a tree, or that it does not contain any useful information to work with.

### What is grammar

Grammar describes all possible structures that could be a result of parsing and restrictions, because without restrictions parsing would be trivial.

To explain parts of a grammar generative power of the last will be taken into consideration. Grammar consists of a set of non-terminal symbols, symbols that can be transformed into other symbols, and of terminal symbols with obvious meaning. Set of production rules of a grammar defines all possible transformation of one sequence of symbols (left-hand side) to another (right-hand side). The grammar starting symbol is an element of the set of non-terminals and an element to start the process of generation.

Most of the programming languages are using context free grammar of type 2 grammar, according to the [chomsky hierarchy](https://en.wikipedia.org/wiki/Chomsky_hierarchy). In this kind of grammar, production rules are restricted with only one symbol in the left-hand side possible.

## Applications 

Parsers are applicable in various fields. Some usage examples will be shown.

### Compilers frontend

Parsers are used to transform the source code to the abstract syntax tree, as was states in the `what is parsing` the form that is easier to work with.

To see a syntax tree, for example, python `ast` library can be used

### Regular expressions

Regular expressions are used in various fields, for example, in the `grep` command or data validation.

Regular expressions are type 3 grammar. 

## Implementation

### Unger parser

Unger parser is a simple parser that can be used to parse simple arithmetic expressions. It is a [top-down](https://en.wikipedia.org/wiki/Top-down_parsing) parser, which means that it starts with the starting symbol and then tries to find the right production rule to transform the symbol to the right-hand side. It is also a non-directional parser, therefore it needs the whole input to be able to parse it.

### Grammar

For the sake of simplicity, the grammar is going to be a simple arithmetic grammar defined as a map, where the key is the non-terminal symbol and the value is a set of possible right-hand sides. Non-terminal symbols are surrounded by `<` and `>`.

```cpp
map<string, set<vector<string>>> grammar = {
    {"<expr>",    { {"<term>"}, {"<term>", "+", "<expr>"}, {"<term>", "-", "<expr>"}       }},
    {"<term>",    { {"<factor>"}, {"<factor>", "*", "<term>"}, {"<factor>", "/", "<term>"} }},
    {"<factor>",  { {"(", "<expr>", ")"}, {"<digit>"}                                      }},
    {"<digit>",   { {"0", "<digit_l>"}, {"1", "<digit_l>"}, ..., {"9", "<digit_l>"}        }},
    {"<digit_l>", { {""}, {"<digit>"}                                                      }}
};
```

### Parser

The parser function is a recursive function that takes input string and current symbol and returns a tree. 

```cpp
tree parser(string input, string symbol);
```

If the current symbol is the input string, then the tree is created with the symbol as a root and without any children.

```cpp
if (input == symbol) {
    return {symbol, {}};
}
```

If there is no production rule for the current symbol, then the input string is not parsable by the grammar from the given symbol and empty tree is returned.

```cpp
if (!grammar.contains(symbol)) {
    return {};
}
```

Otherwise, the parser tries to find the right production rule for the current symbol. The input string is divided into substrings, so the number of  substrings is equal to the number of symbols in the right-hand side of the production rule. The parser is called recursively for each substring and the symbol from the right-hand side of the production rule. If the parser returns an empty tree, then the production rule is not valid and the next one is tried. If the parser returns a tree, then the tree is created with the current symbol as a root and the trees returned by the parser as children. If the parser returns a tree for all substrings, then the tree is returned.

```cpp
for (auto rule : grammar[symbol]) {
    for (auto substr : substrings(input, rule.size())) {
        vector<tree> children;
        bool valid = true;

        for (int i = 0; i < rule.size(); i++) {
            tree child = parser(substr[i], rule[i]);
            if (child.empty()) {
                valid = false;
                break;
            }
            children.push_back(child);
        }

        if (valid) {
            return {symbol, children};
        }
    }
}
```

## Future reading

As a book for better explanation on a topic, `Parsing Techniques: A practical guide` can be a good option, because of its list of links to the original papers and studies of parsing.

## References

- [wikipedia](https://en.wikipedia.org/wiki/Parsing#Computer_languages)
- [Parsing Techniques: A practical guide](https://www.dickgrune.com/Books/PTAPG_2nd_Edition/index.html)
- [Chomsky hierarchy](https://en.wikipedia.org/wiki/Chomsky_hierarchy)
- [Top-down parsing](https://en.wikipedia.org/wiki/Top-down_parsing)
- [Unger parser](https://en.wikipedia.org/wiki/Unger_parser)
- [ast](https://docs.python.org/3/library/ast.html)
