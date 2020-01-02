#include <fstream>
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

TEST_CASE("Basic") {
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
        }
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
    }
}
