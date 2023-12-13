#include "../../text/lexer/lexer.hpp"
#include "ast.hpp"

using AstResult = std::variant<Ast, Diagnostic>;
using ExpressionResult = std::variant<Expression, Diagnostic>;

const std::vector<std::string> KEYWORDS = {
    "let",
    "func"
};

bool is_keyword(std::string);

class Parser {
    public:
    Lexer lexer;
    TokenResult current;
    TokenResult previous;
    std::vector<Diagnostic> diagnostics;
    bool requires_semi_colon = true;

    Parser(Lexer);
    AstResult parse(void);
    AstResult parse_next(void);
    AstResult parse_name(void);
    AstResult parse_statement(void);
    AstResult parse_variable_declaration(void);
    AstResult parse_function_declaration(void);
    AstResult parse_block(void);
    AstResult parse_expression(void);
    ExpressionResult parse_assignment(void);
    ExpressionResult parse_logical_or(void);
    ExpressionResult parse_logical_and(void);
    ExpressionResult parse_bitwise_or(void);
    ExpressionResult parse_bitwise_xor(void);
    ExpressionResult parse_bitwise_and(void);
    ExpressionResult parse_equality(void);
    ExpressionResult parse_relational(void);
    ExpressionResult parse_shift(void);
    ExpressionResult parse_additive(void);
    ExpressionResult parse_multiplicative(void);
    ExpressionResult parse_unary(void);
    ExpressionResult parse_literal(void);
    TokenResult eat(std::vector<TokenKind>);
};
