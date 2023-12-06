#pragma once

#include "../../utils/span.hpp"

enum class TokenKind {
    Integer,
    Float,
    Char,
    String,
    Identifier,
    Boolean,

    Plus,
    Minus,
    Asterisk,
    Slash,
    Modulo,
    Ampersand,
    Pipe,
    Caret,
    Tilde,
    Greater,
    Less,
    Assign,
    Exclamation,
    AmpersandAmpersand,
    PipePipe,
    GreaterGreater,
    LessLess,
    AssignAssign,
    ExclamationAssign,
    PlusAssign,
    MinusAssign,
    AsteriskAssign,
    SlashAssign,
    ModuloAssign,
    AmpersandAssign,
    PipeAssign,
    CaretAssign,
    GreaterAssign,
    LessAssign,
    GreaterGreaterAssign,
    LessLessAssign,

    LeftParenthesis,
    RightParenthesis,
    LeftCurlyBrace,
    RightCurlyBrace,

    Comma,
    Colon,
    SemiColon,
    MinusGreater,

    EndOfFile
};

class Token {
    public:
    TokenKind kind;
    Span span;
    std::string value;

    Token(TokenKind, Span, std::string);
    Token(void);

    std::string kind_as_string(void);
};
