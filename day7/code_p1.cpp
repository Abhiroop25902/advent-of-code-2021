#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>
using namespace std;

typedef unsigned long long ull;

// this will give error in case of any overflow
#pragma GCC optimize "trapv"

vector<int> split(string s, string del = " ")
{
    vector<int> numbers;
    int start = 0;
    int end = s.find(del, start);

    while (end != -1)
    {
        numbers.push_back(stoi(s.substr(start, end - start)));
        start = end + del.size();
        end = s.find(del, start);
    }

    numbers.push_back(stoi(s.substr(start, end - start)));

    return numbers;
}

int minDistMedian(vector<int> &positions)
{
    sort(positions.begin(), positions.end());

    int median;

    if (positions.size() % 2 == 1)
        median = positions[positions.size() / 2];
    else
        median = (positions[positions.size() / 2] + positions[(positions.size() / 2) - 1]) / 2;

    ull dist = 0;

    for(auto position: positions)
        dist += abs(median - position);

    return dist;
}

int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    string line;
    fin >> line;

    auto positions = split(line, ",");

    cout << minDistMedian(positions);

    fin.close();
    return 0;
}