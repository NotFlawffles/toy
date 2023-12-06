#include "../../../../include/text/parser/expression/expression.hpp"

Expression::Expression(Expression left, Token op, Expression right) {
    kind = ExpressionKind::Binary;
    this->left = &left;
    this->op = op;
    this->right = &right;
}

Expression::Expression(Token op, Literal literal) {
    kind = ExpressionKind::Unary;
    this->op = op;
    this->literal = literal;
}

Expression::Expression(Literal literal) {
    this->kind = ExpressionKind::Literal;
    this->literal = literal;
}
