#pragma once
#include "data_saver.hpp"
#include "lexer.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <filesystem>
#include <fstream>

class Exec{    
    Lexer lexer;
    DataSaver saver;
    public:
        Exec() = default;
        ~Exec() = default;
        void exec_com(const std::string& command);
        void create(const std::string& command);
        void chtp(const std::string& command);
        void rename(const std::string& command);
        void remove(const std::string& command);
        void history(const std::string& command);
        void write(const std::string& command);
        void anal(const std::string& command);
        void init();
        
};
