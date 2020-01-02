//
// Created by David on 26.12.2019.
//

#include <vector>
#include <cstring>
#include <iostream>

using namespace std;

class Parser {
private:
    vector<string> m_files;
    bool m_multiThreaded = false;
    char m_divider = ' ';

    void show_help(string program) {
        cerr << "Usage:\t" << program << " FILES" << endl
             << "\t\tFILES\t\t\t\t\tSource files (separated by space)\n"
             << "\t\t-h, --help\t\t\t\tShow this help message\n"
             //<< "\t-d, --divider \t\t\tWhat will be considered as word divider (Optional, default is Space)\n"
             << "\t\t-mt, --multithreaded \tRun each file in different thread\n"
             << endl;
    }

    static bool isParameter(string s) {
        return s.rfind("-", 0) == 0 || s.rfind("--", 0) == 0;
    }

public:
    Parser(int argc, char *argv[]) {
        if (argc < 2) {
            show_help(argv[0]);
            throw invalid_argument("Invalid syntax.");
        }
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];
            if (isParameter(arg)) {
                if (arg == "-mt" || arg == "--multithreaded")
                    m_multiThreaded = true;
                else if (arg == "-h" || arg == "--help")
                    show_help(argv[0]);
                else {
                    cerr << "Unknown parameter " << arg << endl;
                    throw invalid_argument("Invalid syntax.");
                }
            } else
                m_files.emplace_back(arg);
        }
    }

    ~Parser() = default;

    vector<string> getFiles() {
        return m_files;
    }

    bool isMultiThreaded() {
        return m_multiThreaded;
    }

    char getDivider() {
        return m_divider;
    }
};