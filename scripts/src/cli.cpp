#include "cli.hpp"
#include "executor.hpp"
#include <iostream>
#include <algorithm>
#include <future>
#include <atomic>

void CLI::run(){
    Exec executor;
    std::atomic<bool> running = true;
    auto input_f = std::async(std::launch::async, [&](){ // асинхронная обработка потока ввода. Пускай пока что будет так, в будущем мб добавлю еще какие то обработки поверх этой
        std::string command; // команда с потока ввода. Динамичная по дефолту класса string
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
            // std::cin.get() == 1310 - такая проверка конечно имеет место быть, но она избыточна, так как empty проверяет на пустую строку
            executor.exec_com(command); // далее уже запускается работа executor-а
        }
    });

    /*Какое либо действие поверх
    while(running){fmt::print("go suc");}
    */

    input_f.wait(); // завершение
}