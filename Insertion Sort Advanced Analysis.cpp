#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

const string input_file = "text.in";
const string out_file = "text.out";
ifstream fin;
ofstream fout;

void openfile() { fin.open(input_file.c_str()); fout.open(out_file.c_str()); }
void closefile() { fin.close(), fout.close(); }

const int maxn = 1000003;
int tree[maxn];
int n;

inline int lowbit(int x)
{
    return x & (-x);
}

// 将位置为pos的数更新val的值
inline void update(int pos, int val)
{
    while (pos <= n)
    {
        tree[pos] += val;
        pos += lowbit(pos);
    }
}

inline int query(int x)
{
    int ans = 0;
    while (x > 0)
    {
        ans += tree[x];
        x -= lowbit(x);
    }
    return ans;
}
struct node
{
    int data;
    int index;
    int sortIndex;
};
bool cmp1(const node& a, const node& b)
{
    if(a.data == b.data)
        return a.index < b.index;
    return a.data < b.data;
}
bool cmp2(const node& a, const node& b)
{
    return a.index < b.index;
}

node vec[100001];
int main()
{
    openfile();

    int i, j, T;

    fin >> T;
    while (T --)
    {
        fin >> n;
        long long res = 0;
        memset(tree, 0, sizeof(tree));
        for (i = 1; i <= n; ++ i)
        {
            fin >> vec[i].data;
            vec[i].index = i;
        }
        sort(vec+1, vec+n+1, cmp1);
        vec[1].sortIndex = 1;

        for (i = 2; i <= n; ++ i)
        {
            if (vec[i].data == vec[i-1].data)
                vec[i].sortIndex = vec[i-1].sortIndex;
            else
                vec[i].sortIndex = vec[i-1].sortIndex + 1;
        }
        sort(vec+1, vec+n+1, cmp2);
        for (i = 1; i <= n; ++ i)
        {
            update(vec[i].sortIndex, 1);
            int r = i - query(vec[i].sortIndex);
            //cout << r << endl;
            res += r;
        }
        fout << res << endl;

    }

    closefile();
    return 0;
}
