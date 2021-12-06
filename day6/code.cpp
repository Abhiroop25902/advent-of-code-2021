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

// here direct simulation will take a lot of time as number of pufferfishes will grow near exponentially
//  we will have to use DP

// part 1 -> recursive
// we can observe that a pufferfish with time `alpha` will take alpha time and then reset itself to 6, and generate a pufferfish with time 8

// so we can say that the extra pufferfish released by a fish with time 'alpha' and remaining days 'daysRemaining' is
// f(alpha, daysRemaining) = 1 + f(6, daysRemianing - alpha - 1) + f(8, daysRemaining - alpha - 1)
// base case f(6,k) = 0 if k < 6; f(8, m) = 0 if m < 8

// -1 in recursion is due to the fact that we are also considering 0 as a valid timer
// Eg: if alpha = 4 -> timer goes 4,3,2,1,0 ; i.e 5 days (alpha + 1)

// now doing this recursively will also go exponential so here we can use DP
// so what I did was create two arrays f6 and f8 where f6[daysRemaining] = f(6, daysRemaining) and similar with f8
int main()
{
    const string INPUT_FILE = "./input.txt";
    ifstream fin;
    fin.open(INPUT_FILE);

    const short NUM_DAYS = 256;

    string line;
    fin >> line;

    auto timers = split(line, ",");

    vector<ull> f6(NUM_DAYS, 0);
    vector<ull> f8(NUM_DAYS, 0);

    for (int i = 0; i < NUM_DAYS; i++)
    {
        if (i - 7 >= 0)
            f6[i] = 1 + f6[i - 7] + f8[i - 7];
        if (i - 9 >= 0)
            f8[i] = 1 + f6[i - 9] + f8[i - 9];
    }

    ull numPufferFish = timers.size();

    for (auto time : timers)
    {
        // cout << time << endl;
        // cout <<NUM_DAYS - time - 1 << endl ;
        // cout <<  f6[NUM_DAYS - time - 1]  << endl;
        // cout <<  f8[NUM_DAYS - time - 1]  << endl;
        numPufferFish += 1 + f6[NUM_DAYS - time - 1] + f8[NUM_DAYS - time - 1];
    }

    cout << numPufferFish;

    fin.close();
    return 0;
}