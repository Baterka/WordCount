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
    bool m_new_line_is_divider = false;
    char m_divider = 32;
    int m_ngram_size = 1;
    string m_output_file;

    void show_help(string program) {
        cerr << program << " FILES" << endl
             << "\tFILES\t\t\t\t\t\t\t\t\tSource files (separated by space)\n"
             << "\t-n COUNT, --ngram COUNT\t\t\t\t\t\t\t\tHow much words is one word (Optional, default is 1)\n"
             << "\t-h, --help\t\t\t\t\t\t\t\tShow this help message\n"
             << "\t-d CHAR, --divider CHAR \t\t\t\tWhat will be considered as word divider (Optional, default is \" \")\n"
             << "\t-nld, --new_line_divider \t\t\t\tNew line in file is also divider (Optional)\n"
             << "\t-mt, --multi_threaded \t\t\t\t\tRun each file in different thread (Optional)\n"
             << "\t-of FILENAME, --output_file FILENAME \tPrint output into file (Optional)\n";
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
        string prev_switch;
        bool next_is_value = false;
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];
            if (isParameter(arg)) {
                if (arg == "-mt" || arg == "--multi_threaded")
                    m_multiThreaded = true;
                else if (arg == "-nld" || arg == "--new_line_divider")
                    m_new_line_is_divider = true;
                else if (arg == "-h" || arg == "--help")
                    show_help(argv[0]);
                else if (arg == "-d" || arg == "--divider")
                    prev_switch = "d";
                else if (arg == "-n" || arg == "--ngram")
                    prev_switch = "n";
                else if (arg == "-of" || arg == "--output_file")
                    prev_switch = "of";
                else {
                    cerr << "Unknown parameter " << arg << endl;
                    throw invalid_argument("Invalid syntax.");
                }
            } else if (!prev_switch.empty()) {
                if (prev_switch == "d") {
                    m_divider = arg[0];
                    prev_switch = "";
                } else if (prev_switch == "n") {
                    m_ngram_size = stoi(arg);
                    prev_switch = "";
                } else if (prev_switch == "of") {
                    m_output_file = arg;
                    prev_switch = "";
                } else {
                    throw invalid_argument("Invalid syntax.");
                }
            } else
                m_files.emplace_back(arg);
        }

        if (!prev_switch.empty())
            throw invalid_argument("Missing value for argument '-" + prev_switch + "'");

        if (m_files.empty())
            throw invalid_argument("You must define at least one input file.");
    }

    ~Parser() = default;

    vector<string> getFiles() {
        return m_files;
    }

    bool isMultiThreaded() {
        return m_multiThreaded;
    }

    bool isNewLineDivider() {
        return m_new_line_is_divider;
    }

    int getNGramSize(){
        return m_ngram_size;
    }

    char getDivider() {
        return m_divider;
    }

    string getOutputFile() {
        return m_output_file;
    }
};