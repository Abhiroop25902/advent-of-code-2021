#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

using namespace std;

typedef unsigned long long ull;

// this will give error in case of any overflow
#pragma GCC optimize "trapv"

string findOxygenGeneratorRating(vector<string> &report, int bitIdx = 0)
{
    if (report.size() == 1)
        return report[0];

    if (report.size() == 0 || bitIdx == report[0].size())
        throw std::runtime_error("Error: specialOutOfBound during Idx");

    vector<string> zeroStrings;
    vector<string> oneStrings;

    for (auto str : report)
        if (str[bitIdx] == '0')
            zeroStrings.push_back(str);
        else
            oneStrings.push_back(str);

    if (zeroStrings.size() > oneStrings.size())
        return findOxygenGeneratorRating(zeroStrings, bitIdx + 1);
    else
        return findOxygenGeneratorRating(oneStrings, bitIdx + 1);
}

string findCO2ScrubberRating(vector<string> &report, int bitIdx = 0)
{
    if (report.size() == 1)
        return report[0];

    if (report.size() == 0 || bitIdx == report[0].size())
        throw std::runtime_error("Error: specialOutOfBound during Idx");

    vector<string> zeroStrings;
    vector<string> oneStrings;

    for (auto str : report)
        if (str[bitIdx] == '0')
            zeroStrings.push_back(str);
        else
            oneStrings.push_back(str);

    if (zeroStrings.size() <= oneStrings.size())
        return findCO2ScrubberRating(zeroStrings, bitIdx + 1);
    else
        return findCO2ScrubberRating(oneStrings, bitIdx + 1);
}

int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    vector<string> report;
    string temp;

    while (fin >> temp)
        report.push_back(temp);

    auto oxygenGeneratorRating = findOxygenGeneratorRating(report);
    auto decimalOxygenGeneratorRating = stoll(oxygenGeneratorRating, 0, 2);

    auto co2ScrubberRating = findCO2ScrubberRating(report);
    auto decimalCO2ScrubberRating = stoll(co2ScrubberRating, 0, 2);

    cout << "O2 Generator Rating: " << oxygenGeneratorRating << "\tDecimal:" << decimalOxygenGeneratorRating << endl;
    cout << "CO2 Scrubber Rating: " << findCO2ScrubberRating(report) << "\tDecimal:" << decimalCO2ScrubberRating << endl;
    cout << "Multiplication: " << decimalCO2ScrubberRating * decimalOxygenGeneratorRating;

    fin.close();
    return 0;
}