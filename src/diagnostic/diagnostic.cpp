#include "../../include/diagnostic/diagnostic.hpp"
#include <iostream>

Diagnostic::Diagnostic(DiagnosticKind kind, Span span, std::string message) {
    this->kind = kind;
    this->span = span;
    this->message = message;
}

void Diagnostic::show(void) {
    std::cerr << span.stream << '[' << span.row << ':' << span.column << "]: " << message << std::endl;
}
