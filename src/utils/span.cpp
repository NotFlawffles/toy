#include "../../include/utils/span.hpp"

Span::Span(std::string stream, size_t row, size_t column, size_t index, size_t length) {
    this->stream = stream;
    this->row = row;
    this->column = column;
    this->index = index;
    this->length = length;
}

Span::Span(void) {}
