#include <fstream>
#include <random>
#include "catch.hpp"
#include "../counter.hpp"

using namespace std;

unsigned int Factorial(unsigned int number) {
    return number <= 1 ? number : Factorial(number - 1) * number;
}

void generateFile(vector<string> words) {
    ofstream out("file.txt");
    for (int i = 0; i < words.size(); i++)
        out << words[i] + (i < words.size() - 1 ? " " : "");
    out.close();
}

TEST_CASE("Basic functionality") {
    SECTION("Single character words") {
        SECTION("Sorted") {
            SECTION("Once") {
                vector<string> words({"a", "b", "c", "d", "e"});
                generateFile(words);

                auto *counter = new Counter({"file.txt"});

                auto output = counter->getWords();

                int i = 0;
                for (auto p : output) {
                    REQUIRE(p.first == words[i++]);
                    REQUIRE(p.second == 1);
                }
            };
            SECTION("Multiple times") {
                vector<string> words({"a", "b", "a", "c", "c", "d", "e", "c"});
                vector<pair<string, int>> correct_output({
                                                                 {"c", 3},
                                                                 {"a", 2},
                                                                 {"b", 1},
                                                                 {"d", 1},
                                                                 {"e", 1},
                                                         });
                generateFile(words);

                auto *counter = new Counter({"file.txt"});

                auto output = counter->getWords();

                int i = 0;
                for (auto p : output) {
                    //cout << p.first << " " << p.second << endl;
                    REQUIRE(p.second == correct_output[i].second);
                    REQUIRE(p.first == correct_output[i++].first);
                }
            };
        };
        SECTION("Unsorted") {
            SECTION("Once") {
                vector<string> sorted_words({"a", "b", "c", "d", "e"});
                vector<string> words(sorted_words);
                shuffle(words.begin(), words.end(), std::mt19937(std::random_device()()));
                generateFile(words);

                auto *counter = new Counter({"file.txt"});

                auto output = counter->getWords();

                int i = 0;
                for (auto p : output) {
                    REQUIRE(p.first == sorted_words[i++]);
                    REQUIRE(p.second == 1);
                }
            };
            SECTION("Multiple times") {
                vector<string> sorted_words({"a", "b", "a", "c", "c", "d", "e", "c"});
                vector<string> words(sorted_words);
                shuffle(words.begin(), words.end(), std::mt19937(std::random_device()()));
                vector<pair<string, int>> correct_output({
                                                                 {"c", 3},
                                                                 {"a", 2},
                                                                 {"b", 1},
                                                                 {"d", 1},
                                                                 {"e", 1},
                                                         });
                generateFile(words);

                auto *counter = new Counter({"file.txt"});

                auto output = counter->getWords();

                int i = 0;
                for (auto p : output) {
                    //cout << p.first << " " << p.second << endl;
                    REQUIRE(p.second == correct_output[i].second);
                    REQUIRE(p.first == correct_output[i++].first);
                }
            };
        };
    };
    SECTION("Multi character words") {
        SECTION("Sorted") {
            SECTION("Once") {
                vector<string> words({"ahoj", "jak", "karle", "mas", "se"});
                generateFile(words);

                auto *counter = new Counter({"file.txt"});

                auto output = counter->getWords();

                int i = 0;
                for (auto p : output) {
                    REQUIRE(p.first == words[i++]);
                    REQUIRE(p.second == 1);
                }
            };
            SECTION("Multiple times") {
                vector<string> words({"ahoj", "karle", "jak", "ahoj", "ahoj", "jak", "se", "mas"});
                vector<pair<string, int>> correct_output({
                                                                 {"ahoj",  3},
                                                                 {"jak",   2},
                                                                 {"karle", 1},
                                                                 {"mas",   1},
                                                                 {"se",    1},
                                                         });
                generateFile(words);

                auto *counter = new Counter({"file.txt"});

                auto output = counter->getWords();

                int i = 0;
                for (auto p : output) {
                    //cout << p.first << " " << p.second << endl;
                    REQUIRE(p.second == correct_output[i].second);
                    REQUIRE(p.first == correct_output[i++].first);
                }
            };
        };
        SECTION("Unsorted") {
            SECTION("Once") {
                vector<string> sorted_words({"ahoj", "jak", "karle", "mas", "se"});
                vector<string> words(sorted_words);
                shuffle(words.begin(), words.end(), std::mt19937(std::random_device()()));
                generateFile(words);

                auto *counter = new Counter({"file.txt"});

                auto output = counter->getWords();

                int i = 0;
                for (auto p : output) {
                    REQUIRE(p.first == sorted_words[i++]);
                    REQUIRE(p.second == 1);
                }
            };
            SECTION("Multiple times") {
                vector<string> sorted_words({"ahoj", "karle", "jak", "ahoj", "ahoj", "jak", "se", "mas"});
                vector<string> words(sorted_words);
                shuffle(words.begin(), words.end(), std::mt19937(std::random_device()()));
                vector<pair<string, int>> correct_output({
                                                                 {"ahoj",  3},
                                                                 {"jak",   2},
                                                                 {"karle", 1},
                                                                 {"mas",   1},
                                                                 {"se",    1},
                                                         });
                generateFile(words);

                auto *counter = new Counter({"file.txt"});

                auto output = counter->getWords();

                int i = 0;
                for (auto p : output) {
                    //cout << p.first << " " << p.second << endl;
                    REQUIRE(p.second == correct_output[i].second);
                    REQUIRE(p.first == correct_output[i++].first);
                }
            };
        };
    };
}

TEST_CASE("N-grams") {
    vector<string> words({"a", "b", "a", "a"});
    SECTION("Bigram") {
        vector<pair<string, int>> correct_output({
                                                         {"a a", 1},
                                                         {"a b", 1},
                                                         {"b a", 1},
                                                 });
        generateFile(words);

        auto *counter = new Counter({"file.txt"}, false, ' ', false, 2);

        auto output = counter->getWords();

        int i = 0;
        for (auto p : output) {
            //cout << p.first << " " << p.second << endl;
            REQUIRE(p.second == correct_output[i].second);
            REQUIRE(p.first == correct_output[i++].first);
        }
    };
    SECTION("Trigram") {
        vector<pair<string, int>> correct_output({
                                                         {"a b a", 1},
                                                         {"b a a", 1},
                                                 });
        generateFile(words);

        auto *counter = new Counter({"file.txt"}, false, ' ', false, 3);

        auto output = counter->getWords();

        int i = 0;
        for (auto p : output) {
            //cout << p.first << " " << p.second << endl;
            REQUIRE(p.second == correct_output[i].second);
            REQUIRE(p.first == correct_output[i++].first);
        }
    };
    SECTION("5-gram with 4 words") {
        generateFile(words);

        auto *counter = new Counter({"file.txt"}, false, ' ', false, 5);

        auto output = counter->getWords();

        REQUIRE(output.empty());
    }
}