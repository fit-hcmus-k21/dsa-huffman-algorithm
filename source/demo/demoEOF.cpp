#include <bits/stdc++.h>
using namespace std;

int main() {
    char c ;
    ifstream fin("demo2.txt", ios::binary);
    while (fin >> c) {
        // cout << c << endl;
    }
    // in ra mã ascii của eof
    cout << "EOF: " << (int) fin.eof() << endl;
    fin.close();
    return 0;
}