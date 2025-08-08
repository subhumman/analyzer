#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include "lib/lexer.hpp"

// тесты для лексера
void test_lexer_tokenize() {
    std::cout << "Testing Lexer::tokenize..." << std::endl;
    
    Lexer lexer;
    
    // простая команда
    std::string result1 = lexer.tokenize("CREATE file.txt");
    assert(result1 == "CREATE");
    
    // команда с одним словом
    std::string result2 = lexer.tokenize("HISTORY");
    assert(result2 == "HISTORY");
    
    // пустая строка
    std::string result3 = lexer.tokenize("");
    assert(result3 == "");
    
    // строка только с пробелами
    std::string result4 = lexer.tokenize("   ");
    assert(result4 == "");
    
    // команда с множественными пробелами
    std::string result5 = lexer.tokenize("  CREATE  file.txt  ");
    assert(result5 == "CREATE");
    
    std::cout << "✓ Lexer::tokenize tests passed" << std::endl;
}

void test_lexer_parse_argument() {
    std::cout << "Testing Lexer::parse_argument..." << std::endl;
    
    Lexer lexer;
    
    // команда с аргументами
    std::vector<std::string> result1 = lexer.parse_argument("CREATE file.txt content");
    assert(result1.size() == 3);
    assert(result1[0] == "CREATE");
    assert(result1[1] == "file.txt");
    assert(result1[2] == "content");
    
    // команда без аргументов
    std::vector<std::string> result2 = lexer.parse_argument("HISTORY");
    assert(result2.size() == 1);
    assert(result2[0] == "HISTORY");
    
    // пустая строка
    std::vector<std::string> result3 = lexer.parse_argument("");
    assert(result3.empty());
    
    // строка с множественными пробелами
    std::vector<std::string> result4 = lexer.parse_argument("  CREATE   file.txt  ");
    assert(result4.size() == 2);
    assert(result4[0] == "CREATE");
    assert(result4[1] == "file.txt");
    
    // команда с кавычками
    std::vector<std::string> result5 = lexer.parse_argument("CREATE \"file name.txt\" content");
    assert(result5.size() == 3);
    assert(result5[0] == "CREATE");
    assert(result5[1] == "\"file");
    assert(result5[2] == "name.txt\"");
    
    std::cout << "✓ Lexer::parse_argument tests passed" << std::endl;
}

void test_lexer_integration() {
    std::cout << "Testing Lexer integration..." << std::endl;
    
    Lexer lexer;
    std::string command = "CREATE test.txt \"Hello World\"";
    std::string token = lexer.tokenize(command);
    std::vector<std::string> args = lexer.parse_argument(command);
    
    assert(token == "CREATE");
    assert(args.size() == 3);
    assert(args[0] == "CREATE");
    assert(args[1] == "test.txt");
    assert(args[2] == "\"Hello");
    
    std::cout << "✓ Lexer integration test passed" << std::endl;
}

void test_lexer_commands() {
    std::cout << "Testing Lexer with different commands..." << std::endl;
    
    Lexer lexer;
    
    std::string create_cmd = "CREATE filename.txt content";
    std::string token1 = lexer.tokenize(create_cmd);
    assert(token1 == "CREATE");
    
    std::string delete_cmd = "REMOVE filename.txt";
    std::string token2 = lexer.tokenize(delete_cmd);
    assert(token2 == "REMOVE");
    
    std::string rename_cmd = "RENAME old.txt new.txt";
    std::string token3 = lexer.tokenize(rename_cmd);
    assert(token3 == "RENAME");
    
    std::string history_cmd = "HISTORY";
    std::string token4 = lexer.tokenize(history_cmd);
    assert(token4 == "HISTORY");

    std::string anal_cmd = "ANAL";
    std::string token5 = lexer.tokenize(anal_cmd);
    assert(token5 == "ANAL");
    
    std::cout << "✓ Lexer commands tests passed" << std::endl;
}

void run_all_tests() {
    std::cout << "Starting tests..." << std::endl;
    std::cout << "==================" << std::endl;
    
    try {
        // тесты лексера
        test_lexer_tokenize();
        test_lexer_parse_argument();
        test_lexer_commands();
        
        test_lexer_integration();
        
        std::cout << "==================" << std::endl;
        std::cout << "All tests passed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        std::exit(1);
    } catch (...) {
        std::cerr << "Test failed with unknown exception" << std::endl;
        std::exit(1);
    }
}
int main() {
    run_all_tests();
    return 0;
}