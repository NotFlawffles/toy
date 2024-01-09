#pragma once

#include <variant>
#include <string>
#include "call.hpp"

using LiteralValue = std::variant<long long, double, char, std::string, bool, Call>;

enum class LiteralKind {
    Integer,
    Float,
    Char,
    String,
    Name,
    Boolean,
    Call
};

class Literal {
    public:
    LiteralKind kind;
    LiteralValue value;

    Literal(LiteralKind, LiteralValue);
    Literal(void);
};
