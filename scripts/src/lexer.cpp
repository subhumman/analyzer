#include "lexer.hpp"

Lexer::Lexer() = default;

std::vector<std::string> Lexer::parse_argument(const std::string& command){
    std::istringstream iss(command);
    std::vector<std::string> args;
    std::string arg;
    while(iss >> arg){
        args.push_back(arg);
    }
    return args;
}

std::string Lexer::tokenize(const std::string& command){
    std::istringstream iss(command);
    std::string token;
    iss >> token;
    return token;
}