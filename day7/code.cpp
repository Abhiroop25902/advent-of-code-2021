#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

typedef unsigned long long ull;
typedef long double ld;

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

ull fuelConsumed(ull dist){
    return dist * (dist + 1) /2;
}

int minDistBruteForce(vector<int> &positions)
{
    sort(positions.begin(), positions.end());
    ull minDist = UINT64_MAX;

    for(int atkPosition = positions[0]; atkPosition <= positions.back(); atkPosition++){
    
        cout << atkPosition << "/" << positions.back() << "\tdone\n";
        ull dist = 0;

        for(auto position: positions)
            dist += fuelConsumed(abs(atkPosition - position));

        minDist = min(minDist, dist);
    }    

    return minDist;
}

int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    string line;
    fin >> line;

    auto positions = split(line, ",");

    cout << minDistBruteForce(positions);

    fin.close();
    return 0;
}