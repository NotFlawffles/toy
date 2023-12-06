#include "../../include/compiler/compiler.hpp"
#include "../../include/text/lexer/lexer.hpp"
#include "../../include/text/parser/parser.hpp"
#include "../../include/utils/utility.hpp"

CompilationResult compile(std::string path) {
    auto source = read_file(path);

    if (std::get_if<Diagnostic>(&source)) {
	return std::get<Diagnostic>(source);
    }

    auto lexer = Lexer(path, std::get<std::string>(source));
    auto parser = Parser(lexer);
    auto tree = parser.parse();

    for (auto diagnostic: parser.diagnostics) {
	diagnostic.show();
    }

    return EXIT_SUCCESS;
}
