#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <unordered_map>

#include "bingo.h"

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

int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    string numString;
    fin >> numString;

    auto numbers = split(numString, ",");

    vector<Bingo *> bingoTables;

    while (!fin.eof())
        bingoTables.push_back(Bingo::readBingo(fin));

    unordered_map<Bingo *, bool> done;
    int doneCount = 0;
    for (auto number : numbers)
        for (auto tablePtr : bingoTables)
            if (doneCount < bingoTables.size() && !done[tablePtr] && tablePtr->checkElement(number))
            {
                done[tablePtr] = true;
                doneCount++;
                if (doneCount == bingoTables.size())
                    cout << tablePtr->sumUnchecked() * number << endl;
            }
    fin.close();
    return 0;
}