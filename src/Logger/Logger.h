#pragma once
#include <iostream>
#include <type_traits>

#define ASSERT(x, y) if(!(x)) std::cout << "Assert failed at file: " << __FILE__ << " on line: " << __LINE__ << " calling function: " << #x << " message: " << y << std::endl

class Logger
{
public:
    template<typename... Targs>
    static void Log(Targs&&... args){
        std::cout << "[LOGGER]: ";
        ((std::cout<< "\033[31m" <<  std::forward<Targs>(args) << "\033[0m" << " "), ...) << std::endl;
    }
};