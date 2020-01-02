//
// Created by David on 26.12.2019.
//

#include <vector>
#include <fstream>
#include "parser.hpp"

using namespace std;

class Counter {
private:
    vector<string> m_files;
    bool m_multi_threaded = false;

    const char LINE_CHAR = '\n';
    bool m_new_line_is_divider = false;
    char m_divider = ' ';
    atomic<int> m_counter{0};
    atomic<long> m_time{0};

    vector<thread> m_threads;

public:
    explicit Counter(const vector<string> &files) {
        m_files = files;
    }

    Counter(const vector<string> &files, const bool multi_threaded) {
        m_files = files;
        m_multi_threaded = multi_threaded;
    }

    Counter(const vector<string> &files, const bool multi_threaded, const char divider) {
        m_files = files;
        m_multi_threaded = multi_threaded;
        m_divider = divider;
    }

    Counter(const vector<string> &files, const bool multi_threaded, const char divider, bool new_line_is_divider) {
        m_files = files;
        m_multi_threaded = multi_threaded;
        m_divider = divider;
        m_new_line_is_divider = new_line_is_divider;
    }

    int getWords() {
        cout << "multi_threaded: " << (m_multi_threaded ? "TRUE" : "FALSE") << endl;

        auto counter = [this](const string &filePath) {
            auto start = chrono::steady_clock::now();
            ifstream fin;
            fin.open(filePath, ios::in);

            if (!fin)
                throw std::runtime_error("Could not open file: " + filePath);

            char ch;
            int words = 0;

            while (fin.peek() != EOF) {
                fin.get(ch);

                // If char is non-printable, ignore
                if (!isprint(ch) && !(m_new_line_is_divider && ch == LINE_CHAR))
                    continue;

                // If char is divider, increase word-count
                if (ch == m_divider || (m_new_line_is_divider && ch == LINE_CHAR))
                    words++;
            }

            words++;

            auto end = chrono::steady_clock::now();
            long ptime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            printf("File: %s | Words: %i | Took: %ims\n", filePath.c_str(), words, (int) ptime);

            m_time += ptime;
            m_counter += words;
        };

        for (const auto &f : m_files) {
            if (m_multi_threaded)
                m_threads.push_back(move(thread(counter, f)));
            else {
                counter(f);
            }
        }

        if (m_multi_threaded)
            for (std::thread &t : m_threads) {
                if (t.joinable())
                    t.join();
            }

        return m_counter;
    }

};