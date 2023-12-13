#include "../../../include/text/parser/name.hpp"

Name::Name(NameKind kind, std::string name, std::string type, std::any value) {
    this->kind = kind;
    this->name = name;
    this->type = type;
    this->value = value;
}
