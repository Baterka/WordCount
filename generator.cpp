#include <random>
#include <iostream>
#include <fstream>
#include <utility>

using namespace std;

class Generator {
private:
    string m_alphabet = "abcdefghijklmnopqrstuvwxyz";
    uniform_int_distribution<size_t> m_alpha_dist;
    uniform_int_distribution<size_t> m_length_dist;
public:
    Generator(pair<int, int> range, string alphabet) : m_alphabet(std::move(alphabet)),
                                                       m_length_dist(range.first, range.second),
                                                       m_alpha_dist(0, m_alphabet.size() - 1) {};

    explicit Generator(pair<int, int> range) : m_length_dist(range.first, range.second),
                                               m_alpha_dist(0, m_alphabet.size() - 1) {};

    explicit Generator(string alphabet) : m_alphabet(std::move(alphabet)), m_length_dist(1, 5),
                                          m_alpha_dist(0, m_alphabet.size() - 1) {};

    string getRandomWord(int length) {
        random_device dev;
        static default_random_engine rng(dev());
        string str;
        while (str.size() < length) str += m_alphabet[m_alpha_dist(rng)];
        return str;
    }

    string getRandomWord() {
        random_device dev;
        static default_random_engine rng(dev());
        return getRandomWord(m_length_dist(rng));
    }

    string getAlphabet() {
        return m_alphabet;
    }

    pair<int, int> getRange() {
        return {m_length_dist.min(), m_length_dist.max()};
    }
};

class Parser {
private:
    vector<int> m_words;
    int m_min = 1;
    int m_max = 5;
    string m_output_dir = "";
    string m_alphabet = "abcdefghijklmnopqrstuvwxyz";

    void show_help(string program) {
        cerr << "Usage:" << endl
             << "\tWORDS\t\t\t\t\t\t\t\tNumber of words in file (separated by space)\n"
             << "\t-h, --help\t\t\t\t\t\t\t\tShow this help message\n"
             << "\t-r MIN MAX, --range MIN MAX \t\tWord size range (Optional)\n"
             << "\t-a ALPHABET, --alphabet ALPHABET \tAlphabet used to generate words (Optional)\n"
             << "\t-od DIR, --output_dir DIR \tSave output files into this directory (Optional, default \".\")\n";
       exit(0);
    }

    static bool isParameter(string s) {
        return s.rfind("-", 0) == 0 || s.rfind("--", 0) == 0;
    }

public:
    Parser(int argc, char *argv[]) {
        if (argc < 2)
            show_help(argv[0]);
        string prev_switch;
        bool next_is_value = false;
        for (int i = 1; i < argc; ++i) {
            string arg = argv[i];
            if (isParameter(arg)) {
                if (arg == "-h" || arg == "--help")
                    show_help(argv[0]);
                else if (arg == "-r" || arg == "--range")
                    prev_switch = "r";
                else if (arg == "-od" || arg == "--output_dir")
                    prev_switch = "od";
                else if (arg == "-a" || arg == "--alphabet")
                    prev_switch = "a";
                else {
                    cerr << "Unknown parameter " << arg << endl;
                    throw invalid_argument("Invalid syntax.");
                }
            } else if (!prev_switch.empty()) {
                if (prev_switch == "a") {
                    m_alphabet = arg;
                    prev_switch = "";
                } else if (prev_switch == "r") {
                    m_min = stoi(arg);
                    prev_switch = "r(2)";
                } else if (prev_switch == "od") {
                    m_output_dir = arg;
                    prev_switch = "";
                } else if (prev_switch == "r(2)") {
                    m_max = stoi(arg);
                    if (m_min > m_max)
                        throw invalid_argument("Range is invalid.");
                    prev_switch = "";
                }
            } else {
                m_words.emplace_back(stoi(arg));
            }
        }

        if (!prev_switch.empty())
            throw invalid_argument("Missing value for argument '-" + prev_switch + "'");

        if (m_words.empty())
            throw invalid_argument("You must define at least one count.");
    }

    ~Parser() = default;

    vector<int> getWords() {
        return m_words;
    }

    pair<int, int> getRange() {
        return {m_min, m_max};
    }

    string getAlphabet() {
        return m_alphabet;
    }

    string getOutputDir() {
        return m_output_dir;
    }
};

int main(int argc, char *argv[]) {
    try {
        // Parse input parameters
        auto parser = new Parser(argc, argv);

        // Initialize generator
        Generator generator(parser->getRange(), parser->getAlphabet());

        cout << "Setup:\n\tword_counts: ";
        for (const auto &f : parser->getWords())
            cout << f << ' ';
        cout << endl;
        cout << "\talphabet: " << generator.getAlphabet() << endl;
        const auto range = generator.getRange();
        cout << "\tword_length_range: " << range.first << "-" << range.second << endl;
        cout << "\toutput_dir: " << parser->getOutputDir() << endl << endl;

        cout << "Generating files..." << endl;
        int index = 0;
        for (auto size : parser->getWords()) {
            string fileName = parser->getOutputDir() + "words" + to_string(++index) + ".txt";
            ofstream out(fileName);
            for (int i = 0; i < size; i++)
                out << generator.getRandomWord() + (i < size - 1 ? " " : "");
            out.close();
            cout << "\t" << fileName << endl;
        }
        cout << "Done." << endl;
        delete parser;
        return 0;
    } catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
        return 0;
    }
}
