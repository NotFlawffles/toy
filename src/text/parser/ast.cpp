#include "../../../include/text/parser/ast.hpp"

Ast::Ast(std::vector<Ast> block, Span span) {
    kind = AstKind::Block;
    this->span = span;
    value = block;
}

Ast::Ast(Expression expression, Span span) {
    kind = AstKind::Expression;
    this->span = span;
    value = expression;
}

Ast::Ast(Name name, Span span) {
    this->kind = AstKind::VariableDeclaration;
    this->span = span;
    value = name;
}

Ast::Ast(void) {}
