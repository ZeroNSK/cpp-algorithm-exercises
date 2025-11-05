#include <iostream>
#include <map>
#include <string>
#include "functions.h"
using namespace std;

void histogram() {
    string s;
    cout << "Введите текст: ";
    cin.ignore();
    getline(cin, s);
    map<char,int> f;
    for (char c : s) if (c != ' ' && c != '\n') f[c]++;
    int maxh = 0;
    for (auto &p : f) if (p.second > maxh) maxh = p.second;

    for (int h = maxh; h > 0; h--) {
        for (auto &p : f)
            cout << (p.second >= h ? '#' : ' ');
        cout << endl;
    }
    for (auto &p : f) cout << p.first;
    cout << endl;
}
