#pragma once

#include <variant>
#include <string>

using LiteralValue = std::variant<long long, double, char, std::string, bool>;

enum class LiteralKind {
    Integer,
    Float,
    Char,
    String,
    Name,
    Boolean
};

class Literal {
    public:
    LiteralKind kind;
    LiteralValue value;

    Literal(LiteralKind, LiteralValue);
    Literal(void);
};
