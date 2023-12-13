#pragma once

#include "functionargument.hpp"
#include <any>
#include <string>
#include <vector>

enum class NameKind {
    Variable,
    Function
};

class Name {
    public:
    NameKind kind;
    std::string name;
    std::string type;
    std::vector<FunctionArgument> function_arguments;
    std::any value;

    Name(NameKind, std::string, std::string, std::any);
};
