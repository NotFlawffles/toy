#pragma once

#include "../../utils/span.hpp"
#include "token.hpp"
#include "../../diagnostic/diagnostic.hpp"
#include <variant>

using TokenResult = std::variant<Token, Diagnostic>;

class Lexer {
    public:
    std::string content;
    Span span;
    char current;

    Lexer(std::string, std::string);
    Lexer(void);

    TokenResult next(void);
    TokenResult lex_number(void);
    TokenResult lex_char(void);
    TokenResult lex_string(void);
    TokenResult lex_identifier(void);
    TokenResult lex_plus(void);
    TokenResult lex_minus(void);
    TokenResult lex_asterisk(void);
    TokenResult lex_slash(void);
    TokenResult lex_modulo(void);
    TokenResult lex_ampersand(void);
    TokenResult lex_pipe(void);
    TokenResult lex_caret(void);
    TokenResult lex_greater(void);
    TokenResult lex_less(void);
    TokenResult lex_assign(void);
    TokenResult lex_exclamation(void);
    TokenResult advance_with_token(TokenResult);
    void skip_whitespace(void);
    void advance(void);
};
