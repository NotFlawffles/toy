#pragma once

#include "../../lexer/token.hpp"
#include "literal.hpp"

enum class ExpressionKind {
    Binary,
    Unary,
    Literal
};

class Expression {
    public:
    ExpressionKind kind;
    Expression* left;
    Expression* right;
    Token op;
    Literal literal;

    Expression(Expression, Token, Expression);
    Expression(Token, Literal);
    Expression(Literal);
};
