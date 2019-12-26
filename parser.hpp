//
// Created by David on 26.12.2019.
//

#include <vector>
#include <cstring>

using namespace std;

class Parser {
private:
    vector<string> m_files;
    bool m_multithreaded = false;

    void show_help(string program) {
        cerr << "Usage: " << program << " FILES" << endl
             << "\tFILES\t\t\t\t\tSource files (separated by space)\n"
             << "\t-h, --help\t\t\t\tShow this help message\n"
             << "\t-mt, --multithreaded \tRun each file in different thread\n"
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
                    m_multithreaded = true;
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

    bool isMultithreaded() {
        return m_multithreaded;
    }
};