#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Bingo
{
    static const short TABLE_SIZE = 5;
    vector<vector<short>> table;
    vector<vector<bool>> taken;
    unordered_map<short, pair<short, short>> numToPos;
    unordered_set<short> numbers;

    bool checkForBingo(pair<short, short> pos);
    bool isPresent(short num);

public:
    Bingo(vector<vector<short>> &table);
    static Bingo *readBingo(ifstream &fin);
    void printTable();
    bool checkElement(short num);
    int sumUnchecked();
};

Bingo::Bingo(vector<vector<short>> &table)
{
    this->table = table;
    taken = vector<vector<bool>>(table.size(), vector<bool>(table.size(), false));

    for (int i = 0; i < table.size(); i++)
        for (int j = 0; j < table[i].size(); j++)
        {
            numToPos[table[i][j]] = {i, j};
            numbers.insert(table[i][j]);
        }
}

Bingo *Bingo::readBingo(ifstream &fin)
{
    vector<vector<short>> table(5, vector<short>(5, 0));

    for (int i = 0; i < TABLE_SIZE; i++)
        for (int j = 0; j < TABLE_SIZE; j++)
            fin >> table[i][j];

    return new Bingo(table);
}

void Bingo::printTable()
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
            cout << table[i][j] << " ";

        cout << '\t';

        for (int j = 0; j < table[i].size(); j++)
            cout << taken[i][j] << " ";

        cout << '\n';
    }
    cout << '\n';
}

bool Bingo::checkElement(short num)
{
    if (isPresent(num))
    {
        auto pos = numToPos[num];
        taken[pos.first][pos.second] = true;

        return checkForBingo(pos);
    }
    else
        return false;
}

bool Bingo::checkForBingo(pair<short, short> pos)
{
    int colSum = 0;

    for (int i = 0; i < table.size(); i++)
        colSum += taken[i][pos.second];

    if (colSum == table.size())
        return true;


    int rowSum = 0;

    for (int j = 0; j < table.size(); j++)
        rowSum += taken[pos.first][j];

    return rowSum == table.size();
}

int Bingo::sumUnchecked()
{
    int sum = 0;

    for (int i = 0; i < table.size(); i++)
        for (int j = 0; j < table.size(); j++)
            if (taken[i][j] == false)
                sum += table[i][j];

    return sum;
}

bool Bingo::isPresent(short num)
{
    return numbers.find(num) != numbers.end();
}