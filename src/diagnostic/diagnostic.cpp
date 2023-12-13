#include "../../include/diagnostic/diagnostic.hpp"
#include "../../include/utils/utility.hpp"
#include <iostream>

Diagnostic::Diagnostic(DiagnosticKind kind, Span span, std::string message) {
    this->kind = kind;
    this->span = span;
    this->message = message;
}

void Diagnostic::show(void) {
    std::cerr << span.stream << '[' << span.row << ':' << span.column << "]: " << message << std::endl;

    if (span.stream != "cli") {
	std::string line = get_line(span.stream, span.row);
	
	if (line[0] == '\n') {
	    line.at(0) = ' ';
	}

	std::cerr << "\tin: " << line << std::endl
		  << '\t';

	for (size_t index = 0; index < span.column; index++) {
	    std::cout << ' ';
	}

	for (size_t index = 0; index < span.length; index++) {
	    std::cout << '^';
	}

	std::cout << std::endl;
    }
}
