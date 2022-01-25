#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

map<char, int> hex_to_dec{
    {'0', 0},
    {'1', 1},
    {'2', 2},
    {'3', 3},
    {'4', 4},
    {'5', 5},
    {'6', 6},
    {'7', 7},
    {'8', 8},
    {'9', 9},
    {'A', 10},
    {'B', 11},
    {'C', 12},
    {'D', 13},
    {'E', 14},
    {'F', 15},
};

map<int, char> dec_to_hex{
    {0, '0'},
    {1, '1'},
    {2, '2'},
    {3, '3'},
    {4, '4'},
    {5, '5'},
    {6, '6'},
    {7, '7'},
    {8, '8'},
    {9, '9'},
    {10, 'A'},
    {11, 'B'},
    {12, 'C'},
    {13, 'D'},
    {14, 'E'},
    {15, 'F'},
};

string get_hex_value(int n)
{
    string h;
    int i = 0;

    if (!n)
    {
        h = "0";
    }
    else
    {
        while (n != 0)
        {
            int tmp = 0;
            tmp = n % 16;
            if (tmp < 10)
            {
                h += (char)(tmp + 48);
            }
            else
            {
                h += (char)(tmp + 55);
            }
            i++;
            n = n / 16;
        }
    }
    reverse(h.begin(), h.end());
    return h;
}

int get_dec_value(string s)
{
    int n = s.size() - 1;
    int val = 0;
    int count = 0;
    while (n >= 0)
    {
        int tmp = hex_to_dec[s[n]];
        n--;
        val = val + tmp * ((int)pow(16, count));
        count++;
    }
    return val;
}

string add_hex(string a, string b)
{
    if (a.size() < b.size())
        add_hex(b, a);

    int n = a.size();
    int m = b.size();

    string val = "";

    int carry = 0;
    int i;
    int j;

    for (i = n - 1, j = m - 1; j >= 0; i--, j--)
    {
        int sum = hex_to_dec[a[i]] + hex_to_dec[b[j]] + carry;
        char to_add = dec_to_hex[sum % 16];
        val.push_back(to_add);
        carry = sum / 16;
    }

    while (i >= 0)
    {
        int sum = hex_to_dec[a[i]] + carry;
        char to_add = dec_to_hex[sum % 16];
        val.push_back(to_add);
        carry = sum / 16;
        i--;
    }

    if (carry)
    {
        val.push_back(dec_to_hex[carry]);
    }

    reverse(val.begin(), val.end());
    return val;
}

void remove_backspaces(string &s)
{
    while (s.back() == ' ')
    {
        s.pop_back();
    }
    return;
}

int main()
{
}