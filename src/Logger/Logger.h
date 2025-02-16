#pragma once
#include <iostream>

#define ASSERT(x, y) if(!(x)) std::cout << "Assert failed at file: " << __FILE__ << " on line: " << __LINE__ << " calling function: " << #x << " message: " << y << std::endl

class Logger
{
public:
    template<typename... Targs>
    static void Log(Targs&&... args){
        ((std::cout << std::forward<Targs>(args) << " "), ...) << std::endl;
    }
};