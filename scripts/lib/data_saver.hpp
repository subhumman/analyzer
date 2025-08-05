#pragma once
#include <string>
#include <nlohmann/json.hpp>

class DataSaver {
public:
    DataSaver();
    void save_operation(const std::string& operation, const std::string& filename, const std::string& status = "success");
    void save_to_file(const std::string& filename = "operations.json");
    void load_from_file(const std::string& filename = "operations.json");
    void show_history() const;
    
private:
    nlohmann::json operations;
};