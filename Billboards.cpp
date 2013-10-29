#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <deque>
using namespace std;

const string input_file = "text.in";
const string out_file = "text.out";
ifstream fin;
ofstream fout;

void openfile() { fin.open(input_file.c_str()); fout.open(out_file.c_str()); }
void closefile() { fin.close(), fout.close(); }



int main()
{
    openfile();

    int i, j, k, n, T;
    long long sum = 0;
    fin >> n >> k;
    vector<int> profit;
    profit.assign(n, 0);
    for (i = 0; i < n; ++ i)
    {
        fin >> profit[i];
        sum += profit[i];
    }
    if (k >= n) {
        cout << 0 << endl;
        return 0;
    }
    profit[n] = 0;
    deque<long long> minQ;
    vector<long long> dp(n+1); // dp[i] is the minmum profits if we don't choose profit[i]
    for (i = 0; i <= k; ++ i)
    {
        dp[i] = profit[i];
        while (!minQ.empty() && dp[i] <= dp[minQ.back()])
            minQ.pop_back();
        minQ.push_back(i);
    }

    for (i = k + 1; i < n; ++ i)
    {
        dp[i] = profit[i] + dp[minQ.front()];
        while (!minQ.empty() && dp[i] <= dp[minQ.back()])
            minQ.pop_back();
        while (!minQ.empty() && i >= minQ.front() + k + 1)
            minQ.pop_front();
        minQ.push_back(i);
    }
    dp[n] = dp[minQ.front()];
    cout << sum - dp[n] << endl;
    closefile();
    return 0;
}
