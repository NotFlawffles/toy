#pragma once

#include <string>

class Span {
    public:
    std::string stream;
    size_t row, column, index, length;

    Span(std::string, size_t, size_t, size_t, size_t);
    Span(void);
};
