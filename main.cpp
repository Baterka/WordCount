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
        auto *counter = new Counter(parser->getFiles(), parser->isMultiThreaded(), parser->getDivider(),
                                    parser->isNewLineDivider(), parser->getNGramSize());

        // Start time measurement
        auto start = chrono::steady_clock::now();

        // Count words
        vector<pair<string, int>> words = counter->getWords();

        // End time measurement (w/o print)
        auto end = chrono::steady_clock::now();

        int total = 0;
        if (!parser->getOutputFile().empty()) {
            ofstream fout(parser->getOutputFile());

            cout << endl << "Printing output into file..." << endl;
            for (const auto &w : words) {
                fout << w.second << " " << w.first << endl;
                total += w.second;
            }
            fout.close();
        } else {
            cout << endl << "Printing output:" << endl;
            for (const auto &w : words) {
                cout << w.second << " " << w.first << endl;
                total += w.second;
            }
        }
        cout << "Done." << endl << endl;

        cout << "Summary:" << endl;
        cout << "\tWords total:\t" << total << endl
             << "\tTook:\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms (w/o print)"
             << endl;
        // End time measurement (with print)
        auto end2 = chrono::steady_clock::now();
        cout << "\t\t\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end2 - start).count() << "ms (total)";

    } catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 0;
    }
}
