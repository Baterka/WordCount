#include <unistd.h>
#include <iostream>

#include "parser.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        // Parse input parameters
        auto *parser = new Parser(argc, argv);

        // Initialize counter
        auto *counter = new Counter(parser->getFiles(), parser->isMultithreaded());

    } catch (...) {
        return 0;
    }
}
