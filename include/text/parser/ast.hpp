#pragma once

#include <variant>
#include <vector>
#include "../../utils/span.hpp"
#include "expression/expression.hpp"

enum class AstKind {
    Block,
    Expression
};

class Ast {
    using AstValue = std::variant<std::vector<Ast>, Expression>;

    public:
    AstKind kind;
    AstValue value;
    Span span;

    Ast(std::vector<Ast>, Span);
    Ast(Expression, Span);
    Ast(void);
};
