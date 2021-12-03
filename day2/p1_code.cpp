#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

typedef unsigned long long ull;

int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    string status;
    int value;
    int currX = 0;
    int currDepth = 0;

    while (fin >> status >> value)
    {
        if(status == "forward")
            currX += value;
        else if(status == "down")
            currDepth += value;
        else if(status == "up")
            currDepth = max(0, currDepth - value);
        else throw std::runtime_error("error: wrong status");
    }

    cout << currX << endl;
    cout << currDepth << endl;
    cout << "ans : " << (ull)currX * currDepth;
    fin.close();
    return 0;
}