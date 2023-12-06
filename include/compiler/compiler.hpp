#pragma once

#include <variant>
#include "../diagnostic/diagnostic.hpp"

using CompilationResult = std::variant<int, Diagnostic>;

CompilationResult compile(std::string path);
