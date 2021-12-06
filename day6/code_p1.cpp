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

//idea -> direct simulation
int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    const short NUM_DAYS = 80;

    string line;
    fin >> line;

    auto counters = split(line, ",");

    for (int day = 0; day < NUM_DAYS; day++)
    {
        int len = counters.size();
        for (int i = 0; i < len; i++)
        {
            if(counters[i] == 0){
                counters[i] = 6;
                counters.push_back(8);
            }
            else
                counters[i]--;
        }

        // cout << "day left: " <<NUM_DAYS - day - 1 << "\t";
        // for(auto counter: counters)
        //     cout << counter << " ";
        // cout << "\n";
        // cout << day << " " <<counters.size() << '\n';
    }

    cout << counters.size();

    fin.close();
    return 0;
}