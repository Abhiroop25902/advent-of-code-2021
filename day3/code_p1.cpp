#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

typedef unsigned long long ull;

// this will give error in case of any overflow
#pragma GCC optimize "trapv"

int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    vector<string> numberStrings;
    string temp;

    while (fin >> temp)
        numberStrings.push_back(temp);

    string gammaRate;
    string epsilonRate;

    for (int j = 0; j < numberStrings[0].size(); j++)
    {
        int zero_count = 0;
        for (auto str : numberStrings)
            if (str[j] == '0')
                zero_count++;

        if (zero_count > numberStrings.size() - zero_count) // RHS = one_count
        {
            gammaRate.push_back('0');
            epsilonRate.push_back('1');
        }
        else{
            gammaRate.push_back('1');
            epsilonRate.push_back('0');
        }
    }

    auto gammaRateDecimal = stoi(gammaRate, 0, 2);
    auto epsilonRateDecimal = stoi(epsilonRate, 0, 2);

    cout << "gamma rate:\t"<< gammaRate << "\tdecimal: "<<gammaRateDecimal<<endl;
    cout << "epsilon rate:\t"<< epsilonRate << "\tdecimal: "<<epsilonRateDecimal<<endl;
    cout << "Multiplication:\t" << (ull)gammaRateDecimal * (ull)epsilonRateDecimal;


    fin.close();
    return 0;
}