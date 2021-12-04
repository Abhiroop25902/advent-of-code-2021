#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

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

    // for (auto i : numbers)
    //     cout << i << " ";
    // cout << "\n";

    vector<Bingo *> bingoTables;

    while (!fin.eof())
        bingoTables.push_back(Bingo::readBingo(fin));

    for (auto number : numbers)
    {

        bool done = false;
        for (auto tablePtr : bingoTables)
        {
            if (tablePtr->checkElement(number))
            {
                cout << number << endl;
                tablePtr->printTable();
                cout << tablePtr->sumUnchecked() * number << endl;
                done = true;
                break;
            }
        }

        if (done == true)
            break;

        // cout << endl << endl << endl;
    }
    fin.close();
    return 0;
}