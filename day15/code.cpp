#include <bits/stdc++.h>

using std::cout;
using std::cin;
#define endl '\n'
#define FAST_IO std::ios_base::sync_with_stdio(false); cin.tie(NULL)
#define ll long long

#define maxN 10000

char grid[maxN][maxN];
bool locked[maxN][maxN];
bool visited[maxN][maxN];
int cost[maxN][maxN];
int r = 0, c = 0;

int delta[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

void testcase() {
    // djikstra
    // cost, i, j
    std::set<std::tuple<int, int, int>> s;
    visited[0][0] = true;
    locked[0][0] = true;
    cost[0][0] = 0;
    s.insert(std::make_tuple(0, 0, 0));
    while (s.size()) {
        std::tuple<int, int, int> pt = *(s.begin());
        int curCost = std::get<0>(pt);
        int curR = std::get<1>(pt);
        int curC = std::get<2>(pt);
        locked[curR][curC] = true;
        s.erase(s.begin());
        for (int d = 0; d < 4; ++d) {
            int newR = curR + delta[d][0];
            int newC = curC + delta[d][1];
            if (newR < 0 || newR >= r || newC < 0 || newC >= c) continue;
            if (locked[newR][newC]) continue;
            int newCost = grid[newR][newC] - '0';

            if (visited[newR][newC]) {
                if (curCost + newCost < cost[newR][newC]) {
                    s.erase(s.find(std::make_tuple(cost[newR][newC], newR, newC)));
                    s.insert(std::make_tuple(curCost + newCost, newR, newC));
                    cost[newR][newC] = curCost + newCost;
                }
            } else {
                visited[newR][newC] = true;
                s.insert(std::make_tuple(curCost + newCost, newR, newC));
                cost[newR][newC] = curCost + newCost;
            }
        }
    }
    cout << cost[r - 1][c - 1] << endl;
}

int main() {
    clock_t begin = clock();

    freopen("./input.txt", "r", stdin);
    std::string line;
    /* Part 1 Grid: */
    r = 0;
    while (cin >> grid[r++]);
    --r;
    c = strlen(grid[0]);
    

    /* Generate part 2 grid: */
    // Clone downwards 5 times first. add 1 every time.
    for (int i = r; i < 5 * r; ++i) {
        for (int col = 0; col < c; ++col) {
            int num = (grid[i % r][col] - '0' + i / r);
            if (num > 9) num -= 9;
            grid[i][col] = num + '0';
        }
    }
    r *= 5;
    // Clone rightwards 5 times.
    for (int i = c; i < 5 * c; ++i) {
        for (int row = 0; row < r; ++row) {
            int num = (grid[row][i % c] - '0' + i / c);
            if (num > 9) num -= 9;
            grid[row][i] = num + '0';
        }
    }
    c *= 5;
    testcase();

    clock_t now = clock();
    cout << "Time Taken: " << (double) (now - begin) / CLOCKS_PER_SEC << "s" << endl;

    return 0;
}
