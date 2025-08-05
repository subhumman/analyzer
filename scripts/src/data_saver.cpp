#include "data_saver.hpp"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

DataSaver::DataSaver() {
    operations = nlohmann::json::array();
}

void DataSaver::save_operation(const std::string& operation, const std::string& filename, const std::string& status) {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    std::tm timeinfo;
#ifdef _WIN32
    localtime_s(&timeinfo, &time_t);
#else
    localtime_r(&time_t, &timeinfo);
#endif
    ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
    
    nlohmann::json op = {
        {"timestamp", ss.str()},
        {"operation", operation},
        {"filename", filename},
        {"status", status}
    };
    
    operations.push_back(op);
}

void DataSaver::save_to_file(const std::string& filename) {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open file for writing: " + filename);
        }
        file << operations.dump(2);
        std::cout << "> Operations saved to " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "> Error saving operations: " << e.what() << std::endl;
    }
}

void DataSaver::load_from_file(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "> No previous operations file found, starting fresh" << std::endl;
            return;
        }
        file >> operations;
        std::cout << "> Loaded " << operations.size() << " operations from " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "> Error loading operations: " << e.what() << std::endl;
        operations = nlohmann::json::array();
    }
}

void DataSaver::show_history() const {
    if (operations.empty()) {
        std::cout << "> No operations history" << std::endl;
        return;
    }
    
    std::cout << "> Operations History:" << std::endl;
    for (const auto& op : operations) {
        std::cout << "  [" << op["timestamp"].get<std::string>() << "] " 
                  << op["operation"].get<std::string>() << " - " 
                  << op["filename"].get<std::string>() << " (" 
                  << op["status"].get<std::string>() << ")" << std::endl;
    }
}