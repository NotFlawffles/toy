#include "../include/compiler/compiler.hpp"
#include <cstdlib>
#include <iostream>

#define ARGV_MINIMUM_REQUIRED 2

int usage(void) {
    std::cerr << "usage: toyc <file name>" << std::endl;
    return EXIT_FAILURE;
}

int main(int argc, char** argv) {
    if (argc < ARGV_MINIMUM_REQUIRED) {
	return usage();
    }

    compile(argv[1]);
    return EXIT_SUCCESS;
}
