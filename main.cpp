#include "scripts/lib/executor.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <iostream>

int main() {
    Exec executor;
    executor.init();
    
    std::cout << "> File Analyzer v0.1\n";
    std::cout << "> You could stay in your memory importent detail - all your files was saved in build/debug/ directory\n";
    std::cout << "> Available commands:\n";
    std::cout << ">   CREATE <filename> - Create a new file\n";
    std::cout << ">   RENAME <old_name> <new_name> - Rename file\n";
    std::cout << ">   CHTP <filename> <new_extension> - Change file type\n";
    std::cout << ">   REMOVE <filename> - Remove file\n";
    std::cout << ">   HISTORY - Show operations history\n";
    std::cout << ">   WRITE - write the text .txt to the tail your file\n";
    std::cout << ">   ANAL - analyze own .txt file to character count\n";
    std::cout << ">   EXIT - Exit program\n";
    std::cout << ">\n";
    
    std::string command;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, command);
        
        if (command == "EXIT" || command == "exit") {
            std::cout << "> Goodbye!\n";
            break;
        }
        
        if (!command.empty()) {
            executor.exec_com(command);
        }
    }
    
    return 0;
}