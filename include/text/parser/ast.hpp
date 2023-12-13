#pragma once

#include <variant>
#include <vector>
#include "../../utils/span.hpp"
#include "expression/expression.hpp"
#include "name.hpp"

enum class AstKind {
    Block,
    Expression,
    VariableDeclaration
};

class Ast {
    using AstValue = std::variant<std::vector<Ast>, Expression, Name>;

    public:
    AstKind kind;
    AstValue value;
    Span span;

    Ast(std::vector<Ast>, Span);
    Ast(Expression, Span);
    Ast(Name, Span);
    Ast(void);
};
