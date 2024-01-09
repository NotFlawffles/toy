#include "../../../include/text/lexer/lexer.hpp"
#include <cctype>

Lexer::Lexer(std::string path, std::string content) {
    this->content = content;
    this->span = Span(path, 1, 1, 0, this->content.length());
    this->current = this->content[this->span.index];
}

Lexer::Lexer(void) {}

TokenResult Lexer::next(void) {
    skip_whitespace();

    switch (current) {
	case '\0':
	    return Token();

	case '.':
	    return lex_number();

	case '\'':
	    return lex_char();

	case '"':
	    return lex_string();

	case '_':
	    return lex_identifier();

	case '+':
	    return lex_plus();

	case '-':
	    return lex_minus();

	case '*':
	    return lex_asterisk();

	case '/':
	    return lex_slash();

	case '%':
	    return lex_modulo();

	case '&':
	    return lex_ampersand();

	case '|':
	    return lex_pipe();

	case '^':
	    return lex_caret();

	case '>':
	    return lex_greater();

	case '<':
	    return lex_less();

	case '=':
	    return lex_assign();

	case '!':
	    return lex_exclamation();

	case '~':
	    return advance_with_token(
		Token(
		    TokenKind::Tilde,
		    span,
		    "~"
		)
	    );

	case '(':
	    return advance_with_token(
		Token(
		    TokenKind::LeftParenthesis,
		    span,
		    "("
		)
	    );

	case ')':
	    return advance_with_token(
		Token(
		    TokenKind::RightParenthesis,
		    span,
		    ")"
		)
	    );
	    
	case '{':
	    return advance_with_token(
		Token(
		    TokenKind::LeftCurlyBrace,
		    span,
		    "{"
		)
	    );

	case '}':
	    return advance_with_token(
		Token(
		    TokenKind::RightCurlyBrace,
		    span,
		    "}"
		)
	    );

	case ',':
	    return advance_with_token(Token(
		TokenKind::Comma,
		span,
		","
	    ));

	case ':':
	    return advance_with_token(
		Token(
		    TokenKind::Colon,
		    span,
		    ":"
		)
	    );
	    
	case ';':
	    return advance_with_token(
		Token(
		    TokenKind::SemiColon,
		    span,
		    ";"
		)
	    );
	
	default:
	    if (std::isdigit(current)) {
		return lex_number();
	    } else if (std::isalpha(current)) {
		return lex_identifier();
	    } else {
		return Diagnostic(
		    DiagnosticKind::UnhandledCharacter,
		    span,
		    std::string({current})
		);
	    }
    }
}

TokenResult Lexer::lex_number(void) {
    Span span = this->span;
    std::string value;
    bool isfloat = false;

    while (std::isdigit(current) || current == '.') {
	if (current == '.') {
	    if (isfloat) {
		return Diagnostic(
		    DiagnosticKind::SyntaxError,
		    span,
		    "unexpcted '.'"
		);

		isfloat = true;
	    }
	}

	value.push_back(current);
	advance();
    }

    if (value.at(value.length() - 1) == '.' || (value.length() == 1 && value.at(0) == '.')) {
	return Diagnostic(
	    DiagnosticKind::SyntaxError,
	    span,
	    "unexpcted '.'"
	);
    }

    span.length = value.length();

    return Token(
	isfloat ? TokenKind::Float : TokenKind::Integer,
	span,
	value
    );
}

TokenResult Lexer::lex_char(void) {
    Span span = this->span;
    span.length = 3;
    advance();
    char value = current;
    advance();

    if (!current) {
	return Diagnostic(
	    DiagnosticKind::SyntaxError,
	    this->span,
	    "unterminated char sequence"
	);
    } else if (current != '\'') {
	return Diagnostic(
	    DiagnosticKind::SyntaxError,
	    this->span,
	    "unterminated char sequence"
	);
    }

    advance();

    return Token(
	TokenKind::Char,
	span,
	std::string({value})
    );
}

TokenResult Lexer::lex_string(void) {
    Span span = this->span;
    std::string value;
    advance();

    while (current != '"') {
	if (!current) {
	    return Diagnostic(
		DiagnosticKind::SyntaxError,
		this->span,
		"unterminated string sequence"
	    );
	}

	value.push_back(current);
	advance();
    }

    advance();
    span.length = value.length();

    return Token(
	TokenKind::String,
	span,
	value
    );
}

TokenResult Lexer::lex_identifier(void) {
    Span span = this->span;
    std::string value;

    while (std::isalnum(current) || current == '_') {
	value.push_back(current);
	advance();
    }

    span.length = value.length();

    if (value == "true" || value == "false") {
	return Token(
	    TokenKind::Boolean,
	    span,
	    value
	);
    } else {
	return Token(
	    TokenKind::Identifier,
	    span,
	    value
	);
    }
}

TokenResult Lexer::lex_plus(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::PlusAssign,
		    span,
		    "+="
		)
	    );

	default:
	    return Token(
		TokenKind::Plus,
		span,
		"+"
	    );
    }
}

TokenResult Lexer::lex_minus(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::MinusAssign,
		    span,
		    "-="
		)
	    );

	case '>':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::MinusGreater,
		    span,
		    "->"
		)
	    );

	default:
	    return Token(
		TokenKind::Minus,
		span,
		"-"
	    );
    }
}

TokenResult Lexer::lex_asterisk(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::AsteriskAssign,
		    span,
		    "*="
		)
	    );

	default:
	    return Token(
		TokenKind::Asterisk,
		span,
		"*"
	    );
    }
}

TokenResult Lexer::lex_slash(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::SlashAssign,
		    span,
		    "/="
		)
	    );

	case '/':
	    while (current != '\n' || !current) {
		advance();
	    }

	    return next();

	case '*':
	    while (true) {
		advance();

		if (!current) {
		    return Diagnostic(
			DiagnosticKind::SyntaxError,
			this->span,
			"unterminated multi-line comment"
		    );
		}

		if (current == '*') {
		    advance();

		    if (current == '/') {
			advance();
			break;
		    }
		}
	    }

	    return next();

	default:
	    return Token(
		TokenKind::Slash,
		span,
		"/"
	    );
    }
}

TokenResult Lexer::lex_modulo(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::ModuloAssign,
		    span,
		    "%="
		)
	    );

	default:
	    return Token(
		TokenKind::Modulo,
		span,
		"%"
	    );
    }
}

TokenResult Lexer::lex_ampersand(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::AmpersandAssign,
		    span,
		    "&="
		)
	    );

	case '&':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::AmpersandAmpersand,
		    span,
		    "&&"
		)
	    );

	default:
	    return Token(
		TokenKind::Ampersand,
		span,
		"&"
	    );
    }
}

TokenResult Lexer::lex_pipe(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::PipeAssign,
		    span,
		    "|="
		)
	    );

	case '|':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::PipePipe,
		    span,
		    "||"
		)
	    );

	default:
	    return Token(
		TokenKind::Pipe,
		span,
		"|"
	    );
    }
}

TokenResult Lexer::lex_caret(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::CaretAssign,
		    span,
		    "^="
		)
	    );

	default:
	    return Token(
		TokenKind::Caret,
		span,
		"^"
	    );
    }
}

TokenResult Lexer::lex_greater(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::GreaterAssign,
		    span,
		    ">="
		)
	    );

	case '>':
	    span.length++;
	    advance();

	    switch (current) {
		case '=':
		    span.length++;

		    return advance_with_token(
			Token(
			    TokenKind::GreaterGreaterAssign,
			    span,
			    ">>="
			)
		    );

		default:
		    return Token(
			TokenKind::GreaterGreater,
			span,
			">>"
		    );
	    }

	default:
	    return Token(
		TokenKind::Greater,
		span,
		">"
	    );
    }
}

TokenResult Lexer::lex_less(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::LessAssign,
		    span,
		    "<="
		)
	    );

	case '<':
	    span.length++;
	    advance();

	    switch (current) {
		case '=':
		    span.length++;

		    return advance_with_token(
			Token(
			    TokenKind::LessLessAssign,
			    span,
			    "<<="
			)
		    );

		default:
		    return Token(
			TokenKind::LessLess,
			span,
			"<<"
		    );
	    }

	default:
	    return Token(
		TokenKind::Less,
		span,
		"<"
	    );
    }
}

TokenResult Lexer::lex_assign(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::AssignAssign,
		    span,
		    "=="
		)
	    );

	default:
	    return Token(
		TokenKind::Assign,
		span,
		"="
	    );
    }
}

TokenResult Lexer::lex_exclamation(void) {
    Span span = this->span;
    advance();

    switch (current) {
	case '=':
	    span.length++;

	    return advance_with_token(
		Token(
		    TokenKind::ExclamationAssign,
		    span,
		    "!="
		)
	    );

	default:
	    return Token(
		TokenKind::Exclamation,
		span,
		"!"
	    );
    }   
}

TokenResult Lexer::advance_with_token(TokenResult token) {
    advance();
    return token;
}

void Lexer::skip_whitespace(void) {
    while (std::isspace(current)) {
	if (current == '\n') {
	    span.row++;
	    span.column = 0;
	}

	advance();
    }
}

void Lexer::advance(void) {
    span.column++;
    current = content[++span.index];
}
