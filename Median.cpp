#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <deque>
#include <map>
using namespace std;

const string input_file = "text.in";
const string out_file = "text.out";
ifstream fin;
ofstream fout;

void openfile() { fin.open(input_file.c_str()); fout.open(out_file.c_str()); }
void closefile() { fin.close(), fout.close(); }

void insertValue(vector<long> &num, long value)
{
    int n = num.size();
    num.push_back(value);
    int i = n - 1;
    while (i >= 0)
    {
        if (num[i] > value) {
            num[i+1] = num[i];
        } else
            break;
        -- i;
    }
    num[i+1] = value;
}

bool removeValue(vector<long> &num, int value)
{
    int low = 0;
    int high = num.size() - 1;
    while (low <= high)
    {
        int mid = (low + high) >> 1;
        if (num[mid] == value) {
            for (int i = mid; i < num.size()-1; ++ i)
                num[i] = num[i+1];
            num.pop_back();
            return true;
        } else if (num[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return false;
}

void getMedian(vector<long> &num)
{
    double sum = 0;
    int size = num.size();
    if (size % 2 == 0) {
         sum = (double(num[size/2]) + double(num[size/2-1])) / 2;
    }
    else
        sum = num[size/2];
    if (ceil(sum) == sum)
        printf("%.0lf\n", sum);
    else
        printf("%.1lf\n", sum);
}

int main()
{
    openfile();

    int i,  N;
    long j;
    fin >> N;

    char ch;
    vector<long> num;
    map<long, int> m;

    for (i = 0; i < N; i ++)
    {
        fin >> ch >> j;
        if (ch == 'r') {
            if (num.empty())
                cout << "Wrong!" << endl;
            else {
                if (removeValue(num, j)) {
                    if (num.empty())
                        cout << "Wrong!" << endl;
                    else {
                        getMedian(num);
                    }
                } else
                    cout << "Wrong!" << endl;
            }
        } else {
           insertValue(num, j);
           getMedian(num);
        }
    }

    closefile();
    return 0;
}
/*
void swap(vector<long> &num, int i, int j)
{
    if (i == j) return;
    int t = num[i];
    num[i] = num[j];
    num[j] = t;
}

int partion(vector<long> &num, int begin, int end)
{
    int pivot = num[end];
    int p = begin, q = begin, r = end;
    while (q < end)
    {
        if (num[q] < pivot) {
            swap(num, p, q);
            p ++;
            q ++;
        } else
            q ++;
    }
    swap(num, p, r);
    return p;
}

void print(vector<long> &num, int begin, int end)
{
    int i = 0;
    for (i = 0; i < begin; ++ i)
        cout << num[i] << " ";

        cout << "(";
    for (i = begin; i <= end; ++ i)
        cout << num[i] << " " ;

        cout << ") ";
    for (i = end + 1; i < num.size(); ++ i)
        cout << num[i] << " ";
    cout << endl;
}

void print(vector<long> &num)
{
    for (int i = 0; i < num.size(); ++ i)
        cout << num[i] << " ";
    cout << endl;
}

// k starts from 1
long getKthNum(vector<long> &num, int begin, int end, int k)
{
    int p = partion(num, begin, end) - begin;
    //cout << p + begin << " " << k <<endl;
   // print(num, begin, end);
    if (p == k-1)
        return num[p+begin];
    else if (p > k-1) {
        return getKthNum(num, begin, p+begin-1, k);
    } else
        return getKthNum(num, p+begin+1, end, k-p-1);
}



double findMedian(vector<long> &num)
{
    int n = num.size();

    if (n & 1)
        // odd
        cout << getKthNum(num, 0, n-1, n / 2 + 1) << endl;
    else {
        long long l = getKthNum(num, 0, n-1, n/2 + 1);
        long long r = getKthNum(num, 0, n-1, n/2);
        if ((l + r) & 1)
            cout << (l+r)/2 << ".5" << endl;
        else
            cout << (l+r)/2 << endl;
    }
    //print(num);
}

int main()
{
    openfile();

    int i,  N;
    long j;
    fin >> N;

    char ch;
    vector<long> num;
    map<long, int> m;

    for (i = 0; i < N; i ++)
    {
        fin >> ch >> j;
        if (ch == 'r') {
            if (m.find(j) == m.end())
                cout << "Wrong!" << endl;
            else {
                vector<long>::iterator findit = find(num.begin(), num.end(), j);
                num[findit - num.begin()] = num[num.size()-1];
                num.pop_back();
                if (m[j] == 1)
                    m.erase(j);
                else
                    m[j] --;
                if (num.empty())
                    cout << "Wrong!" << endl;
                else
                    findMedian(num);
            }
        } else {
            num.push_back(j);
            if (m.find(j) == m.end())
                m[j] = 1;
            else
                m[j] ++;
            findMedian(num);
        }
    }

    closefile();
    return 0;
}*/
