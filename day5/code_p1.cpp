#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <unordered_map>
using namespace std;

typedef unsigned long long ull;

// this will give error in case of any overflow
#pragma GCC optimize "trapv"

vector<short> split(string s, string del = " ")
{
    vector<short> numbers;
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

int findIntersectionCount(vector<vector<short>> &paths)
{

    short maxElem = INT16_MIN;
    for (auto path : paths)
        for (auto elem : path)
            maxElem = max(maxElem, elem);

    vector<vector<int>> pathCount(maxElem + 1, vector<int>(maxElem + 1, 0));

    for (auto path : paths)
    {
        if (path[0] == path[2])
        {
            if (path[1] > path[3])
                swap(path[1], path[3]);

            for (int y = path[1]; y <= path[3]; y++)
                pathCount[y][path[0]]++;
        }
        else if (path[1] == path[3])
        {
            if (path[0] > path[2])
                swap(path[0], path[2]);

            for (int x = path[0]; x <= path[2]; x++)
                pathCount[path[1]][x]++;
        }
    }

    // for (auto i : pathCount)
    // {
    //     for (auto j : i)
    //         cout << j << " ";
    //     cout << endl;
    // }

    int intersectionCount = 0;
    for (auto i : pathCount)
        for (auto j : i)
            if(j > 1)
                intersectionCount++;

    return intersectionCount;
}

int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    string line;

    vector<vector<short>> paths;

    while (fin >> line)
    {
        auto path = split(line, ",");

        fin >> line;
        fin >> line;
        auto fin = split(line, ",");
        path.insert(path.end(), fin.begin(), fin.end());

        // for (auto i : path)
        //     cout << i << " ";
        // cout << '\n';

        paths.push_back(path);
    }

    cout << findIntersectionCount(paths);
    fin.close();
    return 0;
}