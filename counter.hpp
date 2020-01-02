#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>
#include <functional>
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

    map<string, int> m_words;
    mutex m_words_mutex;

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

    vector<pair<string, int>> getWords() {
        cout << "Setup:\n\tfiles: ";
        for (const auto &f : m_files)
            cout << f << ' ';
        cout << endl;
        cout << "\tmulti_threaded: " << (m_multi_threaded ? "TRUE" : "FALSE") << endl;
        cout << "\tdivider: '" << m_divider << "' (" << (int) m_divider << ")" << endl;
        cout << "\tnew_line_is_divider: " << (m_new_line_is_divider ? "TRUE" : "FALSE") << endl << endl;

        auto counter = [this](const string &filePath) {
            printf("\t%s\n", filePath.c_str());
            auto start = chrono::steady_clock::now();
            ifstream fin;
            fin.open(filePath, ios::in);

            if (!fin)
                throw runtime_error("Could not open file: " + filePath);

            char ch;
            string word;
            map<string, int> words;
            int count = 0;

            auto newWord = [this, &word, &words, &count]() {
                count++;
                words[word]++;
                word = "";
            };

            while (fin.peek() != EOF) {
                fin.get(ch);

                // If char is non-printable, ignore
                if (!isprint(ch) && !(m_new_line_is_divider && ch == LINE_CHAR))
                    continue;

                // If char is divider, increase word-count
                if (ch == m_divider || (m_new_line_is_divider && ch == LINE_CHAR)) {
                    newWord();
                } else
                    word += ch;
            }

            newWord();

            m_counter += count;
            lock_guard<mutex> guard(m_words_mutex);
            for (auto &w : words)
                m_words[w.first] += w.second;

            auto end = chrono::steady_clock::now();
            long ptime = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            printf("\t\tWords: %i | Took: %ims\n", count, (int) ptime);
        };

        printf("Processing...\n");
        for (const auto &f : m_files) {
            if (m_multi_threaded)
                m_threads.push_back(move(thread(counter, f)));
            else {
                counter(f);
            }
        }

        if (m_multi_threaded)
            for (thread &t : m_threads) {
                if (t.joinable())
                    t.join();
            }

        vector<pair<string, int>> output;

        // Copy pairs from map to vector
        copy(m_words.begin(), m_words.end(), back_inserter<vector<pair<string, int>>>(output));

        // sort the vector DESC
        sort(output.begin(), output.end(), [](const pair<string, int> &l, const pair<string, int> &r) {
            return l.second > r.second;
        });

        printf("Done.\n");

        return output;
    }
};