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

const int maxM = 51;
const int maxN = 51;

int n, m, k;
char board[maxM][maxN];
int dp[maxM][maxN]; // minmum operations to reach [i, j];
int endRow, endCol;

void dfs(int row, int col, int time, int operations)
{
    if (row < 1 || col < 1 || row > n || col > m)
        return;
    if (dp[row][col] <= operations || time > k)
        return;
    dp[row][col] = operations;
    //cout << row << " " << col << " " << operations << endl;
    dfs(row-1, col, time + 1, operations + (board[row][col] != 'U'));
    dfs(row+1, col, time + 1, operations + (board[row][col] != 'D'));
    dfs(row, col-1, time + 1, operations + (board[row][col] != 'L'));
    dfs(row, col+1, time + 1, operations + (board[row][col] != 'R'));

}

int main()
{
    openfile();

    int i, j;
    fin >> n >> m >> k;
    for (i = 1; i <= n; ++ i)
    {
        for (j = 1; j <= m; ++ j) {
            fin >> board[i][j];
            if (board[i][j] == '*') {
                endRow = i;
                endCol = j;
            }
            dp[i][j] = INT_MAX;
        }
    }

    dfs(1, 1, 0, 0);

    if (dp[endRow][endCol] == INT_MAX)
        cout << -1 << endl;
    else
        cout << dp[endRow][endCol] << endl;

    closefile();
    return 0;
}
