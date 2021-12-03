#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    const string INPUT_FILE = "./input.txt";
    vector<int> arr;
    int temp;

    ifstream fin;
    fin.open(INPUT_FILE);
    while (fin >> temp)
        arr.push_back(temp);
    fin.close();

    int count = 0;
    long long prevSum = INT64_MAX;

    for (int i = 0; i + 2 <= arr.size() - 1; i++)
    {
        long long currSum = arr[i] + arr[i + 1] + arr[i + 2];

        if (currSum > prevSum)
            count++;

        prevSum = currSum;
    }

    cout << count;
}