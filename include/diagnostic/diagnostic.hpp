#pragma once

#include "../utils/span.hpp"

enum class DiagnosticKind {
    FileNotFound,
    FileNotRegular,
    SyntaxError,
    UnhandledCharacter
};

class Diagnostic {
    public:
    DiagnosticKind kind;
    Span span;
    std::string message;

    Diagnostic(DiagnosticKind, Span, std::string);
    void show(void);
};
