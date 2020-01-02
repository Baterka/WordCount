#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>

#include "counter.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        // Parse input parameters
        auto *parser = new Parser(argc, argv);

        // Initialize counter
        auto *counter = new Counter(parser->getFiles(), parser->isMultiThreaded(), parser->getDivider());


        auto start = chrono::steady_clock::now();
        int words = counter->getWords();
        auto end = chrono::steady_clock::now();

        cout << endl << "Total words: " << words << " | Took: "
             << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;

    } catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 0;
    }
}
