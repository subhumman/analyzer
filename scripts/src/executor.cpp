#include "executor.hpp"
#include <iostream>

namespace fs = std::filesystem;

void Exec::init() {
    saver.load_from_file();
}

void Exec::exec_com(const std::string& command) {
    try {
        std::string token = lexer.tokenize(command);
        
        static const std::unordered_map<std::string, std::function<void(const std::string&)>> commands = {
            {"CREATE", [this](const std::string& cmd) { this->create(cmd); }},
            {"RENAME", [this](const std::string& cmd) { this->rename(cmd); }},
            {"CHTP", [this](const std::string& cmd) { this->chtp(cmd); }},
            {"REMOVE", [this](const std::string& cmd) { this->remove(cmd); }},
            {"HISTORY", [this](const std::string& cmd) { this->history(cmd); }},
            {"WRITE", [this](const std::string& cmd) {this->write(cmd);}},
            {"ANAL", [this](const std::string& cmd) {this->anal(cmd);}}
        };
        
        auto it = commands.find(token);
        if (it != commands.end()) {
            it->second(command);
        } else {
            std::cerr << "> Error: Unknown command '" << token << "'" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "> Error executing command: " << e.what() << std::endl;
    }
}

void Exec::anal(const std::string& command){
    auto args = lexer.parse_argument(command);
    if (args.size() < 2) {
        throw std::runtime_error("> Error command syntax");
    }
    try {
        if (!std::filesystem::exists(args[1])) {
            throw std::runtime_error("> File does not exist");
        }

        // открытие файла в бинарнике для лучшего контроля памяти
        std::ifstream file(args[1], std::ios::binary);
        if (!file) {
            throw std::runtime_error("> Error opening file");
        }

        constexpr size_t BUFFER_SIZE = 4096; // 4 KB
        char buffer[BUFFER_SIZE];
        int symbol_count = 0; // счётчик символов 
        int pending_bytes = 0; // ожидаемые байты для текущего символа utf-8

        while (file.read(buffer, BUFFER_SIZE)) {
            for (size_t i = 0; i < file.gcount(); ++i) {
                unsigned char byte = buffer[i];
                
                if (pending_bytes > 0) {
                    // проверка, что это продолжение символа (биты 10xxxxxx)
                    if ((byte & 0xC0) == 0x80) {
                        pending_bytes--;
                    } else {
                        // некорректный utf-8
                        pending_bytes = 0;
                    }
                } else {
                    // определение длинны символа utf-8
                    if (byte < 0x80) { // 1-байтовый символ (ascii)
                        symbol_count++;
                    } else if ((byte & 0xE0) == 0xC0) { // 2-байтовый
                        pending_bytes = 1;
                        symbol_count++;
                    } else if ((byte & 0xF0) == 0xE0) { // 3-байтовый
                        pending_bytes = 2;
                        symbol_count++;
                    } else if ((byte & 0xF8) == 0xF0) { // 4-байтовый
                        pending_bytes = 3;
                        symbol_count++;
                    }
                }
            }
        }

        // учет остатка данных после последнего read
        for (size_t i = 0; i < file.gcount(); ++i) {
            unsigned char byte = buffer[i];
            if (pending_bytes > 0) {
                    if ((byte & 0xC0) == 0x80) {
                        pending_bytes--;
                    } else {
                        // некорректный utf-8
                        pending_bytes = 0;
                    }
                } else {
                    // определение длинны символа utf-8
                    if (byte < 0x80) { // 1-байтовый символ (ascii)
                        symbol_count++;
                    } else if ((byte & 0xE0) == 0xC0) { // 2-байтовый
                        pending_bytes = 1;
                        symbol_count++;
                    } else if ((byte & 0xF0) == 0xE0) { // 3-байтовый
                        pending_bytes = 2;
                        symbol_count++;
                    } else if ((byte & 0xF8) == 0xF0) { // 4-байтовый
                        pending_bytes = 3;
                        symbol_count++;
                    }
                }
        }

        std::cout << "> Symbols in file: " << symbol_count << "\n";

    } catch (const std::exception& e) {
        throw std::runtime_error("> Error reading file: " + std::string(e.what()));
    }
}


// in this fn i used the ios::app to write a text to file tail. If you want rewrite text you can used the ios::out;
void Exec::write(const std::string& command){
    auto args = lexer.parse_argument(command);
    if(args.size() < 3) throw std::runtime_error("> Error on command type");
    std::string& filename = args[1];
    try{
        //this we concate the "mone word more text" to one arg(check the lexer class)
        std::string text;
        for(size_t i = 2; i < args.size(); i++){
            if(i > 2)   text += " ";
            text += args[i];
        }

        std::ofstream outfile(filename, std::ios::app);
        if(!outfile) throw std::runtime_error("> Could not open file: " + filename);
        
        outfile << text << std::endl;
        if(outfile.fail()) throw std::runtime_error("> Write operation failed");
        
        std::cout << "> Text written to " << filename << std::endl;
    
    }catch(fs::filesystem_error& e){
        throw std::runtime_error("> Error on " + std::string(e.what()));
    }
    return;
}

void Exec::create(const std::string& command){
    auto args = lexer.parse_argument(command);
    if (args.size() < 2) {
        throw std::runtime_error("> Fatal Error! CREATE file.format");
    }
    
    const std::string filename = args[1];
    FILE* file = nullptr; 
    
    try {
        if(fopen_s(&file, filename.c_str(), "w") != 0 || !file) {
            throw std::runtime_error("> Failed create file " + filename);
        }
        fclose(file);
        std::cout << "> File created successful" << std::endl;
        
        // Сохраняем операцию
        saver.save_operation("CREATE", filename);
        saver.save_to_file();
        
    } catch (const std::exception& e) {
        std::cerr << "> Error Create file: " << e.what() << std::endl;
        saver.save_operation("CREATE", filename, "failed");
        saver.save_to_file();
    }
}

void Exec::chtp(const std::string& command){
    auto args = lexer.parse_argument(command);
    if(args.size() < 3) {
        throw std::runtime_error("> Error on command " + command);
    }

    const std::string fst = args[1];
    const std::string sec = args[2];
    if(sec.empty() || sec[0] == '.') {
        throw std::runtime_error("> Error on command " + command);
    }

    size_t dot_pos = fst.find_last_of('.');
    if(dot_pos == std::string::npos || dot_pos == 0) {
        throw std::runtime_error("> Error on parse file type in " + fst);
    }
    
    std::string new_filename = fst.substr(0, dot_pos + 1) + sec;
    
    try {
        fs::rename(fst, new_filename);
        std::cout << "> File successful type changed" << std::endl;
        
        // Сохраняем операцию
        saver.save_operation("CHTP", fst + " -> " + new_filename);
        saver.save_to_file();
        
    } catch (const std::exception& e) {
        std::cerr << "> Error on last stages change type: " << e.what() << std::endl;
        saver.save_operation("CHTP", fst + " -> " + new_filename, "failed");
        saver.save_to_file();
    }
}

void Exec::rename(const std::string& command){
    auto args = lexer.parse_argument(command);
    if(args.size() < 3) {
        throw std::runtime_error("> Command size should be 3 keywords");
    }
    
    const std::string old_name = args[1];
    const std::string new_name = args[2];
    
    try {
        fs::rename(old_name, new_name);
        std::cout << "> Renamed was successful!" << std::endl;
        
        // Сохраняем операцию
        saver.save_operation("RENAME", old_name + " -> " + new_name);
        saver.save_to_file();
        
    } catch(const fs::filesystem_error& e) {
        throw std::runtime_error("> Rename failed - '" + std::string(e.what()) + "'");
    }
}

void Exec::remove(const std::string& command){
    auto args = lexer.parse_argument(command);
    if (args.size() < 2) {
        throw std::runtime_error("> Command incorrect");
    }
    
    const std::string& filename = args[1];
    
    try {
        if(fs::remove(filename)) {
            std::cout << "> '" << filename << "' remove successful!" << std::endl;
            
            // Сохраняем операцию
            saver.save_operation("REMOVE", filename);
            saver.save_to_file();
            
        } else {
            std::cout << "> '" << filename << "' does not exist" << std::endl;
            saver.save_operation("REMOVE", filename, "file_not_found");
            saver.save_to_file();
        }
    } catch(const fs::filesystem_error& e) {
        throw std::runtime_error("> Error on file remove: " + std::string(e.what()));
    }
}

void Exec::history(const std::string& command) {
    (void)command; // Suppress unused parameter warning
    saver.show_history();
}