#include "../../../../include/text/parser/expression/literal.hpp"

Literal::Literal(LiteralKind kind, LiteralValue value) {
    this->kind = kind;
    this->value = value;
}

Literal::Literal(void) {}
