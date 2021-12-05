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

    //finding max element of the data -> the countgrid made will have size (maxelem + 1)*(maxelem + 1)
    for (auto path : paths)
        for (auto elem : path)
            maxElem = max(maxElem, elem);

    vector<vector<short>> pathCount(maxElem + 1, vector<short>(maxElem + 1, 0));

    for (auto path : paths)
        if (path[0] == path[2]) //if x1 == x2
        {
            if (path[1] > path[3])
                swap(path[1], path[3]);

            for (int y = path[1]; y <= path[3]; y++)
                pathCount[y][path[0]]++;
        }
        else if (path[1] == path[3]) // y1 == y2
        {
            if (path[0] > path[2])
                swap(path[0], path[2]);

            for (int x = path[0]; x <= path[2]; x++)
                pathCount[path[1]][x]++;
        }
        else // diagonal case
        {
            if (path[0] > path[2]) //making sure x will always increment
            {
                swap(path[0], path[2]);
                swap(path[1], path[3]);
            }

            int yUpdate = path[1] < path[3] ? 1 : -1; //checking if y will increment or decrement

            int x = path[0];
            int y = path[1];

            while (x <= path[2])
            {
                pathCount[y][x]++;
                x++;
                y += yUpdate;
            }
        }

    //// print the grid
    // for (auto i : pathCount)
    // {
    //     for (auto j : i)
    //         cout << j << " ";
    //     cout << endl;
    // }

    //count intersection points
    int intersectionCount = 0;
    for (auto i : pathCount)
        for (auto j : i)
            if (j > 1)
                intersectionCount++;

    return intersectionCount;
}

int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    string line;

    //convert one line into a vector of 4 values path
    //{path[0], path[1]} -> {path[2],path[3]}
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