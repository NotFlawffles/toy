#include "../../../include/text/lexer/token.hpp"

Token::Token(TokenKind kind, Span span, std::string value) {
    this->kind = kind;
    this->span = span;
    this->value = value;
}

Token::Token(void) {
    this->kind = TokenKind::EndOfFile;
}

std::string Token::kind_as_string(void) {
    switch (kind) {
        case TokenKind::Integer:
	    return "Integer";

        case TokenKind::Float:
	    return "Float";

        case TokenKind::Char:
	    return "Char";

        case TokenKind::String:
	    return "String";

        case TokenKind::Identifier:
	    return "Identifier";

        case TokenKind::Boolean:
	    return "Boolean";

        case TokenKind::Plus:
	    return "+";

        case TokenKind::Minus:
	    return "-";

        case TokenKind::Asterisk:
	    return "*";

        case TokenKind::Slash:
	    return "/";

        case TokenKind::Modulo:
	    return "%";

        case TokenKind::Ampersand:
	    return "&";

        case TokenKind::Pipe:
	    return "|";

        case TokenKind::Caret:
	    return "^";

        case TokenKind::Tilde:
	    return "~";

        case TokenKind::Greater:
	    return ">";

        case TokenKind::Less:
	    return "<";

        case TokenKind::Assign:
	    return "=";

        case TokenKind::Exclamation:
	    return "!";

        case TokenKind::AmpersandAmpersand:
	    return "&&";

        case TokenKind::PipePipe:
	    return "||";

        case TokenKind::GreaterGreater:
	    return ">>";

        case TokenKind::LessLess:
	    return "<<";

        case TokenKind::AssignAssign:
	    return "==";

        case TokenKind::ExclamationAssign:
	    return "!=";

        case TokenKind::PlusAssign:
	    return "+=";

        case TokenKind::MinusAssign:
	    return "-=";

        case TokenKind::AsteriskAssign:
	    return "*=";

        case TokenKind::SlashAssign:
	    return "/=";

        case TokenKind::ModuloAssign:
	    return "%=";

        case TokenKind::AmpersandAssign:
	    return "&=";

        case TokenKind::PipeAssign:
	    return "|=";

        case TokenKind::CaretAssign:
	    return "^=";

        case TokenKind::GreaterAssign:
	    return ">=";

        case TokenKind::LessAssign:
	    return "<=";

        case TokenKind::GreaterGreaterAssign:
	    return ">>=";

        case TokenKind::LessLessAssign:
	    return "<<=";

        case TokenKind::LeftParenthesis:
	    return "(";

        case TokenKind::RightParenthesis:
	    return ")";

        case TokenKind::LeftCurlyBrace:
	    return "{";

        case TokenKind::RightCurlyBrace:
	    return "}";

        case TokenKind::Comma:
	    return ",";

        case TokenKind::Colon:
	    return ":";

        case TokenKind::SemiColon:
	    return ";";

        case TokenKind::MinusGreater:
	    return "->";

        case TokenKind::EndOfFile:
	    return "EndOfFile";
	
	default:
	    return "Unknown";
    }
}
