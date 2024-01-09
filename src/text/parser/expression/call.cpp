#include "../../../../include/text/parser/expression/call.hpp"

Call::Call(std::string name, std::any arguments) {
    this->name = name;
    this->arguments = arguments;
}
