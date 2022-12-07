#include <bits/stdc++.h>
using namespace std;

int main() {
    char c = 129;
    unsigned char b = 129;
    signed char a = 129;
    cout << (int) c << endl;
    cout << (int) b << endl;
    cout << (int) a << endl;

    unsigned char d = c;
    unsigned char e = a;

    cout << (int) d << endl;
    cout << (unsigned int) b << endl;
    cout << (int) e << endl;

    return 0;
}