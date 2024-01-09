#pragma once

#include <string>
#include <any>

class Call {
    public:
    std::string name;
    std::any arguments;

    Call(std::string, std::any);
};
