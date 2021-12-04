#ifndef BINGO
#define BINGO

#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

class Bingo
{
public:
    Bingo(vector<vector<short>> &table);
    static Bingo *readBingo(ifstream &fin);
    void printTable();
    bool checkElement(short num);
    int sumUnchecked();
};
#endif