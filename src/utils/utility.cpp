#include "../../include/utils/utility.hpp"
#include <fstream>
#include <filesystem>

FileResult read_file(std::string path) {
    std::ifstream file(path);

    if (!file.good()) {
	return Diagnostic(
	    DiagnosticKind::FileNotFound,
	    Span(
		"cli",
		1,
		6,
		5,
		path.length()
	    ),
	    "could not find file: " + path
	);
    }

    if (!std::filesystem::is_regular_file(path)) {
	return Diagnostic(
	    DiagnosticKind::FileNotRegular,
	    Span(
		"cli",
		1,
		6,
		5,
		path.length()
	    ),
	    "specified file is not regular: " + path
	);
    }

    std::string content;

    if (file.good()) {
	std::stringstream string_stream;
	string_stream << file.rdbuf();
	content = string_stream.str();
    }

    return content;
}

std::string get_line(std::string path, size_t line) {
    std::ifstream file(path);
    std::string target;
    size_t current_line = 1;

    while (file.good()) {
	char current = file.get();

	if (current == '\n') {
	    current_line++;
	}

	if (current_line == line) {
	    target.push_back(current);
	}
    }

    return target;
}
