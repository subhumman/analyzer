#pragma once
#include <vector>
#include <string>
#include <sstream>
class Lexer{
    public:
        Lexer();
        std::string tokenize(const std::string& command);
        std::vector<std::string> parse_argument(const std::string& command);
};