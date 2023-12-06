#pragma once

#include "../diagnostic/diagnostic.hpp"
#include <variant>
#include <string>

using FileResult = std::variant<std::string, Diagnostic>;

FileResult read_file(std::string path);
