#include "../../../include/text/parser/parser.hpp"
#include <algorithm>

using enum TokenKind;

bool is_keyword(std::string identifier) {
    for (auto keyword: KEYWORDS) {
	if (identifier == keyword) {
	    return true;
	}
    }

    return false;
}

Parser::Parser(Lexer lexer) {
    this->lexer = lexer;
}

AstResult Parser::parse(void) {
    std::vector<Ast> tree;

    while (true) {
	current = this->lexer.next();

	if (std::get<Token>(current).kind == TokenKind::EndOfFile) {
	    break;
	}

	auto next = parse_next();

	if (std::get_if<Ast>(&next)) {
	    tree.push_back(std::get<Ast>(next));
	}
    }

    return Ast(
	tree,
	Span(
	    lexer.span.stream,
	    1,
	    1,
	    0,
	    lexer.span.length
	)
    );
}

AstResult Parser::parse_next(void) {
    AstResult result = Ast();

    switch (std::get<Token>(current).kind) {
	case TokenKind::Integer:
	case TokenKind::Float:
	case TokenKind::Char:
	case TokenKind::String:
	case TokenKind::Boolean:
	case TokenKind::Plus:
	case TokenKind::Minus:
	case TokenKind::LeftParenthesis:
	    result = parse_expression();
	    break;

	case TokenKind::Identifier:
	    result = parse_name();
	    break;

	default:
	    break;
    }

   auto advance = eat({SemiColon});

    if (std::get_if<Diagnostic>(&advance)) {
	diagnostics.push_back(std::get<Diagnostic>(advance));
    }

    return result;
}

AstResult Parser::parse_name(void) {
    if (is_keyword(std::get<Token>(current).value)) {
	return parse_statement();
    }

    return parse_expression();
}

AstResult Parser::parse_statement(void) {
    if (std::get<Token>(current).value == "let") {
	return parse_declaration();
    }

    return Diagnostic(
	DiagnosticKind::SyntaxError,
	lexer.span,
	"unexpected statement"
    );
}

AstResult Parser::parse_declaration(void) {
    auto advance = eat({Identifier});

    if (std::get_if<Diagnostic>(&advance)) {
	return std::get<Diagnostic>(advance);
    }
    
    return Diagnostic(
	DiagnosticKind::SyntaxError,
	lexer.span,
	"yet not implemented"
    );
}

AstResult Parser::parse_block(void) {
    Span span = lexer.span;
    std::vector<Ast> block;
    auto advance = eat({LeftCurlyBrace});

    if (std::get_if<Diagnostic>(&advance)) {
	return std::get<Diagnostic>(advance);
    }
    
    while (std::get_if<Token>(&current)->kind != RightCurlyBrace) {
	AstResult next = parse_next();

	if (std::get_if<Diagnostic>(&next)) {
	    return std::get<Diagnostic>(next);
	}

	block.push_back(std::get<Ast>(next));
    }
    
    return Ast(
	block,
	span
    );
}

AstResult Parser::parse_expression(void) {
    auto expression = parse_assignment();

    if (std::get_if<Diagnostic>(&expression)) {
	return std::get<Diagnostic>(expression);
    } else {
	return Ast(
	    std::get<Expression>(expression),
	    lexer.span
	);
    }
}

ExpressionResult Parser::parse_assignment(void) {
    auto left = parse_logical_or();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	Assign,
	PlusAssign,
	MinusAssign,
	AsteriskAssign,
	SlashAssign,
	ModuloAssign,
	AmpersandAssign,
	PipeAssign,
	CaretAssign,
	GreaterGreaterAssign,
	LessLessAssign
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_logical_or(void) {
    auto left = parse_logical_and();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	PipePipe
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});
	
	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_logical_and(void) {
    auto left = parse_bitwise_or();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	AmpersandAmpersand
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_bitwise_or(void) {
    auto left = parse_bitwise_xor();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	Pipe
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_bitwise_xor(void) {
    auto left = parse_bitwise_and();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	Caret
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance= eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_bitwise_and(void) {
    auto left = parse_equality();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	Ampersand
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_equality(void) {
    auto left = parse_relational();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	Assign,
	ExclamationAssign
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_relational(void) {
    auto left = parse_shift();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	Greater,
	GreaterAssign,
	Less,
	LessAssign
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_shift(void) {
    auto left = parse_additive();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	GreaterGreater,
	LessLess
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_additive(void) {
    auto left = parse_multiplicative();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	Plus,
	Minus
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&right)) {
	    return std::get<Diagnostic>(right);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_multiplicative(void) {
    auto left = parse_unary();

    if (std::get_if<Diagnostic>(&left)) {
	return std::get<Diagnostic>(left);
    }

    std::vector<TokenKind> requirements = {
	Asterisk,
	Slash
    };

    if (std::find(requirements.begin(), requirements.end(), std::get<Token>(current).kind) != requirements.end()) {
	Token op = std::get<Token>(current);
	auto advance = eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	auto right = parse_assignment();

	if (std::get_if<Diagnostic>(&left)) {
	    return std::get<Diagnostic>(left);
	}

	left = Expression(
	    std::get<Expression>(left),
	    op,
	    std::get<Expression>(right)
	);
    }

    return left;
}

ExpressionResult Parser::parse_unary(void) {
    Token op = std::get<Token>(current);

    std::vector<TokenKind> requirements = {
	Plus,
	Minus
    };

    if (std::find(requirements.begin(), requirements.end(), op.kind) != requirements.end()) {
	auto advance = 	eat({op.kind});

	if (std::get_if<Diagnostic>(&advance)) {
	    return std::get<Diagnostic>(advance);
	}

	ExpressionResult literal = parse_literal();

	if (std::get_if<Diagnostic>(&literal)) {
	    return std::get<Diagnostic>(literal);
	}

	std::get<Expression>(literal).op = op;
	return literal;
    }

    return parse_literal();
}

ExpressionResult Parser::parse_literal(void) {
    TokenResult exception;

    switch (std::get<Token>(current).kind) {
	case Integer:
	    exception = eat({Integer});

	    if (std::get_if<Diagnostic>(&exception)) {
		return std::get<Diagnostic>(exception);
	    }

	    return Expression(
		Literal(
		    LiteralKind::Integer,
		    std::stoi(std::get<Token>(exception).value)
		)
	    );

	case Float:
	    exception = eat({Float});

	    if (std::get_if<Diagnostic>(&exception)) {
		return std::get<Diagnostic>(exception);
	    }

	    return Expression(
		Literal(
		    LiteralKind::Float,
		    std::stof(std::get<Token>(exception).value)
		)
	    );

	case Char:
	    exception = eat({Char});

	    if (std::get_if<Diagnostic>(&exception)) {
		return std::get<Diagnostic>(exception);
	    }

	    return Expression(
		Literal(
		    LiteralKind::Char,
		    std::get<Token>(exception).value.at(0)
		)
	    );

	case String:
	    exception = eat({String});

	    if (std::get_if<Diagnostic>(&exception)) {
		return std::get<Diagnostic>(exception);
	    }

	    return Expression(
		Literal(
		    LiteralKind::String,
		    std::get<Token>(exception).value
		)
	    );

	case Identifier:
	    exception = eat({Identifier});

	    if (std::get_if<Diagnostic>(&exception)) {
		return std::get<Diagnostic>(exception);
	    }

	    return Expression(
		Literal(
		    LiteralKind::Name,
		    std::get<Token>(exception).value
		)
	    );

	case Boolean:
	    exception = eat({Boolean});

	    if (std::get_if<Diagnostic>(&exception)) {
		return std::get<Diagnostic>(exception);
	    }

	    return Expression(
		Literal(
		    LiteralKind::String,
		    std::get<Token>(exception).value == "true" ? true : false 
		)
	    );

	case LeftParenthesis: {
	    exception = eat({LeftParenthesis});

	    if (std::get_if<Diagnostic>(&exception)) {
		return std::get<Diagnostic>(exception);
	    }

	    ExpressionResult expression = parse_assignment();
	    exception = eat({RightParenthesis});

	    if (std::get_if<Diagnostic>(&exception)) {
		return std::get<Diagnostic>(exception);
	    }

	    return expression;
	}

	default:
	    break;
    }

    return Diagnostic(
	DiagnosticKind::SyntaxError,
	lexer.span,
	"expected expression"
    );
}

TokenResult Parser::eat(std::vector<TokenKind> kinds) {
    for (auto kind: kinds) {
	if (std::get<Token>(current).kind == kind) {
	    auto previous = current;
	    current = lexer.next();
	    return previous;
	}
    }

    std::string message = "unexpected token: " + std::get<Token>(current).kind_as_string() + "\n\texpected one of these tokens: ";

    for (auto kind: kinds) {
	message += Token(kind, lexer.span, std::string()).kind_as_string();

	if (kind != kinds.at(kinds.size() - 1)) {
	    message += ", ";
	}
    }

    message.push_back('\n');

    return Diagnostic(
	DiagnosticKind::SyntaxError,
	lexer.span,
	message
    );
}
