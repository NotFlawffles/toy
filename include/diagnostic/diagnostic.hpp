#pragma once

#include "../utils/span.hpp"

#define audhandle(which) if (std::get_if<Diagnostic>(&which)) { return std::get<Diagnostic>(which); }

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
