#include "cli.hpp"
#include "executor.hpp"
#include <iostream>
#include <algorithm>
#include <future>
#include <atomic>

void CLI::run(){
    Exec executor;
    std::atomic<bool> running = true;
    auto input_f = std::async(std::launch::async, [&](){ // асинхронная обработка потока ввода
        std::string command; 
        while(running){
            std::cout << "> ";
            if(!std::getline(std::cin, command)){
                if(std::cin.eof()){// проверка на нажатие ctr+d(unix) и ctr+z (win)
                    std::cout << "> end of input detected exciting" << std::endl;
                } 
                else{
                    std::cerr << "> input err occurred" << std::endl;
                } 
                break;
            }
            if(command.empty())  continue; // проверка на ENTER при пустой строке
            // std::cin.get() == 1310 - избыточна
            executor.exec_com(command);
        }
    });
    input_f.wait(); 
}
