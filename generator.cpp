#include <random>
#include <iostream>
#include <fstream>

using namespace std;

string random_string(size_t length) {
    static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
    random_device dev;
    static default_random_engine rng(dev());
    static uniform_int_distribution<size_t> dist(0, alphabet.size() - 1);

    string str;
    while (str.size() < length) str += alphabet[dist(rng)];
    return str;
}

int main(int argc, char *argv[]) {
    vector<int> sizes{5'000'000, 15'000'000, 10'000'000};

    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(5, 15);

    int index = 0;
    for (auto size : sizes) {
        string fileName = "../words" + to_string(++index) + ".txt";
        ofstream out(fileName);
        for (int i = 0; i < size; i++)
            out << random_string(dist(rng)) + (i < size - 1 ? " " : "");
        out.close();
        cout << "File ''" << fileName << " generated." << endl;
    }
    return 0;
}
